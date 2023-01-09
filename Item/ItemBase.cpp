// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

UItemBase::UItemBase()
{
	ItemDisplayName = FText::FromString("ItemBase");
	UseActionText = FText::FromString("Use");
}

void UItemBase::Use(class ADHCharacter* Character)
{

}
