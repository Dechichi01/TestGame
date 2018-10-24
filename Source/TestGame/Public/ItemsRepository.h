// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "ItemsRepository.generated.h"

class UItemData;
class UObjectLibrary;

const FName DEFAULT_ITEMS_PATH = "/Content/Items/Data/";
/**
 *
 */
UCLASS()
class TESTGAME_API UItemsRepository : public UObject
{
	GENERATED_BODY()

public:
	UItemsRepository();

	UObjectLibrary* ItemsLibrary;

	FName ItemsDataPath;

	TMap<FString, UItemData*> ItemsMap;

	UItemData& GetItemById(FString ItemId, FString SearchTag);

private:
	bool CacheWithTag(FString Tag);
};
