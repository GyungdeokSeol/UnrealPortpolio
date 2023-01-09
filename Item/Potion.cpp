// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"
#include "../Actor/Character/InventoryComponent.h"
#include "../Actor/Character/DHCharacter.h"



void UPotion::Use(ADHCharacter* Character)
{
	if (Character)
	{
		Character->TakeHeal(HealAmount);

		if (OwningInventory)
		{
			OwningInventory->RemoveItem(this);
		}
	}
	OnUse(Character);
}