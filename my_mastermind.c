#include "my_mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <stdbool.h> 

void Create_unknown_code(char *Eazy_unrevealed_code)
{
    const char unknown_samp_lives[] = "0123456789";
    for (int i = 0; i < 4; i=i+1) {
        Eazy_unrevealed_code[i] = unknown_samp_lives[rand() % 10];
    }
    Eazy_unrevealed_code[4] = '\0';
}


void calculate_suggested_cards(const char *hidden_code, const char *predict,
                               int *right_choice, int *wrong_chosen)
{
    *right_choice = 0; *wrong_chosen = 0;
    char secretly_peaked[5];  char trial_duplicate[5];
    strcpy(secretly_peaked, hidden_code);   strcpy(trial_duplicate, predict);
    for (int i = 0; i < 4; i=i+1) { if (hidden_code[i] == predict[i])
        {
            (*right_choice)++;  secretly_peaked[i] = 'X';    trial_duplicate[i] = 'X';
        } }
    for (int i = 0; i < 4; i++) { if (trial_duplicate[i] != 'X')
        {
            for (int j = 0; j < 4; j++) {
                if (secretly_peaked[j] == trial_duplicate[i])
                {  (*wrong_chosen)++;
                    secretly_peaked[j] = 'X'; break;
                }
            }
        }
    }
}


bool read_guess(char *chance, int *valid_input) {
    char c;
    int i = 0;
    *valid_input = 1; 

    while (i < 4) {
        int read_outcome = read(STDIN_FILENO, &c, 1);
        if (read_outcome < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (read_outcome == 0) { 
            return false; 
        }
        
        if (c < '0' || c > '8') {
            *valid_input = 0; 
            break;
        }
        chance[i++] = c;
    }

    
    while (c != '\n' && read(STDIN_FILENO, &c, 1) > 0);

    if (!(*valid_input)) {
        printf("Wrong input. Please enter only digits between 0 and 8.\n");
    }

    return true; 
}

void play_mastermind(const char *code, int trials_attempts) {
    srand(time(NULL));
    char secret_code[5];
    if (code == NULL) {
        Create_unknown_code(secret_code);
    } else {
        strcpy(secret_code, code);
    }
    printf("Will you give a trial and find the secret code?\n");
    char suggestion_guess[5];
    int rightly_kept, wrongly_kept;
    for (int attempt = 0; attempt < trials_attempts; attempt++) {
        printf("\n---- Round %d ----\n", attempt + 1);
        printf("Please enter a valid guess\n");
        int valid_input;
        if (!read_guess(suggestion_guess, &valid_input)) {
            printf("\nGoodbye!\n");
            return;
        }
        if (!valid_input) {
            continue; 
        }
        calculate_suggested_cards(secret_code, suggestion_guess, &rightly_kept,  &wrongly_kept);
        if (rightly_kept == 4) {
            printf("Congratz! You did it!\n");
            return;  
        } else {
            printf("Well placed pieces: %d\nMisplaced pieces: %d\n", rightly_kept, wrongly_kept);
        }
    }
    printf("Out of attempts. The secret code was: %s\n", secret_code);
}

int custom_atoi_read(const char *eazy) {
    int outcome = 0;
    int sign = 1;
    int i = 0;

    while (eazy[i] == ' ' || eazy[i] == '\t' || eazy[i] == '\n') i++;

    if (eazy[i] == '-') {
        sign = -1;
        i++;
    } else if (eazy[i] == '+') {
        i++;
    }

    while (eazy[i] >= '0' && eazy[i] <= '9') {
        outcome = outcome * 10 + (eazy[i] - '0');
        i++;
    }

    return sign * outcome;
}

int main(int argument, char *alternate[]) {
    char *code = NULL;
    int attempts = 10;
    if (argument > 1) {
        for (int i = 1; i < argument; i++) {
            if (alternate[i][0] == '-' && alternate[i][1] == 'c') {
                code = alternate[i + 1];
            } else if (alternate[i][0] == '-' && alternate[i][1] == 't') {
                attempts = custom_atoi_read(alternate[i + 1]);
            }
        }
    }

    play_mastermind(code, attempts);

    return 0;
}
