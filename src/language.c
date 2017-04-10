#include <stdio.h>
#include <string.h>

int read_rus() 
{
    return 1;
}

int read_eng() 
{
    return 1;
}

int main()
{

	FILE *in = fopen("rus-eng.txt", "rt");
    char il;


    if(!in){
        perror("error");
        return -1;
    }
    while(1) {
        fscanf(in,"%c", &il);
        printf("%zu ", il);
        if(il == '\n') {
            break;
        } else {

        }
    }
    fclose(in);
    return 0;
}