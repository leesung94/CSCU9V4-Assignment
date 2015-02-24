/* File: hangman.c
 * StudentID: 2114299
 *
 * This program implements the game, Hangman. 
 *
 * Comments
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define STR_LEN 50

void stageOne();
void stageChange(int wrongGuess);
void guessCharacter(int wordLength, char ToBeAchieved[],char *wordAchieved);
void hideLetters(int wordLength, char wordToBeAchieved[], char *wordAchieved);
void hasSolved(int wordLength, char *wordAchieved, int *hasSolved);

int main(int argc, char *argv[]) {

	int option = 1;
	int categorySelect;
	int chooseWord;
	int seekWord;
	int docLen = 0;
	int wordLength;
	char wordToBeAchieved[STR_LEN + 1];

	do {
		//char dictionary[] = "movies.txt"; /* filename currently hard-coded; better if a command line argument. */

		printf("*********************************************\n");
		printf("*******************HANGMAN*******************\n");
		printf("*********************************************\n");
		printf("Welcome to Hangman! Please Select a category!\n");
		printf("Enter 1 for: Movies\n");
		printf("Enter 2 for: Music Artists\n");
		printf("Enter 3 for: Countries and Cities\n");
		scanf("%d", &categorySelect);
		if (categorySelect == 1) {
			FILE *word;
			word=fopen("movies.txt", "r");
			if (word == NULL) {
				exit(1);
			}
			char reading;
			while (reading != EOF) {
				reading = getc(word);
				if (reading == '\n'){
					docLen++;
				}
			}
			srand ( time(NULL) );
			chooseWord = rand() % docLen;
			fseek(word, 0, SEEK_SET);
			for(seekWord = 0; seekWord <= chooseWord; seekWord++)
				fgets(wordToBeAchieved, STR_LEN + 1, word);
			fclose(word);
			wordLength = strlen(wordToBeAchieved);
			char wordAchieved[wordLength + 1];
			hideLetters(wordLength, wordToBeAchieved, wordAchieved);
			for(int i = 0; i < wordLength; i++) {
				printf("%c ", wordAchieved[i]);
			}
			stageOne();
			guessCharacter(wordLength, wordToBeAchieved, wordAchieved);
		} else if (categorySelect == 2) {
			FILE *word;
			word = fopen("artists.txt", "r");
			if (word == NULL) {
				exit(1);
			}
			char reading;
			while (reading != EOF) {
				reading = getc(word);
				if (reading == '\n') {
					docLen++;
				}
			}
			srand ( time(NULL) );
			chooseWord = rand() % docLen;
			fseek(word, 0, SEEK_SET);
			for (seekWord = 0; seekWord <= chooseWord; seekWord++)
				fgets(wordToBeAchieved, STR_LEN + 1, word);
			fclose(word);
			wordLength = strlen(wordToBeAchieved);
			char wordAchieved[wordLength + 1];
			hideLetters(wordLength, wordToBeAchieved, wordAchieved);
			for (int i = 0; i < wordLength; i++) {
				printf("%c ", wordAchieved[i]);
			}
			stageOne();
			guessCharacter(wordLength, wordToBeAchieved, wordAchieved);
		} else if (categorySelect == 3) {
			FILE *word;
			word = fopen("places.txt", "r");
			if (word == NULL) {
				exit(1);
			}
			char reading;
			while (reading != EOF) {
				reading = getc(word);
				if (reading == '\n') {
					docLen++;
				}
			}
			srand ( time(NULL) );
			chooseWord = rand() % docLen;
			fseek(word, 0, SEEK_SET);
			for (seekWord = 0; seekWord <= chooseWord; seekWord++)
				fgets(wordToBeAchieved, STR_LEN + 1, word);
			fclose(word);
			wordLength = strlen(wordToBeAchieved);
			char wordAchieved[wordLength + 1];
			hideLetters(wordLength, wordToBeAchieved, wordAchieved);
			for (int i = 0; i < wordLength; i++) {
				printf("%c ", wordAchieved[i]);
			}
			stageOne();
			guessCharacter(wordLength, wordToBeAchieved, wordAchieved);
		} else {
			printf("Sorry incorrect input would you like to try that again?\n");
			printf("Press 1 for yes:\nPress 2 for no:\n");
			scanf("%d", &option);
		}
		printf("Would you like to play again?\n");
		printf("Press 1 for yes:\nPress 2 for no:\n");
		scanf("%d", &option);
	} while (option == 1);
	return 0;
}



