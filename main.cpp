//
//  main.cpp
//  Bull Cow Game
//
//  Created by Sagar Dwevedi on 16/04/21.
//


// < is used whenever we import standard stuff
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

//To make Syntax Unreal friendly
using FText=std::string;//Type Aliasing
using int32 = int;

//function prototypes as outside a class
void PrintIntro();//semicolon to prevent {}
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGAME;//INSTANTIATE a new game, which we re-use across plays

//entry point of the program
int main(int32 argc, const char * argv[]) {
    std::cout<<BCGAME.GetCurrentTry();
    
    // insert code here...
    do{
        PrintIntro();
        //TODO add a game summary
        PlayGame();
    }while(AskToPlayAgain());
    
    return 0;
    
}

//int32 findMe(){
//    std::cout<<"Hello, World!\n";
//    return 1;
//}



//loop continually until the user gives a valid guess
FText GetValidGuess(){
    EGuessStatus Status=EGuessStatus::Invalid_Status;
    FText Guess = "";
    do{
    
    //get a guess from the player
    int32 CurrentTry=BCGAME.GetCurrentTry();
    std::cout<<"Try "<<CurrentTry<<" of"<<BCGAME.GetMaxTries()<<". Enter the Guess please\n";
    //std::cin>>Guess;
    std::getline(std::cin,Guess);
    
    Status = BCGAME.CheckGuessValidity(Guess);
    switch(Status){
        case EGuessStatus::Wrong_Length:
            std::cout<<"Please enter a "<<BCGAME.GetHiddenWordLength()<<"letter word. \n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout<<"Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout<<"Please enter all lowercase letters.\n\n";
            break;
        default:
            //assume the guess is valid
            break;
    }
    }while (Status!=EGuessStatus::OK);//keep looping until we get no errors
    return Guess;
//    repeat the guess back to them
//    std::cout<<Guess<<std::endl;
}


void PrintIntro(){
    //introduce the game
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
    std::cout << std::endl;
    //image of bull and cow
    //std::cout << "Welcome to Bulls and Cows!"<<std::endl;
    std::cout << "Can you guess the "<<BCGAME.GetHiddenWordLength()<<" letter isogram I'm thinking of?\n";
    std::cout<<std::endl;
    return;
}

//plays a single game to completion
void PlayGame()
{
    BCGAME.Reset();
    int32 MAXTries=BCGAME.GetMaxTries();
//    std::cout<<MAXTries<<std::endl;
    
    //loop asking for the guesses while the game is NOT won
    //and there are still tries remaining
    while(!BCGAME.IsGameWon() && BCGAME.GetCurrentTry() <= MAXTries){
        FText Guess=GetValidGuess();//TODO make loop checking valid
        
        //submit valid guess to the game, and receive counts
        FBullCowCount BullCowCount = BCGAME.SubmitValidGuess(Guess);
        
        std::cout<<"Bulls = "<<BullCowCount.Bulls;
        std::cout<<". Cows = "<<BullCowCount.Cows<<std::endl;
        //print number of bulls and cows
        //std::cout<<"Your guess was : "<<Guess<<std::endl;
        //std::cout<<std::endl;
    }
    PrintGameSummary();
    return;
}

bool AskToPlayAgain(){
    std::cout<<"Do you want to play again with the same word(y/n) ?\n";
    FText Response = "";
    getline(std::cin,Response);
    //return (Response[0]=='y'||'Y'); we can't use this as for logical or we need boolean both the side
    return (Response[0]=='y')||(Response[0]=='Y');
    
}

void PrintGameSummary(){
    if(BCGAME.IsGameWon()){
        std::cout<<"WELL DONE - YOU WIN!!\n";
    }
    else{
        std::cout<<"Better luck next time";
    }
}


//getline()
//it reads through any spaces by default and discard the input stream once it reaches
//the new line
