// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemInstance.h"
#include "ItemData.h"
#include "Global/DebugUtils.h"


// Sets default values
AItemInstance::AItemInstance()
{
}

void AItemInstance::BeginPlay()
{
	ENSURE(ItemData);
}

void AItemInstance::OnPicked(AActor * Picker)
{
	LogDebug("Item Picked! %s", ItemData->Name.ToString());
	OnItemPicked(Picker);
}

void AItemInstance::OnReleased(AActor * Releaser)
{
	LogDebug("Item Released! %s", ItemData->Name.ToString());
	OnItemReleased(Releaser);
}

void AItemInstance::OnItemPicked_Implementation(AActor * Picker)
{
	Destroy();
}

void AItemInstance::OnItemReleased_Implementation(AActor * Releaser)
{}

