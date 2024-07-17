#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <pthread.h>
#include <atomic>

using namespace std;

#define MAX_ROWS 2048
#define MAX_COLS 2048

int N;
int K;
atomic<int> counter(0); // shared counter C
int rowInc;

int **matrixA;
int **matrixC;

void increment(atomic<int> *v)
{
    int temp;
    do
    {
        temp = v->load();
    } while (!v->compare_exchange_weak(temp, temp + rowInc));
}

void *matmul(void *arg)
{
    while (counter < N)
    {
        int start = counter;
        increment(&counter);
        int end = counter;

        // Check if all rows have been processed
        if (start >= N)
            break;

        // Perform matrix multiplication for the assigned rows
        for (int i = start; (i < end) && (i < N); i++)
        {
            for (int j = 0; j < N; j++)
            {
                int s = 0;

                for (int k = 0; k < N; k++)
                {
                    s += matrixA[i][k] * matrixA[k][j];
                }

                matrixC[i][j] = s;
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    // Variable for measuring execution time
    clock_t start_time, end_time;

    // File handling: Open input file
    ifstream input("matrix.txt");

    // Check if the file opening was successful
    if (!input.is_open())
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Read matrix size (N) and number of threads (K) from the input file
    input >> N >> K >> rowInc;

    // Allocate memory for input matrix (matrixA)
    matrixA = new int *[N];
    for (int i = 0; i < N; i++)
        matrixA[i] = new int[N];

    // Allocate memory for the output matrix (matrixC)
    matrixC = new int *[N];
    for (int i = 0; i < N; i++)
        matrixC[i] = new int[N];

    // Read matrix values from the input file
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            input >> matrixA[i][j];
        }
    }

    // Close the input file
    input.close();

    // Initialize clock for measuring execution time
    start_time = clock();

    // Arrays to store thread identifiers
    pthread_t threadIds[K];
    int threadID[K];

    // Create threads to perform matrix multiplication
    for (int i = 0; i < K; ++i)
    {
        threadID[i] = i;
        // Create thread
        pthread_create(&threadIds[i], NULL, matmul, (void *)&threadID[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < K; ++i)
    {
        pthread_join(threadIds[i], NULL);
    }

    // File handling: Open output file
    ofstream output("out2.txt");

    // Write the result matrix to the output file
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            output << matrixC[i][j] << " ";
        }

        output << "\n";
    }

    // Free allocated memory for matrices
    for (int i = 0; i < N; i++)
    {
        delete[] matrixA[i];
        delete[] matrixC[i];
    }
    delete[] matrixA;
    delete[] matrixC;

    // Measure execution time and print it to the output file
    end_time = clock();
    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    output << "\ntime taken by code: " << total_time << " seconds\n";

    // Close the output file
    output.close();

    cout << "time taken to execute:" << total_time << "seconds" << endl;

    return 0;
}
