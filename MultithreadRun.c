/***************************************
@Author: Yuan Zhuang
****************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND 200
#define MAX_THREAD 36
#define MAX_OUTPUTPREFIX 100

int main(int argc, char* argv[]){
    int nTasks = 5;
    int i = 0;
    char runIdx[10];
    void *runCommand(void* command);
    char command[MAX_THREAD][MAX_COMMAND];
    char outputPrefix[MAX_OUTPUTPREFIX];
    pthread_t *tid = malloc(nTasks*sizeof(pthread_t));

    if(argc==1){
        fprintf(stderr,"Missing input parameter\n");
        exit(EXIT_FAILURE);
    }
    else if(argc==2){
        nTasks = 8;
        strcpy(outputPrefix, " >> output_");
    }
    else if(argc==3)
        strcpy(outputPrefix, " >> output_");
    else{
        nTasks = atoi(argv[2]);
        if(nTasks<1){
            fprintf(stderr,"Invalid number of tasks\n");
            exit(EXIT_FAILURE);
        }
        else if(nTasks>MAX_THREAD){
            fprintf(stderr,"Exceed max number of threads\n");
            exit(EXIT_FAILURE);
        }
        strcpy(outputPrefix, " >> ");
        strcat(outputPrefix, argv[3]);
    }
    if(2+strlen(argv[1])+1+1+strlen(argv[2])+4+strlen(argv[3])+1+strlen(argv[2])>MAX_COMMAND){
        fprintf(stderr,"Exceed max number of characters in the input, please either increase MAX_COMMAND or reduce the number of inputs.\n");
        exit(EXIT_FAILURE);
    }
        
        
        
    if(tid==NULL){
        fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<nTasks;i++){
        strcpy(command[i], "./");
        strcat(command[i], argv[1]);
        strcat(command[i], " ");
        sprintf(runIdx,"%d ", i);
        strcat(command[i], runIdx);
        strcat(command[i], outputPrefix);
        strcat(command[i], runIdx);
        if(pthread_create(&tid[i], NULL, runCommand, (void*)command[i])!=0){
            fprintf(stderr,"Error in allocating threads\n");
            exit(EXIT_FAILURE);
        }
    }
    for(i=0;i<nTasks;i++){
        pthread_join(tid[i], NULL);
    }
    return 0;
}

void* runCommand(void* command){
    system((char*)command);
    pthread_exit(0);
}
