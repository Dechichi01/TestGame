// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryContainer.h"
#include "USlot.h"


// Sets default values for this component's properties
UInventoryContainer::UInventoryContainer()
{}

int16 UInventoryContainer::GetMaxCapacity() const
{
	return int16();
}

void UInventoryContainer::SetMaxCapacity(int16 MaxCapacity)
{
	if (MaxCapacity == Slots.Num()) 
	{
		return;
	}

	int OldNum = Slots.Num();

	Slots.SetNumUninitialized(MaxCapacity);
	if (MaxCapacity < OldNum)
	{
		return;
	}

	for (int16 i = OldNum; i < MaxCapacity; i++)
	{
		Slots[i] = NewObject<USlot>();
	}
}

bool UInventoryContainer::CanAddItem(const IItem * Item)
{
	return Slots.ContainsByPredicate([&](USlot* const Slot) {
		return Slot->CanAddItem(Item);
	});
}

void UInventoryContainer::AddItem(IItem * Item, int16 Quantity)
{
	int32 Index = Slots.IndexOfByPredicate([&](USlot* const  Slot) {
		return Slot->ItemsMatch(Item);
	});

	if (Index == INDEX_NONE) {
		Index = Slots.IndexOfByPredicate([&](USlot* const  Slot) {
			return Slot->Free();
		});
	}

	AddItemAtSlot(Item, Index, Quantity);
}

void UInventoryContainer::AddItemAtSlot(IItem * Item, int16 SlotIndex, int16 Quantity)
{
	if (ensure(SlotIndex == INDEX_NONE)) {
		return;
	}

	ensure(Slots[SlotIndex]->AddItem(Item, Quantity));
}

void UInventoryContainer::RemoveItemAtSlot(const IItem* Item, int16 SlotIndex, int16 Quantity)
{
	ensure(Slots[SlotIndex]->RemoveItem(Item, Quantity));
}

USlot* UInventoryContainer::GetSlot(int16 SlotIndex) const
{
	return Slots[SlotIndex];
}
