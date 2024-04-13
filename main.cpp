#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Block
{
    vector<ll> words;
    ll tag;
    bool valid;
    bool dirty;
    Block(int numwords)
    {
        words = vector<ll>(numwords, 0);
        tag = -1;
        valid = false;
        dirty = false;
    }
    void create(ll address, ll tag, ll numwords)
    {
        this->tag = tag;
        valid = true;
        for (int i = 0; i < numwords; i++)
            words[i] = (address + (i * 4));
    }
};

class Cache
{
public:
    vector<vector<Block>> data;
    int numsets;
    int numblocks;
    int numwords;
    int lognumbytes;
    string allocate;
    string write;
    string replacement;

    vector<queue<pair<int, Block>>> replace_data;
    vector<int> replace_index;

    vector<set<pair<int, ll>>> lru;
    vector<unordered_map<ll, int>> addr_to_time;
    vector<unordered_map<ll, int>> address_present;

    vector<list<pair<int, ll>>> lru_dll;
    vector<unordered_map<ll, list<pair<int, ll>>::iterator>> nodes;

    int tag_length;

    int total_loads = 0;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    int total_cycles = 0;

    int hit_time = 1;
    int miss_penalty = 100;

    Cache(int numsets, int numblocks, int numwords, string allocate, string write, string replacement)
    {
        this->numsets = numsets;
        this->numblocks = numblocks;
        this->numwords = numwords;
        this->lognumbytes = 2 + (int)log2(numwords);
        this->allocate = (allocate == "write-allocate" ? "yes" : "no");
        this->write = (write == "write-through" ? "through" : "back");
        this->replacement = replacement;

        this->replace_data.resize(numsets, queue<pair<int, Block>>());

        this->lru.resize(numsets, set<pair<int, ll>>());
        this->addr_to_time.resize(numsets, unordered_map<ll, int>());
        this->address_present.resize(numsets, unordered_map<ll, int>());

        this->replace_index.resize(numsets, 0);
        this->tag_length = 32 - (int)log2(numsets) - (int)log2(numblocks);

        this->lru_dll.resize(numsets, list<pair<int, ll>>());
        this->nodes.resize(numsets, unordered_map<ll, list<pair<int, ll>>::iterator>());

        this->miss_penalty *= numwords;

        data.resize(numsets);
        for (int i = 0; i < numsets; i++)
            data[i].resize(numblocks, Block(numwords));
    }

    void operate(vector<pair<char, ll>> instructions)
    {
        for (pair<char, ll> p : instructions)
        {
            if (p.first == 'l')
            {
                total_loads++;
                read(p.second);
                // printSet((p.second>>2) % numsets);
                // printData();
            }
            else
            {
                total_stores++;
                if (write == "through")
                    write_through(p.second);
                else
                    write_back(p.second);
            }
            // printSet((p.second >> lognumbytes) % numsets);
        }
    }

    void read(ll address)
    {
        int index = (address >> lognumbytes) % numsets;
        ll tag = address >> (lognumbytes + (int)log2(numsets));
        for (int i = 0; i < numblocks; i++)
        {
            if (data[index][i].tag == tag && data[index][i].valid)
            {
                load_hits++;
                total_cycles += hit_time;
                // writeAns("load hit");
                return;
            }
        }
        load_misses++;
        // writeAns("load miss");
        total_cycles += hit_time + miss_penalty;
        replace(address);
    }

    void write_through(ll address)
    {
        int index = (address >> lognumbytes) % numsets;
        ll tag = address >> (lognumbytes + (int)log2(numsets));
        for (int i = 0; i < numblocks; i++)
        {
            if (data[index][i].tag == tag && data[index][i].valid)
            {
                store_hits++;
                // writeAns("store hit");
                total_cycles += hit_time + miss_penalty;
                return;
            }
        }
        store_misses++;
        // writeAns("store miss");
        total_cycles += hit_time + miss_penalty;
        if (allocate == "yes")
        {
            total_cycles += miss_penalty;
            replace(address);
        }
    }

    void write_back(ll address)
    {
        int index = (address >> lognumbytes) % numsets;
        ll tag = address >> (lognumbytes + (int)log2(numsets));
        for (int i = 0; i < numblocks; i++)
        {
            if (data[index][i].tag == tag && data[index][i].valid)
            {
                store_hits++;
                // writeAns("store hit");
                total_cycles += hit_time;
                data[index][i].dirty = true;
                return;
            }
        }
        store_misses++;
        // writeAns("store miss");
        total_cycles += hit_time + miss_penalty;
        if (allocate == "yes")
        {
            total_cycles += miss_penalty;
            replace(address);
            for (int i = 0; i < numblocks; i++)
            {
                if (data[index][i].tag == tag && data[index][i].valid)
                {
                    data[index][i].dirty = true;
                    return;
                }
            }
        }
    }

