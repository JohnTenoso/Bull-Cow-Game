#pragma once
#include <string>

// to make syntax Unreal friendly
using Fstring = std::string;
using int32 = int;

struct Bull_Cow_Count
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum E_Word_Status
{
	Ok,
	Invalid_Status,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame(); //Constructor
	Bull_Cow_Count Submit_Valid_Guess(Fstring);
	E_Word_Status Check_Guess_Validity(Fstring) const;

	int32 Get_Current_Try() const;
	int32 Get_Hidden_Word_Length() const;
	int32 Get_Max_Tries() const;
	bool Is_Game_Won() const;

	void Reset();

	// ^^ Please try and ignore this and focus on the interface above ^^
private:
	//See Costructor for initialisation
	int32 My_Current_try;
	Fstring My_Hidden_Word;
	bool b_Game_is_won;
	bool Is_Isogram(Fstring) const;
	bool Is_Lower_case(Fstring) const;
};