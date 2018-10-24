// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "ItemInstance.generated.h"

class UItemData;

UCLASS()
class TESTGAME_API AItemInstance : public AActor, public IPickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void OnItemPicked(AActor* Picker);

	UFUNCTION(BlueprintNativeEvent)
	void OnItemReleased(AActor* Releaser);

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	UItemData* ItemData;

	virtual void OnPicked(AActor* Picker) override;
	virtual void OnReleased(AActor* Releaser) override;

private:
	void OnItemPicked_Implementation(AActor* Picker);
	void OnItemReleased_Implementation(AActor* Releaser);
};
