#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define buff 1024
void HS(int highscore); // highscores
int random_word (int random);	
void Stage(int stage);
void instruction();
void loading();
void gotoxy(int x , int y);
void start ();
int main ()
{
//FILE
	FILE *ptr;
	char buffer[buff];
	int count = 0;
	char words[buff][100];
	char filename[] = "data.txt";
	char *fields;
//gotoxy variables
	int x ;
	int y ;
	
//	bool data_valid = false;
	int menu;
	//if menu == 1
	char valid[100];
	bool flag = false;
	//GAME START bool
//	bool failed = false;
	char word;
	char guess[100];
	int stage = 0;
	char word_valid[100];
	int index = 0;
	char answers[100];
	int coor = 0;
	int length = 0;
	
	//untuk highscores
	int highscores = 0;
	//read file
	ptr = fopen(filename,"r");
	if(ptr == NULL)
	{
		printf("Unable to read game data.Try Again Later");
		return - 1;
		
	}
	while(fgets(buffer,sizeof(buffer),ptr))
	{
		
		strcpy(words[count],strtok(buffer,"\n"));
		count ++;
	}
	fclose(ptr);

	loading(); // loading menu
	system("cls");
	//inisialisasi menu
	start ();
	while(1) // apabila pencet enter,maka :
	{
		if(getch() == 13)
		{
			system("cls");
			break;
		}
	}
	menu :
	do
	{
		bool final_answer = false;
		bool game_valid = false;
		bool start_valid = false;
		system("cls");
		printf("PLEASE CHOOSE BETWEEN 1 - 3\n");
		printf("1.Play The Game\n");
		printf("2.Instruction\n");
		printf("3.Exit\n");
		printf("Your Choice : ");
		scanf("%d",&menu);
		while(getchar() != '\n');
		do
		{
			switch(menu)
			{
				case 1 :
					system("cls");
					printf("Please Type [\"Start Game\"] to continue : "); //validasi untuk memulai program
					scanf("%[^\n]s",&valid);
					while(getchar() != '\n');
					if(strcmp("Start Game",valid) == 0)
					{
						start_valid = true;
						system("cls");
					}
					break;
			
				//Instructions
				case 2 :
					system("cls");
					instruction ();
					printf("Press Esc to go back");
					if(getch() == 27)
					{
						goto menu;
					}
					break;
				//Exit Program
				case 3 :
					system("cls");
					gotoxy(0,10);
					printf("=======================================================================================================================\n");
					gotoxy(40,12);
					printf("Thank You For Using This Program");
					gotoxy(0,14);
					printf("=======================================================================================================================\n");
					return 1;
				default:
					system("cls");
					break;
			}
		}while(start_valid == false);
		
		strcpy(guess,words[random_word(count)]);
		length = strlen(guess);

		//GAME START
		do
		{
			int counts = 0;
			bool answer = false;
			Stage(stage);		
			for(int i = 0 ; i < length ; i ++)
			{
				if(answers[i] == guess[i])
				{
					printf("%c ",guess[i]);
				}
				else if(answers[i] != guess[i])
				{
					fflush(stdout);
					printf("_ ",guess[i]);
				}
			}
			printf("\nWords that have been input : \n");
			for(int i = 0 ; i < strlen(word_valid) ; i ++)
			{
				
				printf("%c ",word_valid[i]);
					
			}
			printf("\nYour Input [Must be in Capital]: ");
			scanf("%c",&word);
			while(getchar() != '\n' && getchar() !='\0');
			if(word > 64 && word < 91)
			{
				bool duplicate = false;
				for(int i = 0 ; i < strlen(word_valid) ; i ++)
				{
					if(word_valid[i] == word)
					{
						duplicate = true;
					}
				}
				if(duplicate == false)
				{
					word_valid[index] = word;
					for(int j = 0 ; j < length ; j ++)
					{
						if(word_valid[index] == guess[j])
						{
							answers[j] = guess[j];
							answer = true;
						}
						if(answers[j] == guess[j])
						{
							counts ++;
						}
					}
					index ++;
				}
				else if(duplicate == true)
				{
					system("cls");
					continue;
				}

				if(answer == false)
				{
					stage ++;
				}
				else if(answer == true)
				{
					gotoxy(75,0);
//					HS(highscores);
				}

				if(stage == 6)
				{
					system("cls");
					Stage(stage);
					printf("The answer was %s\n",guess);
					printf("-GAME OVER-\n");
					printf("Press Esc to exit");
					do
					{
						if(getch() == 27)
						{
							game_valid = true;
							final_answer = false;
						}
					}while(getch() != 27);

				}
				if(counts == length)
				{
					system("cls");
					gotoxy(40,8);
					printf("------_¯_-----_¯_");
					gotoxy(40,9);
					printf("-----_¦¦¦¯¯¯¯¯¦¦¦_");
					gotoxy(40,10);
					printf("-__--¦¦¦¦¦¦¦¦¦¦¦¦¦--__");
					gotoxy(40,11);
					printf("¦__¦-¦¦¦¯¦¦-¦¦¯¦¦¦-¦__¦");
					gotoxy(40,12);
					printf("Congratulations You Win !");
					gotoxy(0,0);
					printf("Press Esc to exit");
					do
					{
						if(getch() == 27)
						{
							game_valid = true;
							final_answer = true;
						}
					}while(getch() != 27);
				}
				system("cls");
			}
			else
			{
				system("cls");
			}

		}while(game_valid == false);
		if(final_answer == true || final_answer == false)
		{
			flag = false;
		}
	
	}while(flag == false);
}
void instruction()
{
	printf("Instructions\n");
	printf("1.\n");
}
int random_word (int random)
{
	int rand_gen;
	srand(time(NULL));
	rand_gen = rand() % random;
	return rand_gen;
}
void gotoxy(int x , int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void loading()
{
	gotoxy(55,22);
	printf("Loading...");
	gotoxy(45,25);
	for(int i = 0 ; i < 30 ; i ++)
	{
		printf("%c",219);
		for(int j = 0 ; j < 10000000 ; j ++);
	}
}
void start ()
{
	gotoxy(23,8);
	printf("================	         //\\\\         ||\\\\            //|| =================\n");
	gotoxy(23,9);
	printf("|| 		 	//  \\\\        || \\\\          // || ||\n");
	gotoxy(23,10);
	printf("||		       //    \\\\       ||  \\\\        //  || ||\n");
	gotoxy(23,11);
	printf("||		      //      \\\\      ||   \\\\      //   || ||\n");
	gotoxy(23,12);
	printf("||==============      //========\\\\     ||    \\\\    //    || ||===============\n");
	gotoxy(23,13);
	printf("||	      ||    //	        \\\\    ||     \\\\  //     || ||\n");
	gotoxy(23,14);
	printf("||	      ||   //	         \\\\   ||      \\\\//      || ||\n");
	gotoxy(23,15);
	printf("||	      ||  //		  \\\\  ||                || ||\n");
	gotoxy(23,16);
	printf("================  // 		   \\\\ ||                || =================\n");

	
	gotoxy(45,23);
	printf("Press [ENTER] to continue\n");
}
void Stage(int stage)
{
	if(stage == 0)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf("       |\n");
		printf("       |\n");
		printf("       |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 1)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf("       |\n");
		printf("       |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 2)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf(" |     |\n");
		printf("       |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 3)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf("/|     |\n");
		printf("       |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 4)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf("/|\\    |\n");
		printf("       |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 5)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf("/|\\    |\n");
		printf("/      |\n");
		printf("       |\n");
		printf("========\n");
	}
	else if(stage == 6)
	{
		printf("\n========\n");
		printf(" |     |\n");
		printf(" O     |\n");
		printf("/|\\    |\n");
		printf("/ \\    |\n");
		printf("       |\n");
		printf("========\n");
	}
//	void HS(int highscore)
//	{
//		highscore += 150;
//		printf("Highscore : %d",highscore);
//	}
}

