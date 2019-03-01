// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenMenuUserWidget.h"

void UOpenMenuUserWidget :: reloadFloderPath(FString FloderPath)
{
	TArray<FString> foundFiles;

	//如果目标文件夹不存在
	if (!IFileManager::Get().DirectoryExists(*FloderPath))
	{

	}
}

bool UOpenMenuUserWidget::checkDirectoryExists(FString FloderPath)
{
	return IFileManager::Get().DirectoryExists(*FloderPath);
}

TArray<FString> UOpenMenuUserWidget::getFile(FString FloderPath, FString extension)
{
	TArray<FString> files;
	IFileManager::Get().FindFiles(files, *FloderPath, *extension);
	return files;
}


