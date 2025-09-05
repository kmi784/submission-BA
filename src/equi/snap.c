#include <stdio.h>
#include <stdlib.h>

int main(int arc, char* argv[]){
    
    FILE *fin, *fout;

    int L = atoi(argv[1]);
    fin = fopen(argv[2], "r");
    fout = fopen(argv[3], "w");

    int number;
    
    int index = -1;
    do{
        ++index;
        fscanf(fin, "%d", &number);
    }while(number!=0 && number!=1);

    for(int i = 0; i < L; ++i){
        for(int j = 0; j < L ; ++j){
            fprintf(fout,"%d\t",number);
            fscanf(fin, "%d", &number);
        }
        fprintf(fout, "0\n");
    }

    for(int i = 0; i < L; ++i){
        fprintf(fout,"0\t");
    }
    fprintf(fout, "0\n");

    return 0;
}