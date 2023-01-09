// Fill out your copyright notice in the Description page of Project Settings.


#include "DHMonsterWidget1.h"
#include "../Actor/Enemy/DHMonsterStat.h"
#include "Components/ProgressBar.h"


void UDHMonsterWidget1::BindMonsterStat(class UDHMonsterStat* NewMonsterStat)
{
	DHCHECK(nullptr != NewMonsterStat);
	CurrentStat = NewMonsterStat;
	NewMonsterStat->OnHPChanged.AddUObject(this, &UDHMonsterWidget1::UpdateHPWidget);
}

void UDHMonsterWidget1::NativeConstruct()
{
	Super::NativeConstruct();
	DHLOG(Warning, TEXT("NativeConstruct"));

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	DHCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UDHMonsterWidget1::UpdateHPWidget()
{
	if (CurrentStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentStat->GetHPRatio());
		}
	}
}
