//
//  FBullCowGame.hpp
//  Bull Cow Game
//
//  Created by Sagar Dwevedi on 22/04/21.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

//To make syntax Unreal friendly
using FString = std::string;//Called Type Alias
using int32 = int;

#endif /* FBullCowGame_hpp */

//all values intialized to zero
struct FBullCowCount{
    int32 Bulls = 0;
    int32 Cows = 0;
};
enum class EGuessStatus{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};
//
//enum Eerror{
//    ok,get_me_out
//}; here ok os global and due due which acts same so compiler shows error of redefining so to prevent this use class after enum

class FBullCowGame{
public:
    FBullCowGame();//constructor
    
    int32 GetMaxTries() const;//this const prevents the change of private part in this same class
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    
    //plz try and ignore this and focus on the interface above
private:
    //see constructor for initialisation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

//fstring is mutable means changeable
//ftext is used for user output

