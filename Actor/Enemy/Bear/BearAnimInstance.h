// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../DungeonHero1.h"
#include "../NormalMonsterAnim.h"
#include "BearAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UBearAnimInstance : public UNormalMonsterAnim
{
	GENERATED_BODY()
	
public:
	UBearAnimInstance();

	virtual void PlayAttackMontage() override;
};
