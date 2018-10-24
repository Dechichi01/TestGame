// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryContainer.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() : DefaultMaxCapacity(0)
{
	InventoryContainer = NewObject<UInventoryContainer>();
	InventoryContainer->SetMaxCapacity(DefaultMaxCapacity);
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

bool UInventoryComponent::AddItem(UItemData * Item, int16 Quantity)
{
	IItem* ItemInterface = Cast<IItem>(Item);
	if (!InventoryContainer->CanAddItem(ItemInterface))
	{
		return false;
	}

	InventoryContainer->AddItem(ItemInterface, Quantity);
	//TODO: Call event
	return true;
}

void UInventoryComponent::RemoveItemAtSlot(UItemData * Item, int16 SlotIndex, int16 Quantity)
{
	IItem* ItemInterface = Cast<IItem>(Item);
	InventoryContainer->RemoveItemAtSlot(ItemInterface, SlotIndex, Quantity);
	//TODO: Call event
}

bool UInventoryComponent::MoveItem(UItemData * Item, int16 ItemSlot, int16 NewSlot)
{
	//TODO:
}

void UInventoryComponent::SwapItems(UItemData * LItem, int16 LItemSlot, UItemData * RItem, int16 RItemSlot)
{
	//TODO;
}
