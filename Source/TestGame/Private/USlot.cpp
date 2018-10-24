// Fill out your copyright notice in the Description page of Project Settings.

#include "USlot.h"
#include "Item.h"

bool USlot::CanAddItem(const IItem * Item) const
{
	return CurrentHeldItem == nullptr || (CurrentHeldItem == Item && Count < Item->MaxStackCount());
}

bool USlot::AddItem(IItem * Item, int32 Quantity)
{
	if (CurrentHeldItem != nullptr && CurrentHeldItem != Item) {
		return false;
	}

	CurrentHeldItem = Item;
	Count+=Quantity;

	return true;
}

bool USlot::RemoveItem(const IItem * Item, int32 Quantity)
{
	if (CurrentHeldItem != Item) 
	{
		return false;
	}

	if (Quantity >= Count) {
		CurrentHeldItem = nullptr;
		Count = 0;
	}
	else {
		Count -= Quantity;
	}

	return true;
}

IItem * USlot::GetItem() const
{
	return CurrentHeldItem;
}

int32 USlot::GetItemCount() const
{
	return Count;
}
