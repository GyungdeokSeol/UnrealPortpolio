// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "Blueprint/UserWidget.h"
#include "DHMonsterWidget1.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UDHMonsterWidget1 : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindMonsterStat(class UDHMonsterStat* NewMonsterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UDHMonsterStat> CurrentStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;

	//float ExHPRatio;
};
