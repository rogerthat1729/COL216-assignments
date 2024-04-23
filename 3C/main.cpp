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

// void inPlaceMatrixTranspose(int **A, int n, int type)
// {
//     if (type == 1)
//     {
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 swap(A[i][j], A[j][i]);
//             }
//         }
//     }
//     else
//     {
//         for (int j = 0; j < n; ++j)
//         {
//             for (int i = j + 1; i < n; ++i)
//             {
//                 swap(A[i][j], A[j][i]);
//             }
//         }
//     }
// }

// void outPlaceMatrixTranspose(int **A, int **B, int n, int type)
// {
//     if (type == 1)
//     {
//         for (int i = 0; i < n; ++i)
//         {
//             for (int j = i + 1; j < n; ++j)
//             {
//                 B[j][i] = A[i][j];
//             }
//         }
//     }
//     else
//     {
//         for (int j = 0; j < n; ++j)
//         {
//             for (int i = j + 1; i < n; ++i)
//             {
//                 B[j][i] = A[i][j];
//             }
//         }
//     }
// }

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

// void inPlaceTranspose(int* A, int n)
// {
//     for(int i = 0 ; i < n ; ++i)
//     {
//         for(int j = i+1 ; j < n ; ++j)
//         {
//             swap(A[i*n+j], A[j*n+i]);
//         }
//     }
// }

// void outPlaceTranspose(int* A, int* B, int n)
// {
//     for(int i = 0 ; i < n ; ++i)
//     {
//         for(int j = 0 ; j < n ; ++j)
//         {
//             B[j*n+i] = A[i*n+j];
//         }
//     }
// }

// void multiplyMatrix(int *A, int *B, int *C, int n)
// {
//     for (int i = 0; i < n; ++i)
//     {
//         for (int j = 0; j < n; ++j)
//         {
//             C[i * n + j] = 0;
//             for (int k = 0; k < n; ++k)
//                 C[i * n + j] += A[i * n + k] * B[k * n + j];
//         }
//     }
// }

int main()
{
    int N = 1200, ctr = 5;
    vector<vector<long double>> multiplytime(N, vector<long double>(6, 0));
    vector<long double> inplaceTransposetime(N, 0);
    vector<long double> outplaceTransposetime(N, 0);
    int *A = new int[N * N];
    int *B = new int[N * N];
    int *C = new int[N * N];
    for (int itr = 1; itr <= ctr; ++itr)
    {
        for (int n = 16; n <= N; n += 16)
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
                auto start = chrono::high_resolution_clock::now();
                multiplyMatrix(A, B, C, n, type);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                multiplytime[n - 1][type - 1] += duration.count() + 0.0;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        C[i * n + j] = 0;
                    }
                }
            }

            // auto start1 = chrono::high_resolution_clock::now();
            // inPlaceTranspose(A, n);
            // auto stop1 = chrono::high_resolution_clock::now();
            // auto duration1 = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
            // inplaceTransposetime[n-1] += duration1.count() + 0.0;

            // auto start2 = chrono::high_resolution_clock::now();
            // outPlaceTranspose(A, B, n);
            // auto stop2 = chrono::high_resolution_clock::now();
            // auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
            // outplaceTransposetime[n-1] += duration2.count() + 0.0;
            // cout << "Type " << p << ", size " << n << ": " << duration.count() << " microseconds" << endl;
            // cout << "Size " << n << ": " << total/6 << " microseconds" << endl;
            // for(int p = 1; p <= 2; ++p)
            // {
            //     auto start = chrono::high_resolution_clock::now();
            //     inPlaceMatrixTranspose(A, n, p);
            //     auto stop = chrono::high_resolution_clock::now();
            //     auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            //     cout << "In-place transpose type " << p << ", size " << n << ": " << duration.count() << " microseconds" << endl;
            // }
            // for(int p = 1 ; p <= 2 ; ++p)
            // {
            //     for(int i = 0 ; i < n ; ++i)
            //     {
            //         for(int j = 0 ; j < n ; ++j)
            //         {
            //             B[i][j] = 0;
            //         }
            //     }
            //     auto start = chrono::high_resolution_clock::now();
            //     outPlaceMatrixTranspose(A, B, n, p);
            //     auto stop = chrono::high_resolution_clock::now();
            //     auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            //     cout << "Out-place transpose type " << p << ", size " << n << ": " << duration.count() << " microseconds" << endl;
            // }
            cout << "Size " << n << " done\n";
        }
        cout << "Iteration " << itr << " done\n";
    }
    delete[] A;
    delete[] B;
    delete[] C;
    ofstream file;
    file.open("output.csv");
    file << "Size,MultiplyTime(in microsec),InPlaceTransposeTime,OutPlaceTransposeTime" << endl;
    for (int i = 15; i < N; i += 16)
    {
        file << i + 1;
        for (int type = 0; type < 6; ++type)
        {
            multiplytime[i][type] /= ctr;
            // inplaceTransposetime[i] /= ctr;
            // outplaceTransposetime[i] /= ctr;
            file << "," << multiplytime[i][type];
        }
        file << endl;
    }
    return 0;
}