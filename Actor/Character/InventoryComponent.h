// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//�������Ʈ�� UI������Ʈ�Ҷ� ���ε�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONHERO1_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
		
	bool AddItem(class UItemBase* Item);
	bool RemoveItem(class UItemBase* Item);

	//���� ���� �� ������
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItemBase*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	int32 Capacity;

	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
	TArray<class UItemBase*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