    void replace(ll address)
    {
        int index = (address >> lognumbytes) % numsets;
        ll tag = address >> (lognumbytes + (int)log2(numsets));
        Block b = Block(numwords);
        b.create(address, tag, numwords);
        if (replacement == "lru")
        {
            // cout << lru[index].size() << endl;
            if (address_present[index][address] == 1)
            {
                address_present[index][address] = 0;
                auto itr = lru[index].find({addr_to_time[index][address], address});
                lru[index].erase(itr);
            }
            if (lru[index].size() >= numblocks)
            {
                // cout << "here" << endl;
                pair<int, ll> to_be_removed = (*(lru[index].begin()));
                ll replace_addr = to_be_removed.second;

                lru[index].erase(lru[index].begin());
                address_present[index][replace_addr] = 0;

                for (int i = 0; i < numblocks; i++)
                {
                    if (data[index][i].tag == tag && data[index][i].valid)
                    {
                        bool dirt = data[index][i].dirty;
                        replace_index[index] = i;
                        total_cycles += (dirt == true ? miss_penalty : 0);
                        if (dirt)
                            data[index][i].dirty = false;
                        break;
                    }
                }
            }
            addr_to_time[index][address] = total_cycles;
            address_present[index][address] = 1;
            lru[index].insert({addr_to_time[index][address], address});

            data[index][replace_index[index]] = b;
            if (lru[index].size() < numblocks)
                replace_index[index]++;




            // if(nodes[index].find(address) != nodes[index].end())
            //     lru_dll[index].erase(nodes[index][address]);
            // // cout << lru_dll[index].size() << endl;
            // if(lru_dll[index].size() >= numblocks)
            // {
            //     replace_index[index] = lru_dll[index].front().second;
            //     lru_dll[index].pop_front();
            //     nodes[index].erase(lru_dll[index].front().second);

            //     bool dirt = data[index][replace_index[index]].dirty;
            //     total_cycles += (dirt == true ? miss_penalty : 0);
            //     if (dirt)
            //         data[index][replace_index[index]].dirty = false;
            // }
            // lru_dll[index].push_back(make_pair(replace_index[index], address));
            // nodes[index][address] = --lru_dll[index].end();
            // data[index][replace_index[index]] = b;

            // if (lru_dll[index].size() < numblocks)
            //     replace_index[index]++;
            // cout << replace_index[index] << endl;
        }
        else
        {
            if (replace_data[index].size() >= numblocks)
            {
                Block old = replace_data[index].front().second;
                replace_index[index] = replace_data[index].front().first;
                replace_data[index].pop();
                bool dirt = data[index][replace_index[index]].dirty;
                total_cycles += (dirt == true ? miss_penalty : 0);
                if (dirt)
                    data[index][replace_index[index]].dirty = false;
                // cout << "here " << index << ' ' << replace_index[index] << endl;
            }
            // cout << "Index " << index << " After read " << address << " " << replace_index[index] << endl;
            replace_data[index].push(make_pair(replace_index[index], b));
            data[index][replace_index[index]] = b;
            // cout << b.words[0] << " " << b.words[1] << " " << b.words[2] << " " << b.words[3] << endl;
            if (replace_data[index].size() < numblocks)
                replace_index[index]++;
            // cout << "here " << index << ' ' << replace_index[index] << endl;
        }
    }

    void writeAns(string text)
    {
        ofstream f;
        f.open("myans.txt", std::ios::app);
        f << text << endl;
        f.close();
    }

    void printStats()
    {
        cout << "Total loads: " << total_loads << endl;
        cout << "Total stores: " << total_stores << endl;
        cout << "Load hits: " << load_hits << endl;
        cout << "Load misses: " << load_misses << endl;
        cout << "Store hits: " << store_hits << endl;
        cout << "Store misses: " << store_misses << endl;
        cout << "Total cycles: " << total_cycles << endl;
    }

    void printData()
    {
        for (int i = 0; i < numsets; i++)
        {
            cout << "Set " << i << ": " << endl;
            for (int j = 0; j < numblocks; j++)
            {
                cout << "Block " << j << ": ";
                for (int k = 0; k < numwords; k++)
                    cout << data[i][j].words[k] << " ";
                cout << endl;
            }
        }
    }

    void printSet(int index)
    {
        cout << "Set " << index << ": " << total_loads + total_stores << endl;
        for (int j = 0; j < numblocks; j++)
        {
            cout << "Block " << j << ": ";
            for (int k = 0; k < numwords; k++)
            {
                cout << data[index][j].words[k] << " ";
            }
            cout << "dirty: " << data[index][j].dirty << ' ';
            cout << endl;
        }
    }
};

vector<pair<char, ll>> read_file(string filename)
{
    ifstream file;
    file.open(filename);
    vector<pair<char, ll>> instructions;
    char type;
    ll address;
    int ignore;
    stringstream ss;
    string line;
    while (getline(file, line))
    {
        ss << line;
        ss >> type >> hex >> address >> ignore;
        instructions.push_back({type, address});
        ss.clear();
    }
    return instructions;
}

void printVect(vector<pair<char, ll>> v)
{
    int n = v.size();
    for (int i = 0; i < n; ++i)
        cout << v[i].first << " " << v[i].second << endl;
}

int main(int argc, char *argv[])
{
    // cout << "hello" << endl;
    int numsets = stoi(argv[1]);
    int numblocks = stoi(argv[2]);
    int numbytes = stoi(argv[3]);
    string allocate = argv[4];
    string write = argv[5];
    string replacement = argv[6];
    string filename = argv[7];

    // cout << numsets << endl;
    // cout << numblocks << endl;
    // cout << numbytes << endl;
    // cout << filename << endl;

    vector<pair<char, ll>> instructions = read_file(filename);
    Cache c = Cache(numsets, numblocks, numbytes / 4, allocate, write, replacement);
    // for(int x : c.replace_index)
    //     cout << x << " ";
    c.operate(instructions);
    // for(int x : c.replace_index)
    //     cout << x << " ";
    c.printStats();
    // c.printData();
    // printVect(instructions);
    return 0;
}