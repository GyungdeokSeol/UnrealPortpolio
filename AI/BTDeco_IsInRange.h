// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDeco_IsInRange.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UBTDeco_IsInRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDeco_IsInRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};