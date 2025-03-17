#include <stdio.h>
#include <stdlib.h>

int count_numbers(const char *filename){
    FileIN *FileIN=fopen(filename, "r");
    if(!FileIN){
        perror("InERR");
        return -1;
    }


    int counter=0;
    char ch;
    int in_number=0;

    while ((ch=fgetc(FileIN))!=EOF) {
        if (ch>='0'&&ch<='9'){
            if (!in_number){
                counter++;
                in_number=1;
            }
        } else {
            in_number=0;
        }
    }
    fclose(FileIN);
    return counter;
}





void write_number(const char *filename,int counter) {
    FileOUT *FileOUT=fopen(filename,"w");
    if (!FileOUT){
        perror("OutERR");
        return;
    }
    fprintf(FileOUT,"%d\n",counter);
    fclose(FileOUT);
}

int main(int argc,char *argv[]){
    if (argc!=3){
        fprintf(stderr,"Usage: %s PATH_IN PATH_OUT\n",argv[0]);
        fprintf(stderr,"or if u wanna to use files in current dir:\n");
        fprintf(stderr,"Usage: %s FileIN FileOUT \n\n");

        return EXIT_FAILURE;
    }

    const char *input_filename=argv[1];
    const char *output_filename=argv[2];

    int number_counter=count_numbers(input_filename);
    if (number_counter==-1){
        return EXIT_FAILURE;
    }
    write_number(output_filename,number_counter);
    printf("numbs: %d\n",number_counter);
    return EXIT_SUCCESS;
}
