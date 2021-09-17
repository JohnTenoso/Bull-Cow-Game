/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using Ftext = std::string;
using int32 = int;
FBullCowGame Bull_Cow_Game; // instantiate a new game, which we re-use across plays

// function prototypes as outside a class
Ftext Get_Guess();
void Print_Intro();
void Play_Game();
void Print_Game_Summary();
bool Play_Again();

//Entry point of Application
int main()
{
	do
	{
		Print_Intro();
		Play_Game();
	} while (Play_Again());

	return 0; //Exit Application
}

//Loop countinually until the user gives a valid Guess
Ftext Get_Guess()
{
	Ftext Guess = "";
	E_Word_Status Status = E_Word_Status::Invalid_Status;
	do {
		//Get the Guess from Player
		int32 Current_try = Bull_Cow_Game.Get_Current_Try();
		std::cout << "Try " << Current_try << " of " << Bull_Cow_Game.Get_Max_Tries();
		std::cout << " Enter your Guess: ";
		std::getline(std::cin, Guess);

		//Check Status and give Feedback
		Status = Bull_Cow_Game.Check_Guess_Validity(Guess);
		switch (Status)
		{
		case E_Word_Status::Wrong_Length:
			std::cout << "Please Enter a " << Bull_Cow_Game.Get_Hidden_Word_Length() << " Letter Word.\n\n";
			break;

		case E_Word_Status::Not_Isogram:
			std::cout << "Please Enter a word without repeating letters.\n\n";
			break;

		case E_Word_Status::Not_Lowercase:
			std::cout << "Please Enter all lowercase only.\n\n";
			break;

		default:
			//Assume the Guess is Valid
			break;
		}
	} while (Status != E_Word_Status::Ok); //Keep looping until it get no errors

	return Guess;
}

void Print_Intro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can You Guess the " << Bull_Cow_Game.Get_Hidden_Word_Length();
	std::cout << " Letter Isogram I'm thinking of? \n";
	std::cout << std::endl;

	return;
}

// plays a single game to completion
void Play_Game()
{
	Bull_Cow_Game.Reset();
	int32 My_Tries = Bull_Cow_Game.Get_Max_Tries();

	//Loop asking for guesses while the game is NOT won and there are still tries remaining
	while (!Bull_Cow_Game.Is_Game_Won() && Bull_Cow_Game.Get_Current_Try() <= My_Tries)
	{
		// submit valid guess to the game, and receive counts
		Ftext Guess = Get_Guess();
		Bull_Cow_Count BCCount = Bull_Cow_Game.Submit_Valid_Guess(Guess);

		std::cout << "Bulls: " << BCCount.Bulls;
		std::cout << " / Cows: " << BCCount.Cows << "\n\n";
	}

	Print_Game_Summary();

	return;
}

void Print_Game_Summary()
{
	if (Bull_Cow_Game.Is_Game_Won())
	{
		std::cout << "You Win!\n";
	}
	else
	{
		std::cout << "Sorry, Try Next Time!\n";
	}

	return;
}

bool Play_Again()
{
	std::cout << "Do you want to play Again with same Hidden Word? Y/N \n";
	Ftext Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
