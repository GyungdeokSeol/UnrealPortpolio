// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DungeonHero1.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "DHGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FDHCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	public: FDHCharacterData() : Level(1), MaxHP(100.f), Attack(10.f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

USTRUCT(BlueprintType)
struct FDHMonsterData : public FTableRowBase
{
	GENERATED_BODY()
	
	public: FDHMonsterData() : Level(1), MaxHP(100.f), Attack(10.f), DropExp(10) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;
};




UCLASS()
class DUNGEONHERO1_API UDHGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDHGameInstance();

	virtual void Init() override;
	FDHCharacterData* GetDHCharacterData(int32 Level);
	FDHMonsterData* GetDHMonsterData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* DHCharacterTable;
	UPROPERTY()
	class UDataTable* DHMonsterTable;
};
