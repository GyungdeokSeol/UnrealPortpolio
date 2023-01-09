// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "BehaviorTree/BTService.h"
#include "BTServ_Detect.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UBTServ_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTServ_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
