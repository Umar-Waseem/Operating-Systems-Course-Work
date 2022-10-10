#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    
    // open editSource.txt file
    FILE *fp = fopen("editSource.txt", "r");
    
    // read from editSource.txt and write to pipe
    pipe(fd);
    int pid = fork();
    if (pid == 0)
    {
        // child process
        close(fd[0]);
        char c;
        printf("\x1b[33m\nWriting from Child process in consumerProducer.c: \n");
        while ((c = fgetc(fp)) != EOF)
        {
            write(fd[1], &c, 1);
        }
        close(fd[1]);
    }
    else
    {
        // read pipe using exec in file producerConsumer.c
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        system("gcc -o producerConsumer producerConsumer.c");
        execlp("./producerConsumer", "producerConsumer", NULL);
        
        // wait for child process to finish
        wait(NULL);
        
        // close file
        fclose(fp);
        
    }
    

    
    
    return 0;
}
