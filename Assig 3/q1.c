
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count[26];

// a function that will be executed by the thread and takes a void pointer as an argument and cast to character and searches for that character in a file and counts the number of times it appears

void* charCount(void* arg){
    // cast arg to char
    char c = *(char*)arg;
    // open file
    FILE* fp = fopen("file.txt", "r");
    // check if file is opened
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }
    // read file
    char ch;
    while((ch = fgetc(fp)) != EOF){
        if(ch == c){
            count[c - 'a']++;
        }
    }
    // close file
    fclose(fp);
    return NULL;
} 

int main(){
    // create an array of 26 threads
    pthread_t threads[26];
    // create an array of 26 characters
    char chars[26];
    // create an array of 26 integers
    int i[26];
    // create 26 threads
    for(int j = 0; j < 26; j++){
        // assign a character to each thread
        chars[j] = 'a' + j;
        // assign an integer to each thread
        i[j] = j;
        // create a thread
        pthread_create(&threads[j], NULL, charCount, &chars[j]);
    }
    // join 26 threads
    for(int j = 0; j < 26; j++){
        pthread_join(threads[j], NULL);
    }
    // print the number of times each character appears in the file
    for(int j = 0; j < 26; j++){
        printf("%c: %d times in file.txt \n", 'a' + j, count[j]);
    }
    return 0;
}