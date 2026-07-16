#include <stdio.h>
#include <stdlib.h>

int main() {
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    int **matrix = (int **)malloc(n * sizeof(int *));
    int i,j,sum;
    for(i = 0; i < n; i++) {
        matrix[i] = (int *)malloc((m+1) * sizeof(int));
        sum = 0;
        for(j = 1; j < m+1; j++) {
            scanf("%d", (*matrix+i)+j);
            sum += *((*matrix+i)+j);
        }
        *((*matrix+i)+0) = sum;
    }

    for (i = 0; i < n; i++) {
        if (matrix[i][0] < m*k) {
            free(matrix[i]);
            for (j = i; j < n-1; j++) {
                matrix[j] = matrix[j+1];
            }
            n--;
        }
    }

    printf("%d\n", n);
    if (n == 0) printf("EMPTY\n");
    else {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m+1; j++) {
                printf("%d ", *((*matrix+i)+j));
            }
            printf("\n");
        }
    }

    for (i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}