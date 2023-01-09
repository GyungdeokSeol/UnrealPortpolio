// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Potion.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UPotion : public UItemBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	float HealAmount;

	virtual void Use(class ADHCharacter* Character) override;

};