void stageOne() {

	printf("You have 9 live(s) left\n");
	printf("_________ \n");
	printf("|/\n");
	printf("| \n");
	printf("| \n");
	printf("| \n");
	printf("| \n");
	printf("| \n");
	printf("--------- \n\n");

}

void guessCharacter(int wordLength, char wordToBeAchieved[],char wordAchieved[]) {
	int wrongGuesses = 0;
	int rightGuesses = 0;
	char wrongCharacters[10];
	char rightCharacters[wordLength];
	for (int i = 0; i < 10; i++) {
		wrongCharacters[i] = ' ';
	}
	int isSolved = 1;
	while((isSolved != 0)) {
		if (wrongGuesses == 9) {
			break;
		}
		printf("\nMystery Word: ");
		for(int i = 0; i < wordLength; i++) {
			printf("%c ", wordAchieved[i]);
		}
		printf("\n");
		printf("Please enter a character: ");
		char check;
		scanf(" %c", &check);
		int correct = 0;
		for(int i = 0; i < wordLength; i++) {
			if (check == rightCharacters[i]) {
				printf("You have already entered this character\n");
				printf("Please try different one\n");
				correct++;
			} else {
				if (toupper(check) == wordToBeAchieved[i]) {
					correct++;
					wordAchieved[i] = toupper(check);
				}
				if (tolower(check) == wordToBeAchieved[i]) {
					correct++;
					wordAchieved[i] = tolower(check);
				}
			}
		}
		if (correct == 0) {
			wrongCharacters[wrongGuesses] = check;
			wrongGuesses+=1;
			stageChange(wrongGuesses);
			printf("Incorrect Character Guesses: ");
			for (int i = 0; i < 9 ; i++) {
				printf("%c ", wrongCharacters[i]);
			}
			printf("\n");
		} else {
			int has = 0;
			for (int i = 0; i < wordLength; i++) {
				if(rightCharacters[i] == check) {
					has = 1;
					break;
				}
			}
			if (has == 1) {
				printf("Correct Character Guesses: ");
				for (int i = 0; i < rightGuesses; i++) {
					printf("%c ", rightCharacters[i]);
				}
				printf("\n");
			} else {
				rightCharacters[rightGuesses] = check;
				rightGuesses+=1;
				printf("Correct Character Guesses: ");
				for (int i = 0; i < rightGuesses; i++) {
					printf("%c ", rightCharacters[i]);
				}
				printf("\n");
			}
		}
		hasSolved(wordLength, wordAchieved, &isSolved);
	}
	if (isSolved == 0){
		printf("\nMystery Word: ");
		for(int i = 0; i < wordLength; i++) {
			printf("%c ", wordToBeAchieved[i]);
		}
		printf("\nWell Done, You correctly guessed the word!\n");
	} else {
		printf("Oh No, You Ran Out Of lives :(\n");
		printf("Better Luck Next Time!\n");
	}
}

void hideLetters(int wordLength, char wordToBeAchieved[], char wordAchieved[]) {
	for (int i = 0; i < wordLength; i++) {
		if (wordToBeAchieved[i] != ' ') {
			wordAchieved[i] = '_';
		}
		if (!(isalpha(wordToBeAchieved[i]))) {
			wordAchieved[i] = wordToBeAchieved[i];
		}
	}
}

void hasSolved(int wordLength, char wordAchieved[], int *isSolved) {
	*isSolved = 0;
	for (int i; i < wordLength; i++){
		if (wordAchieved[i] == '_') {
			*isSolved += 1;
		}
	}
}

void stageChange(int wrongGuesses) {
	int livesLeft = 9 - wrongGuesses;

	printf("You have %d Live(s) left:\n", livesLeft);
	printf("_________ \n");
	if (wrongGuesses >= 1) {
		printf("|/    |   \n");
	} else {
		printf("|/\n");
	}
	if (wrongGuesses >= 2)  {
		printf("|     0   \n");
	} else {
		printf("|\n");
	}
	if (wrongGuesses == 3) {
		printf("|     |   \n");
	} else if (wrongGuesses == 4) {
		printf("|   - |   \n");
	} else if (wrongGuesses >= 5) {
		printf("|   - |-  \n");
	} else {
		printf("| \n");
	}
	if (wrongGuesses == 6) {
		printf("|    /    \n");
	} else if (wrongGuesses == 7) {
		printf("|    /-\\ \n");
	} else if (wrongGuesses == 8) {
		printf("|   _/-\\ \n");
	} else if (wrongGuesses == 9) {
		printf("|   _/-\\_\n");
	} else {
		printf("| \n");
	}
	printf("| \n");
	printf("| \n");
	printf("--------- \n\n");

}






