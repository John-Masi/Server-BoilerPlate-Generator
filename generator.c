#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

// NOTES;
// fopen() -opens file creates a pointer to the file struct
// fread() - returns a number of bytes that it has found from the file
// fwrite() -

#define FILE_NAMES 2

void dynamicRead(){

}

int fileLen(FILE *f){
    f = fopen("file_name.txt","r");
    int count = 1;
    int c;

    char *buff = NULL;
    size_t len = 0;
    ssize_t bytes;
    while((c = fgetc(f)) != EOF){
        if(c == '\n'){
            count = count + 1;
        }
    }
    free(buff);
    fclose(f);
    return count;
}

void populateFileDesc(char *name,char *fd[10]){
    FILE *file_name = fopen(name,"rb");

    int length = fileLen(file_name);
    char *buff = NULL;
    size_t len = 0;
    ssize_t bytes; 
    
    for(int i = 0; i < length; i++){
        bytes = getline(&buff,&len,file_name);
        fd[i] = strdup(buff);
        printf("%s",fd[i]);
        
    }
    fclose(file_name);
    free(buff);

}

void* create(void* args){

    FILE *readFile = fopen("boiler_plate.txt","r");
    int count = 1;
    char **f = (char **)args;

    char *buffer =  NULL;
    size_t len = 0; // Dyanmically creating an array len will be the size of it 
    ssize_t new_buff; // size of data going to the new file 

    for(int i = 0; i < 2; i++){
        FILE *writeFile = fopen(strdup(f[i]),"w");
        count++;
        while((new_buff = getline(&buffer,&len,readFile)) > 0){
            fwrite(buffer,1,new_buff,writeFile); // Writing from buffer to the new file with a size of new_buff 
            printf(": %s\n",buffer);
        }
        
        fclose(writeFile);
        rewind(readFile);
    }
    free(buffer);
    fclose(readFile);

    pthread_exit(NULL);
    return NULL;

}

int main() {
    char *f[10];
    populateFileDesc("file_name.txt",f);

    pthread_t p;
    pthread_create(&p,NULL,create(f),NULL);
    pthread_join(p,NULL);

    return 0;
}
