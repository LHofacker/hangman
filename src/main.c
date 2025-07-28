#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void get_random_word_from_file(char *buffer, int buffer_size){

    FILE *file = fopen("/home/hofacker/Documents/Projetos/C/hangman/assets/hangmanWords.txt", "r");

    if (!file){

        printf("UNABLE TO OPEN FILE! MAY NOT EXIST!\n");
    }else{

        srand((unsigned int)time(NULL));
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

void hide_selected_word(char *word, char **hidden_word_str){

    size_t word_size = strlen(word);
    *hidden_word_str = malloc(word_size + 1);
    (*hidden_word_str)[word_size] = '\0';
    
    for (size_t i = 0; i != word_size; i++) {
        
        (*hidden_word_str)[i] = '_';
    }
}

int main(){

    const size_t MAX_WORD_SIZE = 50;
    char *word = malloc(MAX_WORD_SIZE);
    char *hidden_word = 0;

    get_random_word_from_file(word, MAX_WORD_SIZE);
    hide_selected_word(word, &hidden_word);

    free(word);
    free(hidden_word);

    return 0;
}