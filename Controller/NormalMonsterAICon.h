// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "AIController.h"
#include "NormalMonsterAICon.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API ANormalMonsterAICon : public AAIController
{
	GENERATED_BODY()
	
public:
	ANormalMonsterAICon();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName SpawnPosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	void StopAI();

protected:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
};
