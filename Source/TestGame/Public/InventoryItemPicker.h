// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemPicker.generated.h"

class UInventoryComponent;
class USphereComponent;
class AItemInstance;
struct FTimerHandle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTGAME_API UInventoryItemPicker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryItemPicker();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UInventoryComponent* InventoryComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float UpdateCandidateDelayS;

	TArray<AItemInstance*> ItemsInRange;
	AItemInstance* CurrentItemCandidate;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnPickupAction();

private:
	FTimerHandle TH_FindBestCandidate;
	void FindBestCandidate();
};
