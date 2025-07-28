#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

#define MAX_WORD_SIZE 50
#define MAX_GUESS_SIZE 2

void get_random_word_from_file(char *buffer, int buffer_size){

    FILE *file = fopen("/home/hofacker/Documents/Projetos/C/hangman/assets/hangmanWords.txt", "r");

    if (!file){

        printf("UNABLE TO OPEN FILE! MAY NOT EXIST!\n");
    }else{

        srand((unsigned int)time(NULL));
        int random_line_number = rand() % 11;
        
        int i = 0;
        while(i < random_line_number){

            fgets(buffer, buffer_size, file);
            i += 1;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        fclose(file);
    }

}

void hide_selected_word(char *word, char **hidden_word_str, size_t *actual_word_size){

    *actual_word_size = strlen(word);
    *hidden_word_str = malloc(*actual_word_size + 1);
    (*hidden_word_str)[*actual_word_size] = '\0';
    
    for (size_t i = 0; i != *actual_word_size; i++) {
        
        (*hidden_word_str)[i] = '_';
    }
}

//Cleans up garbage left in stdin;
void cleanup_stdin(char *guess){

    char a;

    if(guess[1] != '\n'){

        a = getchar();
        while (a != '\n')
            a = getchar();
    }
}

int validade_user_input(char *guess){

    char *alfabet = "abcdefghijklmnopqrstuvwxyz";
    int alfabet_size = 27;

    if(*guess != ' ' && *guess != '\n'){

        for(int i = 0; i < alfabet_size; i++){

            if(*guess == alfabet[i]){

                return 0;
            }
        }
    }

    printf("ENTRY IS NOT A LETTER. TRY AGAIN!\n\n");
    return 1;
}

void make_guess(char *used_characters, char *hidden_word, char *word, size_t *actual_word_size){

    char *guess = malloc(2);
    int validated = 1;

    while(validated == 1){

        printf("Input Your Guess: ");
        fgets(guess, 2, stdin);
        validated = validade_user_input(guess);
        cleanup_stdin(guess);
    }

    for (size_t i = 0; i <= *actual_word_size - 1; i++){
        
        if(*guess == word[i]){

            hidden_word[i] = *guess;
        }

    }

    free(guess);
}

int main(){

    char *word = malloc(MAX_WORD_SIZE);
    char *hidden_word = 0;
    size_t *actual_word_size = malloc(sizeof(int));
    actual_word_size;
    char used_characters[27];
    int lives = 7;


    get_random_word_from_file(word, MAX_WORD_SIZE);
    hide_selected_word(word, &hidden_word, actual_word_size);
    make_guess(used_characters, hidden_word, word, actual_word_size);
    printf("%s\n", hidden_word);
    printf("%s\n", word);

    free(word);
    free(hidden_word);
    free(actual_word_size);

    return 0;
}