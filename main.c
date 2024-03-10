/*

		QUIZ GAME	
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// amount has to be same as amount of questions
#define ARRAY_SIZE 5

void clearScreen();
void pressAnyKey();

void game();
void playAgain(float score, char playerName[]);

int isDuplicate(int uniqueNumber[], int currentIndex, int randomNumber);

void displayScore();
void writeScore(float score, char playerName[20]);
void help();

int main()
{
	char choice;

	clearScreen();

	// \033 is escape character [1;<color code>m change color 32 for green
	printf("\033[1;32m");

	printf("WELCOME TO QUIZ GAME\n\n");

	// this reset color back to original
	printf("\033[1;0m");

	printf("--------------------\n");
	printf("Start game     	 \033[1;32m[S]\033[1;0m\n");
	printf("View high score  \033[1;32m[V]\033[1;0m\n");
	printf("Help             \033[1;32m[H]\033[1;0m\n");
	printf("Quit           	 \033[1;32m[Q]\033[1;0m\n");
	printf("--------------------\n");

	printf("Enter your choice... ");
	scanf("%c", &choice);

	switch (choice)
	{
		case 'S':
		case 's':
			game();
			main();
			break;
		
		case 'V':
		case 'v':
			displayScore();
			main();
			break;
		
		case 'H':
		case 'h':
			help();
			main();
			break;

		case 'Q':
		case 'q':
			exit(0);
			break;
	}

	return 0;
}

// Function to play game
void game()
{
	int countQuestion, countCorrect;
	char playerName[20];

	float score;
	char answer;

	clearScreen();
			
	printf("Enter your name (only one word)... ");

	printf("\033[1;32m");
	scanf("%s", playerName);
	printf("\033[1;0m");

	countQuestion = countCorrect = 0;

	// Seed the random number generator with the current time for rand()
    srand(time(NULL));
    
	// Array to store unique random numbers
    int uniqueNumber[ARRAY_SIZE];
    
    // Generate unique random numbers and store them in uniqueNumber
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int random;
        
        // Generate a random number until it is unique in the array
        do 
		{
            random = rand() % ARRAY_SIZE + 1;
        } 
		while (isDuplicate(uniqueNumber, i, random));
        
		// Store the unique random number
        uniqueNumber[i] = random;  
    }
    
	for(int j = 0; j < ARRAY_SIZE; j++)
	{
		switch (uniqueNumber[j])
		{
			case 1:
				printf("\n\nWhat is result of 2 + 2?\n");
				printf("[A]4  [B]3  [C]none  [D]kebab\n\n");
				countQuestion++;

				printf("Enter your answer: ");
				scanf(" %c", &answer);

				if (answer == 'A' || answer == 'a')
				{
					printf("Correct!");
					countCorrect++;
					break;
				}
				else
				{
					printf("Wrong! Correct is [A]4");
					break;
				}

			case 2:
				printf("\n\nHow long it takes to the Earth spin around the Sun\n");
				printf("[A]4  [B]2  [C]none  [D]365\n\n");
				countQuestion++;
				
				printf("Enter your answer: ");
				scanf(" %c", &answer);

				if(answer == 'D' || answer == 'd')
				{
					printf("Correct!");
					countCorrect++;
					break;
				}
				else
				{
					printf("Wrong! Correct is [D]365");
					break;
				}
			
			case 3:
				printf("\n\nWhy can not you love yourself?\n");
				printf("[A]IDK  [B]cause' i am freak  [C]you  [D]none\n\n");
				countQuestion++;
				
				printf("Enter your answer: ");
				scanf(" %c", &answer);

				if(answer == 'C' || answer == 'c')
				{
					printf("Correct!");
					countCorrect++;
					break;
				}
				else
				{
					printf("Wrong! Correct is [C]you");
					break;
				}
			
			case 4:
				printf("\n\nWhat is result of \\033[H\\033[J?\n");
				printf("[A]your mom  [B]nothing  [C]delete your data  [D]clear screen\n\n");
				countQuestion++;
				
				printf("Enter your answer: ");
				scanf(" %c", &answer);

				if(answer == 'D' || answer == 'd')
				{
					printf("Correct!");
					countCorrect++;
					break;
				}
				else
				{
					printf("Wrong! Correct is [D]clear screen");
					break;
				}

			case 5:
				printf("\n\nWhat do you get if you combine hydrogen gas and oxygen gas?\n");
				printf("[A]water  [B]explotion  [C]nothing  [D]your mom\n\n");
				countQuestion++;
				
				printf("Enter your answer: ");
				scanf(" %c", &answer);

				if(answer == 'A' || answer == 'a')
				{
					printf("Correct!");
					countCorrect++;
					break;
				}
				else
				{
					printf("Wrong! Correct is [A]water");
					break;
				}
		}
	}

	score = (float)countCorrect / countQuestion * 100;

	if(score < 0)
	{
		score = 0;
	}

	printf("\n\n");
	printf("\tYour Score: %.2f\n\n", score);

	pressAnyKey();
	
	playAgain(score, playerName);
}

// Function to ask if want to play again
void playAgain(float score, char playerName[])
{
	char play;

	clearScreen();

	printf("Play again? [y/n]...");
	scanf("%c", &play);

	switch (play)
	{
		case 'Y':
		case 'y':
			game();
			break;

		case 'N':
		case 'n':
			writeScore(score, playerName);
			main();				
			break;
	
	default:
		printf("Error: wrong keyword");
		pressAnyKey();
		main();
		break;
	}
}

// Function to check if a number already exists in the array
int isDuplicate(int uniqueNumber[], int currentIndex, int randomNumber) {
    for (int i = 0; i < currentIndex; i++) {
        if (uniqueNumber[i] == randomNumber) {
            return 1;  // Duplicate found
        }
    }
    return 0;  // No duplicate found
}

// Function to clear screen
void clearScreen() 
{
	// clear console
	printf("\033[H\033[J");
}

// Function to wait for any key to be pressed
void pressAnyKey()
{
	printf("\nPress any key to continue... ");
	while((getchar()) != '\n');
	getchar();
}

// Show score
void displayScore()
{
	char name[20];
	float score;
	FILE *fileScore;

	clearScreen();

	fileScore = fopen("score.txt", "r");
	fscanf(fileScore, "%s%f", name, &score);

	printf("\n\t\t \033[1;32m %s \033[1;0m has secured the Highest Score %.2f\n\n", name, score);

	fclose(fileScore);

	pressAnyKey();
}

// Write score to .txt file
void writeScore(float score, char playerName[20])
{
	float newScore;
	char name[20];
	FILE *fileScore;

	clearScreen();

	fileScore = fopen("score.txt", "r");
	fscanf(fileScore, "%s%f", name, &newScore);

	if(score >= newScore)
	{
		newScore = score;
		fclose(fileScore);
		fileScore = fopen("score.txt", "w");
		fprintf(fileScore, "%s\n%.2f", playerName, score);
		fclose(fileScore);
	}
}

// Show help for player
void help()
{	
	clearScreen();

	printf("This game is very easy to play.\n\n" 
		   "You'll be asked some general knowledge questions\n" 
		   "and the right answer is to be chosen among the four options provided.\n"
		   "Your score will be calculated at the end.\n\n"
		   "Remember that the more quicker you give answer the more\n"
		   "score you will secure. Your score will be calculated and displayed\n"
		   "at the end and displayed. If you secure highest score, your score\n"
		   "will be recorded. Have a fun.\n");
	
	pressAnyKey();
}