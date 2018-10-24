// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.h"
#include "ItemData.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class TESTGAME_API UItemData : public UDataAsset, public IItem
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere)
	FGuid Id;
	UPROPERTY(EditDefaultsOnly)
	int16 MaxStack;

	UPROPERTY(EditDefaultsOnly)
	int16 Rarity;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FText Name;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FText Description;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* Thumbnail;

	virtual FString UniqueId() const { return Id.ToString(); };
	virtual int16 MaxStackCount() const { return MaxStack; };

	operator IItem*() { return nullptr; }
};
