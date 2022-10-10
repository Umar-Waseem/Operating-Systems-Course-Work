#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // read from a pipe that is made in file consumerProducer.c
    
    // read from pipe
    char c;
    printf("\x1b[31m\nReading from producerConsumer.c: \x1b[0m \n\n");
    // count number of characters, words and lines
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;
    
    while (read(0, &c, 1) > 0)
    {
        // count number of characters
        charCount++;
        
        // count number of words
        if (c == ' ' || c == '\n')
        {
            wordCount++;
        }
        
        // count number of lines
        if (c == '\n' || c == '\0')
        {
            ++lineCount;
        }
        
        // print to console
        printf("%c", c);
    }
    ++lineCount;
    
    printf("\n\nLine count: %d\n", lineCount);
    printf("Word count: %d\n", wordCount);
    printf("Char count: %d\n", charCount);

    // write to a file
    FILE *fp = fopen("theCount.txt", "w");
    fprintf(fp, "Number Of Lines: %d \n", lineCount);
    fprintf(fp, "Number Of Words: %d \n", wordCount);
    fprintf(fp, "Number Of Chars: %d \n", charCount);

    
    
    return 0;
}
