// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "USlot.generated.h"

class IItem;

/**
 * 
 */
UCLASS(BlueprintType)
class TESTGAME_API USlot : public UObject
{
	GENERATED_BODY()

private:
	USlot() : Count() {}

	class IItem* CurrentHeldItem;
	int32 Count;

public:
	bool CanAddItem(const IItem* Item) const;

	//Did not make const IItem* to not use const_cast on assign
	bool AddItem(IItem* Item, int32 Quantity = 1);
	bool RemoveItem(const IItem* Item, int32 Quantity = 1);

	FORCEINLINE bool Free() const { return CurrentHeldItem == nullptr; }
	FORCEINLINE bool ItemsMatch(const IItem* Other) const { return CurrentHeldItem == Other; }

	IItem* GetItem() const;
	int32 GetItemCount() const;
};
