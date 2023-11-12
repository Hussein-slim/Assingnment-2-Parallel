#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int n, m, k;
int **matrix1, **matrix2, **ans;

void multiplyMatrices() {
    for (int o = 0; o < m; o++) {
        for (int z = 0; z < k; z++) {
            for (int i = 0; i < n; i++) {
                ans[o][z] += matrix1[o][i] * matrix2[i][z];
            }
        }
    }
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
    if (argc != 4) {
        printf("Usage: %s <m> <n> <k>\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    k = atoi(argv[3]);

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

    multiplyMatrices();

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
