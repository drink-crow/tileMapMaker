// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FileManager.h"

#include "OpenMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TILEMAPMAKER_API UOpenMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void reloadFloderPath(FString FloderPath);

	UFUNCTION(BlueprintCallable)
	bool checkDirectoryExists(FString FloderPath);

	UFUNCTION(BlueprintCallable)
	TArray<FString> getFile(FString FloderPath, FString extension);
};
