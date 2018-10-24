// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "InventoryContainer.generated.h"

class IItem;
class USlot;

UCLASS()
class TESTGAME_API UInventoryContainer : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryContainer();
	
protected:
	TArray<USlot*> Slots;

public:
	int16 GetMaxCapacity() const;
	void SetMaxCapacity(int16 MaxCapacity);	
	bool CanAddItem(const IItem* Item);
	
	void AddItem(IItem* Item, int16 Quantity);
	void AddItemAtSlot(IItem* Item, int16 SlotIndex, int16 Quantity = 1);
	FORCEINLINE void RemoveItemAtSlot(const IItem* Item, int16 SlotIndex, int16 Quantity = 1);

	USlot* GetSlot(int16 SlotIndex) const;
};
