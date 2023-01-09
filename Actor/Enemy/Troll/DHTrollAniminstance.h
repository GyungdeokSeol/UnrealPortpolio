// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../DungeonHero1.h"
#include "../NormalMonsterAnim.h"
#include "DHTrollAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UDHTrollAniminstance : public UNormalMonsterAnim
{
	GENERATED_BODY()
	
public:
	UDHTrollAniminstance();

	virtual void PlayAttackMontage() override;
};
