#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define RESULT_ERROR (-1)

long getfilesize1(char *filename){
    struct stat file_status; // The stat() function returns information about a file
    if(stat(filename, &file_status)<0){ 
        return RESULT_ERROR;
    }
    return file_status.st_size;
}

long getfilesize2(char *filename){
    FILE *f = fopen(filename, "r");

    if(f == NULL){
        return RESULT_ERROR;
    }
    if(fseek(f, 0, SEEK_END)<0){ // fseek used to move or change the position of the file pointer to a specified offset ie
        fclose(f);
        return RESULT_ERROR;
    }
    long length = ftell(f);
    fclose(f);
    return length;
}

int main(int argc, char **argv){

    if(argc < 2){
        printf("usage : %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    printf("%s:\t%ld\t%ld\n",filename, getfilesize1(filename),getfilesize2(filename));
}