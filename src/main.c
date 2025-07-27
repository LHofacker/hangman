#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void get_word_from_file(char *buffer, int buffer_size){

    FILE *file = fopen("/home/hofacker/Documents/Projetos/C/hangman/assets/hangmanWords.txt", "r");

    if (!file){

        printf("UNABLE TO OPEN FILE! MAY NOT EXIST.\n");
    }else{

        int random_line_number = rand() % 10;
        int i = 0;
        
        while(i < random_line_number){

            fgets(buffer, buffer_size, file);
            i += 1;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        fclose(file);
    }

}

int main(){

    size_t buffer_size = 50;
    char *buffer = malloc(buffer_size);

    get_word_from_file(buffer, buffer_size);

    printf("%s\n", buffer);

    return 0;
}