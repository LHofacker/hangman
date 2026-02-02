#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<sysexits.h>

#define MAX_WORD_SIZE 50
#define MAX_GUESS_SIZE 2

void get_random_word_from_file(char *buffer, int buffer_size){

    FILE *file = fopen("../assets/hangmanWords.txt", "r");

    if (!file){

        printf("UNABLE TO OPEN FILE! MAY NOT EXIST!\n");
        exit(EX_IOERR);
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

void word_to_lowercase(char *buffer){

    size_t buffer_size = strlen(buffer);

    for(size_t i = 0; i < buffer_size; i++){

        buffer[i] = tolower((unsigned char)buffer[i]);
    }
}

void hide_selected_word(char *word, char **hidden_word_str, size_t *actual_word_size){

    word_to_lowercase(word);

    *actual_word_size = strlen(word);
    *hidden_word_str = malloc(*actual_word_size + 1);
    (*hidden_word_str)[*actual_word_size] = '\0';
    
    for (size_t i = 0; i != *actual_word_size; i++) {
        
        (*hidden_word_str)[i] = '_';
    }
}

void cleanup_stdin(char guess){

    char a;

    if(guess != '\n'){
        a = getchar();

        while (a != '\n'){
            a = getchar();
        }
    }
}

int char_already_used(char guess, char *used_characters){

    size_t length_of_used_chars = strlen(used_characters);

    for(size_t i = 0; i < length_of_used_chars; i++){

        if(guess == used_characters[i]){

            return 0;
        }
    }

    used_characters[length_of_used_chars] = guess;

    return 1;
}

int validade_user_input(char guess, char *used_characters){

    if(!isalpha((unsigned char) guess)){

        printf("GUESS IS NOT A LETTER. TRY AGAIN!\n");
        return 1;
    }

    if(!char_already_used(guess, used_characters)){

        printf("CHAR ALREADY USED. TRY AGAIN!\n");
        return 1;
    }

    return 0;
}

void make_guess(char *used_characters, char* word, char* hidden_word, int *lives){

    char guess;
    int validated = 1;
    int hits = 0;

    
    printf("MAKE YOUR GUESS: ");
    guess = getchar();
    guess = tolower(guess);

    cleanup_stdin(guess);

    validated = validade_user_input(guess, used_characters);

    if(validated == 0){

        size_t word_length = strlen(word);

        for(size_t i = 0; i < word_length; i++){

            if (guess == word[i]){

                hidden_word[i] = guess;
                hits += 1;                
            }
        }

        printf("HITS: %d\n", hits);
        if(hits < 1) *lives -= 1;
    }
}


int game_state(char* word, char* hidden_word, int *lives){

    if (strcmp(word, hidden_word) == 0) return 1;
    if (*lives == 0) return 2;

    return 0;
}

void print_UI(char *hidden_word, char *used_characters, int *lives){

    system("clear");

    printf("%s\n", hidden_word);
    printf("USED CHARS: %s\n", used_characters);
    printf("LIVES: %d\n", *lives);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");

}

int main(){

    char *word = malloc(MAX_WORD_SIZE);
    char *used_characters = malloc(30);
    size_t *actual_word_size = malloc(sizeof(int));
    int *lives = malloc(sizeof(int));
    char *hidden_word = 0;

    int loop_keeper = -1;
    int game_end_flag = 0;

    *lives = 7;
    used_characters[29] = '\0';   

    get_random_word_from_file(word, MAX_WORD_SIZE);
    hide_selected_word(word, &hidden_word, actual_word_size);

    while(loop_keeper == -1){

        print_UI(hidden_word,used_characters, lives);
        make_guess(used_characters, word, hidden_word, lives);
        game_end_flag = game_state(word, hidden_word, lives);

        if (game_end_flag == 1){

            system("clear");
            printf("CONGRATULATIONS! YOU WON!\n");
            printf("\n\n");
            break;
        }

         if (game_end_flag == 2){
            
            system("clear");
            printf("YOU HAVE LOST!\n");
            printf("\n\n");
            break;
        }
    }

    printf("THE WORD WAS: %s\n", word);

    free(word);
    free(used_characters);
    free(lives);
    free(hidden_word);
    free(actual_word_size);

    return 0;
}