// Fill out your copyright notice in the Description page of Project Settings.


#include "DHGameInstance.h"

UDHGameInstance::UDHGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/DHCharacterData.DHCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DHCHARACTER(*CharacterDataPath);
	DHCHECK(DT_DHCHARACTER.Succeeded());
	DHCharacterTable = DT_DHCHARACTER.Object;
	DHCHECK(DHCharacterTable->GetRowMap().Num() > 0);

	FString MonsterDataPath = TEXT("/Game/DHMonsterData1.DHMonsterData1");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_DHMONSTER (*MonsterDataPath);
	DHCHECK(DT_DHMONSTER.Succeeded());
	DHMonsterTable = DT_DHMONSTER.Object;
	DHCHECK(DHMonsterTable->GetRowMap().Num() > 0);
}

void UDHGameInstance::Init()
{
	Super::Init();

}

FDHCharacterData* UDHGameInstance::GetDHCharacterData(int32 Level)
{
	return DHCharacterTable->FindRow<FDHCharacterData>(*FString::FromInt(Level), TEXT(""));
}

FDHMonsterData* UDHGameInstance::GetDHMonsterData(int32 Level)
{
	return DHMonsterTable->FindRow<FDHMonsterData>(*FString::FromInt(Level), TEXT(""));
}