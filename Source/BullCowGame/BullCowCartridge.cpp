// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Guessword.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(Words);
    PrintLine(TEXT("Welcome to Bull Cow Game!!"));
    PrintLine(TEXT("About the Game: The Game is word guessing game. \n You have to guess the right word to win the game."));
    PrintLine(TEXT("The Game asks you about the correct word by giving the number of letters that word contains."));
    PrintLine(TEXT("You will have that many lives as well."));
    PrintLine(TEXT("Press enter to continue."));
    PlayGame = true;
    bGameOver = false;
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    int32 Cow, Bull;
    if(PlayGame)
    {
        ClearScreen();
        PlayGames();

    }
    else if(bGameOver)
    {
        ClearScreen();
        SetGame();
    }
    else{

        if(HiddenWord.Len() == Input.Len())
        {
            if(HiddenWord == Input)
            {
                PrintLine(TEXT("You Win"));
                PrintLine(TEXT("Press enter to play again"));
                EndGame();
            }
            else if(!Isisogram(Input))
            {
                PrintLine(TEXT("No repeating letters. Try again"));
            }
            else
            {
                GetBullCow(Input, Bull, Cow);
                PrintLine(TEXT("You have %i Bulls and %i Cows"), Bull, Cow);
                if(Lives > 0)
                {
                    --Lives;
                    PrintLine(TEXT("oh no! You have lost a life"));
                    PrintLine(TEXT("You have %i lives left \nTry again"), Lives);
                    bGameOver = false;
                }
                else{
                    PrintLine(TEXT("Sorry!! You have no life left"));
                    PrintLine(FString::Printf(TEXT("You Lose. The hidden word was %s."), *HiddenWord));
                    PrintLine(TEXT("Press enter to play again"));
                    EndGame();

                }
                
            }
        }
        else
        {
            PrintLine(FString::Printf(TEXT("Enter the %i character number"), HiddenWord.Len()));
        }
    }
    
}

void UBullCowCartridge::SetGame()
{
    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)]; // sets HiddenWord.
    Lives = HiddenWord.Len();
    bGameOver = false;
    PrintLine(TEXT("Welcome to Bull Cow Game"));
    PrintLine(FString::Printf(TEXT("Guess the %i character Hidden Word"), HiddenWord.Len()));
    PrintLine(TEXT("You have %i lives."), Lives);
}
void UBullCowCartridge::PlayGames()
{
    PrintLine(TEXT("After guessing the word,\n it will show you the number of bulls and cows you got."));
    PrintLine(TEXT("As many bulls you scored means that many words are correct on their places."));
    PrintLine(TEXT("As many cows you scored means that many letters are correct but not on the correct place."));
    PrintLine(TEXT("Press Enter to play the game."));
    PlayGame = false;
    bGameOver = true;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
}

bool UBullCowCartridge::Isisogram(const FString& Word) const
{
    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for(int32 j = Index+1; j < Word.Len(); j++)
        {
            if(Word[Index] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for(FString W: WordList)
    {
        if(W.Len() >= 4 && W.Len() <= 8 && Isisogram(W))
        {
            ValidWords.Emplace(W);
        }
    }
    return ValidWords;
}

void UBullCowCartridge::GetBullCow(const FString& Guess,int32& Bull, int32& Cow) const
{
    Bull = 0;
    Cow = 0;

    for(int32 i = 0; i < Guess.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
        {
            Bull++;
            continue;
        }
        for(int32 j = i; j < HiddenWord.Len(); j++)
        {
            if(Guess[i] == HiddenWord[j])
            {
                Cow++;
                break;
            }
        }
    }
}