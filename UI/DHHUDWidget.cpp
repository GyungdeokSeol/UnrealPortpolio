// Fill out your copyright notice in the Description page of Project Settings.


#include "DHHUDWidget.h"
#include "Components/ProgressBar.h"
#include "../Actor/Character/DHCharacter.h"
#include "../Actor/Character/DHCharacterStat.h"

void UDHHUDWidget::BindCharacterStat(class UDHCharacterStat* CharacterStat)
{
	DHCHECK(nullptr != CharacterStat);
	CurrentCharacterStat = CharacterStat;
	CharacterStat->OnHPChanged.AddUObject(this, &UDHHUDWidget::UpdateHPWidget);
}

void UDHHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HP")));
	DHCHECK(nullptr != HPProgressBar);
}

void UDHHUDWidget::UpdateHPWidget()
{
	DHCHECK(CurrentCharacterStat.IsValid());
	HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
}