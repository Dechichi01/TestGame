// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UInventoryContainer;
class UItemData;
class USlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemAdded, const USlot*, Slot, int16, AddedQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemRemoved, const UItemData*, Item, const USlot*, Slot, int16, RemovedQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemMoved, const UItemData*, Item, const USlot*, PrevSlot, const USlot*, NewSlot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	UInventoryContainer* InventoryContainer;

	UPROPERTY(EditDefaultsOnly)
	int16 DefaultMaxCapacity;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FItemAdded EventItemAdded;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FItemRemoved EventItemRemoved;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FItemMoved EventItemsSwapped;

	bool AddItem(UItemData* Item, int16 Quantity = 1);
	void RemoveItemAtSlot(UItemData* Item, int16 SlotIndex, int16 Quantity = 1);
	bool MoveItem(UItemData* Item, int16 ItemSlot, int16 NewSlot);
	void SwapItems(UItemData* LItem, int16 LItemSlot, UItemData* RItem, int16 RItemSlot);
};
