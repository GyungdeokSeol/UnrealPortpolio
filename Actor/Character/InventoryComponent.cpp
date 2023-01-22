// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../../Item/ItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 10;
}


bool UInventoryComponent::AddItem(class UItemBase* Item)
{
	if (Items.Num() >= Capacity || !Item)
	{
		return false;
	}

	Item->OwningInventory = this;
	Items.Add(Item);

	//UI¾÷µ¥ÀÌÆ®
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(class UItemBase* Item)
{
	if (Item)
	{
		Item->OwningInventory = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}	
}
