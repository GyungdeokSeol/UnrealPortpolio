// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "Blueprint/UserWidget.h"
#include "DHCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UDHCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UDHCharacterStat* NewCharacterStat);
	
protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UDHCharacterStat> CurrentCharacterStat;
	
	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
