// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract, EditInlineNew, DefaultToInstanced)
class DUNGEONHERO1_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	UItemBase();

	virtual class UWorld* Getworld() const {return World;};

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	class UStaticMesh* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item, meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Item)
	class UInventoryComponent* OwningInventory;

	virtual void Use(class ADHCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ADHCharacter* Character);
};
