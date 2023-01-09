// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterAICon.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANormalMonsterAICon::SpawnPosKey(TEXT("SpawnPos"));
const FName ANormalMonsterAICon::PatrolPosKey(TEXT("PatrolPos"));
const FName ANormalMonsterAICon::TargetKey(TEXT("Target"));

ANormalMonsterAICon::ANormalMonsterAICon()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/AI/BB_Normal.BB_Normal"));
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;
	
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Normal.BT_Normal"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

void ANormalMonsterAICon::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(SpawnPosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			DHLOG(Error, TEXT("couldn't run BT"))
		}
	}
}

void ANormalMonsterAICon::StopAI()
{
	BrainComponent->StopLogic("");
}