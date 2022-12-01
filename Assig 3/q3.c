// multiply two matrices of size 3x3 by 9 threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a[3][3];
int b[3][3];
int c[3][3];

void* multiply(void* arg){
    int* data = (int*)arg;
    int i = data[0];
    int j = data[1];
    for(int k = 0; k < 3; k++){
        c[i][j] += a[i][k] * b[k][j];
    }
    return NULL;
}

int main(){

    // input arrays
    printf("Enter the elements of the first matrix: \n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    printf("Enter the elements of the second matrix: \n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("b[%d][%d] = ", i, j);
            scanf("%d", &b[i][j]);
        }
    }
    
    // create 9 threads
    pthread_t threads[9];
    int count = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            int* data = (int*)malloc(2 * sizeof(int));
            data[0] = i;
            data[1] = j;
            pthread_create(&threads[count], NULL, multiply, data);
            count++;
        }
    }
    for(int i = 0; i < 9; i++){
        pthread_join(threads[i], NULL);
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}