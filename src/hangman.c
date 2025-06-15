#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void input_word(char **ptr_to_word, char **ptr_to_secret){

    *ptr_to_word = malloc(sizeof(char) * 100);

    printf("Insira a palavra para jogar: ");
    scanf("%99s", *ptr_to_word);

    size_t len = strlen(*ptr_to_word);

    *ptr_to_word = realloc(*ptr_to_word, len + 1);
    *ptr_to_secret = malloc(len + 1);
}

void hide_input_word(char *ptr_to_word, char *ptr_to_secret){
    
    size_t len = strlen(ptr_to_word);
    for (int i = 0; i <= len - 1; i++){

        ptr_to_secret[i] = '_';
    }

    ptr_to_secret[len] = '\0';
}

void make_guess(char *ptr_to_word, char *ptr_to_secret, int *lives){

    char *guess = malloc(sizeof(char)+1);
    int hits = 0;
    
    printf("Insira sua tentativa: ");
    scanf(" %c", guess);

    for (int i = 0; i <= strlen(ptr_to_word) - 1; i++){

        if (*guess == ptr_to_word[i]){

            ptr_to_secret[i] = *guess;
            hits++;
        }
    }

    if (hits <= 0){

        *lives = *lives - 1;
    }
}

int main(int argc, char *argv[]){

    char *secret_word, *secret_word_hidden;
    int *lives = malloc(sizeof(int));
    *lives = 7;

    input_word(&secret_word, &secret_word_hidden);
    hide_input_word(secret_word, secret_word_hidden);
    make_guess(secret_word, secret_word_hidden, lives);

    printf("%ld AND %ld\n", strlen(secret_word), strlen(secret_word_hidden));
    printf("%s AND %s\n", secret_word, secret_word_hidden);
    printf("LIVES: %d\n", *lives);


    free(secret_word);
    free(secret_word_hidden);
    free(lives);

    return 0;
}