// Fill out your copyright notice in the Description page of Project Settings.


#include "DHCharacterStat.h"
#include "../../DHGameInstance.h"

// Sets default values for this component's properties
UDHCharacterStat::UDHCharacterStat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UDHCharacterStat::BeginPlay()
{
	Super::BeginPlay();

}

void UDHCharacterStat::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UDHCharacterStat::SetNewLevel(int32 NewLevel)
{
	auto DHGameInstance = Cast<UDHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DHCHECK(nullptr != DHGameInstance);
	CurrentStatData = DHGameInstance->GetDHCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
	else
	{
		DHLOG(Error, TEXT("Level (%d) data dosen't exist"), NewLevel);
	}
}

void UDHCharacterStat::SetDamage(float NewDamage)
{
	DHCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.f, CurrentStatData->MaxHP));
}

void UDHCharacterStat::SetHeal(float HealAmount)
{
	SetHP(FMath::Clamp<float>(CurrentHP + HealAmount, 0.f, CurrentStatData->MaxHP));
}

void UDHCharacterStat::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.f;
		OnHPIsZero.Broadcast();
	}
}

float UDHCharacterStat::GetAttack()
{
	DHCHECK(nullptr != CurrentStatData, 0.f);
	return CurrentStatData->Attack;
}

float UDHCharacterStat::GetHPRatio()
{
	DHCHECK(nullptr != CurrentStatData, 0.f);
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.f : (CurrentHP/CurrentStatData->MaxHP);
}