// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
    void SetGame();
	void PlayGames();
	void EndGame();
	bool Isisogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	void GetBullCow(const FString& Guess, int32& Bull, int32& Cow) const;
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	FString PlayerGuess;
	TArray<FString> Isograms;
	bool PlayGame;
};
