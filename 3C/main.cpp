#include <bits/stdc++.h>
#include <chrono>
using namespace std;

void clearMatrix(int **M, int n)
{
    for (int i = 0; i < n; ++i)
    {
        delete[] M[i];
    }
    delete[] M;
}

void inPlaceMatrixTranspose(int *A, int n, int type)
{
    if (type == 1)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = i+1; j < n; ++j)
            {
                swap(A[i*n+j], A[j*n+i]);
            }
        }
    }
    else
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = j+1; i < n; ++i)
            {
                swap(A[i*n+j], A[j*n+i]);
            }
        }
    }
}

void outPlaceMatrixTranspose(int *A, int *B, int n, int type)
{
    if (type == 1)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                B[j*n+i] = A[i*n+j];
            }
        }
    }
    else
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                B[j*n+i] = A[i*n+j];
            }
        }
    }
}

void multiplyMatrix(int *A, int *B, int *C, int n, int type)
{
    if (type == 1)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int k = 0; k < n; ++k)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < n; ++k)
            {
                for (int j = 0; j < n; ++j)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else if (type == 3)
    {
        for (int k = 0; k < n; ++k)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int i = 0; i < n; ++i)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else if (type == 4)
    {
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else if (type == 5)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                for (int i = 0; i < n; ++i)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
    else
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int k = 0; k < n; ++k)
                {
                    C[i * n + j] += A[i * n + k] * B[k * n + j];
                }
            }
        }
    }
}

int main()
{
    int N = 40, ctr = 5, sz = 32*N;
    vector<vector<long double>> multiplytime(N, vector<long double>(6, 0));
    vector<vector<long double>> inplaceTransposetime(N, vector<long double>(2, 0));
    vector<vector<long double>> outplaceTransposetime(N, vector<long double>(2, 0));
    int *A = new int[sz*sz];
    int *B = new int[sz*sz];
    int *C = new int[sz*sz];
    for (int itr = 1; itr <= ctr; ++itr)
    {
        for (int n = 32; n <= 32*N; n += 32)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    A[i * n + j] = rand() % 1000;
                    B[i * n + j] = rand() % 1000;
                }
            }
            for (int type = 1; type <= 6; ++type)
            {
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        C[i * n + j] = 0;
                    }
                }
                auto start = chrono::high_resolution_clock::now();
                multiplyMatrix(A, B, C, n, type);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                multiplytime[(n/32)-1][type - 1] += duration.count() + 0.0;
            }
            for(int type = 1; type <= 2 ; ++type)
            {
                auto start = chrono::high_resolution_clock::now();
                outPlaceMatrixTranspose(A, B, n, type);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                outplaceTransposetime[(n/32)-1][type-1] += duration.count() + 0.0;
            }
            for(int type = 1; type <= 2 ; ++type)
            {
                auto start = chrono::high_resolution_clock::now();
                inPlaceMatrixTranspose(A, n, type);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                inplaceTransposetime[(n/32)-1][type-1] += duration.count() + 0.0;
            }
            cout << "Size " << n << " done\n";
        }
        cout << "Iteration " << itr << " done\n";
    }
    delete[] A;
    delete[] B;
    delete[] C;
    ofstream file;
    file.open("output.csv");
    file << "Size,ijk,ikj,kji,kij,jki,jik,in_ij,in_ji,out_ij,out_ji" << endl;
    for (int i = 0; i < N; i++)
    {
        file << i + 1;
        for (int type = 0; type < 6; ++type)
        {
            multiplytime[i][type] /= ctr;
            file << "," << multiplytime[i][type];
        }
        for(int type = 0; type < 2 ; ++type)
        {
            inplaceTransposetime[i][type] /= ctr;
            file << "," << inplaceTransposetime[i][type];
        }
        for(int type = 0; type < 2 ; ++type)
        {
            outplaceTransposetime[i][type] /= ctr;
            file << "," << outplaceTransposetime[i][type];
        }
        file << endl;
    }
    return 0;
}