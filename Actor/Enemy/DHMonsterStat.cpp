// Fill out your copyright notice in the Description page of Project Settings.


#include "DHMonsterStat.h"
#include "../../DHGameInstance.h"

// Sets default values for this component's properties
UDHMonsterStat::UDHMonsterStat()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UDHMonsterStat::BeginPlay()
{
	Super::BeginPlay();

}

void UDHMonsterStat::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}

void UDHMonsterStat::SetNewLevel(int32  NewLevel)
{
	auto DHGameInstance = Cast<UDHGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	DHCHECK(nullptr != DHGameInstance);
	CurrentStatData = DHGameInstance->GetDHMonsterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		SetHP(CurrentStatData->MaxHP);
	}
}

void UDHMonsterStat::SetDamage(float NewDamage)
{
	DHCHECK(nullptr != CurrentStatData);
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.f, CurrentStatData->MaxHP));
}

void UDHMonsterStat::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.f;
		OnHPIsZero.Broadcast();
	}
}

float UDHMonsterStat::GetAttack()
{
	DHCHECK(nullptr != CurrentStatData, 0.f);
	return CurrentStatData->Attack;
}

float UDHMonsterStat::GetHPRatio()
{
	DHCHECK(nullptr != CurrentStatData, 0.f);
	DHLOG(Warning, TEXT("GetHPRatio"));
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.f : (CurrentHP / CurrentStatData->MaxHP);
}