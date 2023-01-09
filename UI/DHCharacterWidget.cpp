// Fill out your copyright notice in the Description page of Project Settings.


#include "DHCharacterWidget.h"
#include "../Actor/Character/DHCharacterStat.h"
#include "Components/ProgressBar.h"

void UDHCharacterWidget::BindCharacterStat(class UDHCharacterStat* NewCharacterStat)
{
	DHCHECK(nullptr != NewCharacterStat);	
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UDHCharacterWidget::UpdateHPWidget);
}

void UDHCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	DHCHECK(nullptr != HPProgressBar);
	UpdateHPWidget();
}

void UDHCharacterWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
