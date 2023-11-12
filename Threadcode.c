#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int n, m, k;
int numofthreads;
int **matrix1, **matrix2, **ans;
pthread_mutex_t mutex;

void *runner(void *arg) {
    int tid = *(int *)arg;
    int chunk_size = m / numofthreads;
    int start = tid * chunk_size;
    int end = (tid == numofthreads - 1) ? m : (tid + 1) * chunk_size;

    for (int o = start; o < end; o++) {
        for (int z = 0; z < k; z++) {
            for (int i = 0; i < n; i++) {
                ans[o][z] += matrix1[o][i] * matrix2[i][z];
            }
        }
    }
    free(arg); // Free the allocated memory for the thread ID
}

void printMatrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: %s <m> <n> <k> <numofthreads>\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    k = atoi(argv[3]);
    numofthreads = atoi(argv[4]);

    matrix1 = (int **)malloc(m * sizeof(int *));
    matrix2 = (int **)malloc(n * sizeof(int *));
    ans = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; ++i) {
        matrix1[i] = (int *)malloc(n * sizeof(int));
        ans[i] = (int *)malloc(k * sizeof(int));
    }
    for (int i = 0; i < n; ++i) {
        matrix2[i] = (int *)malloc(k * sizeof(int));
    }

    pthread_t threads[numofthreads];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix1[i][j] = rand() % 100 + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            matrix2[i][j] = rand() % 100 + 1;
        }
    }

    // Start the timer
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < numofthreads; i++) {
        int *tid = (int *)malloc(sizeof(int));
        *tid = i;
        pthread_create(&threads[i], NULL, runner, (void *)tid);
    }

    for (int i = 0; i < numofthreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Stop the timer
    gettimeofday(&end_time, NULL);

    double execution_time = (double)(end_time.tv_sec - start_time.tv_sec) +
                           (double)(end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Matrix 1:\n");
    printMatrix(matrix1, m, n);

    printf("Matrix 2:\n");
    printMatrix(matrix2, n, k);

    printf("Result Matrix:\n");
    printMatrix(ans, m, k);

    printf("Matrix Multiplication Time: %lf seconds\n", execution_time);

    // Free allocated memory
    for (int i = 0; i < m; i++) {
        free(matrix1[i]);
        free(ans[i]);
    }
    free(matrix1);
    free(matrix2);
    free(ans);

    return 0;
}
