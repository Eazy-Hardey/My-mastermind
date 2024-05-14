#include "mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <time.h>

void Create_unknown_code(char *Eazy_unrevealed_code)
{
    const char unknown_samp_lives[] = "0123456789";
    for (int i = 0; i < 4; i=i+1) {
        Eazy_unrevealed_code[i] = unknown_samp_lives[rand() % 10];
    }
    Eazy_unrevealed_code[4] = '\0';
}

void read_guess(char *chance)
{
    char c;
    int i = 0;
    while (read(0, &c, 1) > 0 && c != '\n' && i < 4) {
        if (c >= '0' && c <= '8') {
            chance[i++] = c;
        } else {  printf("Wrong input!\n"); return;
        }
    }
    if (i != 4) {
        printf("Invalid input. kindly write 4 digits, each between 0-8.\n");
    }
    chance[4] = '\0';
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
void play_mastermind(const char *code, int trials_attempts)
{
    srand(time(NULL)); char secret_code[5];
    if (code == NULL) { Create_unknown_code(secret_code);
    } else { strcpy(secret_code, code);
    }
   printf("Will you give a trial and find the secret code?\n");
   char suggestion_guess[5];
   int rightly_kept, wrongly_kept;
   for (int attempt = 0; attempt < trials_attempts; attempt++)
   {
       printf("Please enter a valid guess\n"); read_guess(suggestion_guess);
       calculate_suggested_cards(secret_code, suggestion_guess, &rightly_kept,  &wrongly_kept);
       if (rightly_kept == 4)
       {
           printf("Congratz! You did it!\n");
           return;  }  else
       {
           printf("Well placed pieces: %d\nMisplaced pieces: %d\n",        rightly_kept, wrongly_kept);
       }
}
  printf("Out of attempts. The secret code was: %s\n", secret_code);
}
