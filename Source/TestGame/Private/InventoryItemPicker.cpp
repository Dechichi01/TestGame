// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItemPicker.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"
#include "TimerManager.h"
#include "ItemInstance.h"
#include "Global/DebugUtils.h"
#include "Global/CollisionContants.h"

static const int16 ItemsInRangeReserve = 3;

// Sets default values for this component's properties
UInventoryItemPicker::UInventoryItemPicker()
{
	ItemsInRange.Reserve(ItemsInRangeReserve);
	UpdateCandidateDelayS = 1;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(200);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_PICKABLE, ECR_Overlap);
	SphereComp->SetupAttachment(GetOwner()->GetRootComponent());

	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &UInventoryItemPicker::OnBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &UInventoryItemPicker::OnEndOverlap);
}


// Called when the game starts
void UInventoryItemPicker::BeginPlay()
{
	Super::BeginPlay();

	ENSURE_MSG(InventoryComp, TEXT("InventoryItemPicker requires a inventory component to be assigned"));	
}

void UInventoryItemPicker::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AItemInstance* Item = Cast<AItemInstance>(OtherActor);
	if (Item)
	{
		ItemsInRange.Add(Item);
		FindBestCandidate();
	}

	if (ItemsInRange.Num() == 1)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(TH_FindBestCandidate, this, &UInventoryItemPicker::FindBestCandidate, UpdateCandidateDelayS, UpdateCandidateDelayS);
	}
}


void UInventoryItemPicker::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AItemInstance* Item = Cast<AItemInstance>(OtherActor);
	if (Item)
	{
		ItemsInRange.RemoveSingleSwap(Item);
		//TODO: Does remove swap alters array even it the item isn't found?
		FindBestCandidate();
	}

	if (ItemsInRange.Num() == 0)
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(TH_FindBestCandidate);
	}
}

/**
 * This function should be fired by a PlayerInput, provided a context is met
 */
void UInventoryItemPicker::OnPickupAction()
{
	FindBestCandidate();
	if (CurrentItemCandidate == nullptr)
	{
		return;
	}

	if (InventoryComp->AddItem(CurrentItemCandidate->ItemData))
	{
		CurrentItemCandidate->OnPicked(GetOwner());
	}
}

void UInventoryItemPicker::FindBestCandidate()
{
	if (ItemsInRange.Num() == 0)
	{
		CurrentItemCandidate = nullptr;
		return;
	}

	//TODO: Find closest
	CurrentItemCandidate = ItemsInRange[0];
}

