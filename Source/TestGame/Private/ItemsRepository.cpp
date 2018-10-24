// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemsRepository.h"
#include "Engine/ObjectLibrary.h"
#include "ItemData.h"

UItemsRepository::UItemsRepository() : Super(), ItemsDataPath(DEFAULT_ITEMS_PATH) {}

UItemData& UItemsRepository::GetItemById(FString ItemId, FString SearchTag)
{
	if (!ItemsMap.Contains(ItemId)) {
		ensure(CacheWithTag(SearchTag));
	}

	//Item data should be unique. This was a bad solution, use DataTable instead
	check(ItemsMap.Contains(ItemId));

	UItemData* Item = ItemsMap[ItemId];

	return *Item;
}

bool UItemsRepository::CacheWithTag(FString Tag)
{
	//TODO: It  actually loading the full library, test a better solution
	if (!ItemsLibrary)
	{
		ItemsLibrary = UObjectLibrary::CreateLibrary(UItemData::StaticClass(), false, GIsEditor);
		ItemsLibrary->AddToRoot();
		ItemsLibrary->LoadAssetDataFromPath(TEXT(""));
		ItemsLibrary->LoadAssetsFromAssetData();
	}

	TArray<FAssetData> AssetDatas;
	ItemsLibrary->GetAssetDataList(AssetDatas);

	ItemsMap.Reserve(AssetDatas.Num());

	for (int32 i = 0; i < AssetDatas.Num(); i++)
	{
		FAssetData& AssetData = AssetDatas[i];
		UItemData* Item = Cast<UItemData>(AssetData.GetAsset());
		if (ensure(Item))
		{
			ItemsMap[Item->UniqueId()] = Item;
		}
	}

	return true;
}