#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <pthread.h>

pthread_mutex_t mutex1;




void* mergeSort(void* arg){
    printf("Hello from thread %d \n   ", *(int*)arg);

    // mutex
    pthread_mutex_lock(&mutex1);

    int* arr = (int*)arg;
    int n = sizeof(arr) / sizeof(arr[0]);
    if(n > 1){
        int mid = n / 2;
        int left[mid];
        int right[n - mid];
        for(int i = 0; i < mid; i++){
            left[i] = arr[i];
        }
        for(int i = mid; i < n; i++){
            right[i - mid] = arr[i];
        }
        mergeSort(left);
        mergeSort(right);
        int i = 0;
        int j = 0;
        int k = 0;
        while(i < mid && j < n - mid){
            if(left[i] < right[j]){
                arr[k] = left[i];
                i++;
            }
            else{
                arr[k] = right[j];
                j++;
            }
            k++;
        }
        while(i < mid){
            arr[k] = left[i];
            i++;
            k++;
        }
        while(j < n - mid){
            arr[k] = right[j];
            j++;
            k++;
        }
    }
    // exit the thread
    pthread_mutex_unlock(&mutex1);
    pthread_exit(0);

    // mutex
    return NULL;
}
//   https://simplesnippets.tech/merge-sort-algorithm-with-example-with-c-code-sorting-algorithms-data-structures/
int main(int argc, _TCHAR *argv[])
{
    // initialize mutex
    pthread_mutex_init(&mutex1, NULL);
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int numCPU = sysinfo.dwNumberOfProcessors;
    printf("Number of processors: %d\n", numCPU);

    printf("Mac address: ");
    system("getmac ");

    // input array from user
    int arr[10];
    printf("Enter 10 numbers: ");
    for(int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }

    // create threads equal to number of processors and merge sort the array using threads
    pthread_t threads[numCPU];
    for(int i = 0; i < numCPU; i++){
        pthread_create(&threads[i], NULL, mergeSort, &arr[i]);
    }

    // join threads
    for(int i = 0; i < numCPU; i++){
        pthread_join(threads[i], NULL);
    }

    // print sorted array
    printf("Sorted array: ");
    for(int i = 0; i < 8; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    // destroy mutex
    pthread_mutex_destroy(&mutex1);

    return 0;

}