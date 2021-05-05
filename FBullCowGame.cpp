//
//  FBullCowGame.cpp
//  Bull Cow Game
//
//  Created by Sagar Dwevedi on 22/04/21.
//
#pragma once
#include "FBullCowGame.hpp"
#include<string>
#include<map>

//To make syntax unreal friendly
#define TMap std::map//compare it with type aliasing or "using" term
using int32=int;

FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetCurrentTry() const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength()const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const{
    TMap<int32,int32> WordLengthToMaxTries{
        {3,4},{4,7},{5,10},{6,13},{7,15}
    };//To intialize
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(){
//    constexpr int32 MAX_TRIES=3; //or MAX_TRIES={3}
    const FString Hidden_Word = "plan";//This must be a isogram
    
//    MyMaxTries=MAX_TRIES;
    MyHiddenWord = Hidden_Word;
    MyCurrentTry=1;
    bGameIsWon=false;
    return;
    
}

EGuessStatus FBullCowGame::CheckGuessValidity (FString Guess) const{
    if(!IsIsogram(Guess))//if the guess isn't an isogram
    {
        return EGuessStatus::Not_Isogram;//isograms are words with no repating letters
    }else if (!IsLowerCase(Guess)){//if the guess isn't all lowercase
        return EGuessStatus::Not_Lowercase;
    }else if (Guess.length()!=GetHiddenWordLength()){//if the guess length is wrong
        return EGuessStatus::Wrong_Length;
    }else{
        return EGuessStatus::OK;
    }
}

//receive a VALID guess, increments
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();// assuming same length as guess
    for(int32 MHWChar=0;MHWChar<WordLength;MHWChar++){
        //compare letters against the guess
        for(int32 GChar=0;GChar<WordLength;GChar++){
            if(Guess[GChar]==MyHiddenWord[MHWChar]){
                if(MHWChar==GChar){
                    BullCowCount.Bulls++;//increment bulls
                }
                else{
                    BullCowCount.Cows++;//must be cow
                }
            }
        }
    }
    //compare letters against the hidden word
    if(BullCowCount.Bulls == WordLength){
        bGameIsWon=true;
    }
    else{
        bGameIsWon=false;
    }
    return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const{
    //treat 0 and 1 letter strings as isograms
    if(Word.length()<=1){return true;}
    
    TMap<char,bool> LetterSeen;//setup our map
    for(auto Letter: Word)//for all letters of the word
    {
        Letter = tolower(Letter);//handle mixed case
        if(LetterSeen[Letter]){//if the letter is in the map
            return false;//we don't have isogram
        }else{
            LetterSeen[Letter]=true;
        }
          //add the letter to the map as seen
    }
    
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const{
    
    for(auto Letter : Word){
        if(!islower(Letter)){//if not a lowercase letter turn false
            return false;
        }
    }
    return false;
}

//The standard string class provides support for such objects with an interface similar to that of a standard container
//of bytes,but adding features specifically designed to operate with the strings of the single-byte characters.
