#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map // to make syntax Unreal friendly

using int32 = int;

// default constructor
FBullCowGame::FBullCowGame() 
{
	Reset(); 
}

//Receives a VALID Guess, Incriments turn, and returns count
Bull_Cow_Count FBullCowGame::Submit_Valid_Guess(Fstring Guess)
{
	My_Current_try++;
	Bull_Cow_Count BCCount;
	int32 Word_Length = My_Hidden_Word.length(); // Assuming same Length as Guess

	// loop through all letters in the Hidden Word
	for (int32 MHWChar = 0; MHWChar < Word_Length; MHWChar++)
	{
		// compare letters against the Guess word
		for (int32 GChar = 0; GChar < Word_Length; GChar++)
		{
			// if they match then
			if (Guess[GChar] == My_Hidden_Word[MHWChar])
			{
				if (MHWChar == GChar) // if they're in the same place
				{
					BCCount.Bulls++; // incriment bulls
				}
				else
				{
					BCCount.Cows++; // must be a cow
				}
			}
		}
	}

	if (BCCount.Bulls == Word_Length)
	{
		b_Game_is_won = true;
	}
	else
	{
		b_Game_is_won = false;
	}

	return BCCount;
}

E_Word_Status FBullCowGame::Check_Guess_Validity(Fstring Guess) const
{
	if (!Is_Isogram(Guess)) // if the guess isn't an isogram
	{
		return E_Word_Status::Not_Isogram;
	}
	else if (!Is_Lower_case(Guess)) // if the guess isn't all lowercase
	{
		return E_Word_Status::Not_Lowercase;
	}
	else if (Guess.length() != Get_Hidden_Word_Length()) // if the guess length is wrong
	{
		return E_Word_Status::Wrong_Length;
	}
	else
	{
		return E_Word_Status::Ok;
	}
}

int32 FBullCowGame::Get_Current_Try()const 
{ 
	return My_Current_try;
}

int32 FBullCowGame::Get_Hidden_Word_Length() const 
{ 
	return My_Hidden_Word.length();
}

int32 FBullCowGame::Get_Max_Tries() const 
{ 
	TMap <int32, int32> Word_Length_to_Max_tries { {3,5}, {4,5}, {5,3}, {6,3} };
	return Word_Length_to_Max_tries[My_Hidden_Word.length()];
}

bool FBullCowGame::Is_Game_Won() const 
{ 
	return b_Game_is_won; 
}

bool FBullCowGame::Is_Lower_case(Fstring Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}

bool FBullCowGame::Is_Isogram(Fstring Word) const
{
	//Treat 0 and 1 letter words as Isogram
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap <char, bool> Letter_Seen;	//Setup map
	for (auto Letter : Word)		//For all letters of the word
	{
		Letter = tolower(Letter);	//Handle mixes case
		if (Letter_Seen[Letter])	//If the letter is in the map
		{
			return false;			//Do Not have an Isogram
		}
		else
		{
			Letter_Seen[Letter] = true; //Add the letter to the map
		}
	}

	return true; //For Example in case where /0 is entered
}

void FBullCowGame::Reset()
{
	const Fstring Hidden_Word = "planet"; // this MUST be an isogram
	My_Hidden_Word = Hidden_Word;
	My_Current_try = 1;
	b_Game_is_won = false;
	return;
}