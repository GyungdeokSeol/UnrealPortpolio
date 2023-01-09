// Fill out your copyright notice in the Description page of Project Settings.


#include "TrollAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ATrollAIController::ATrollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Troll.BT_Troll"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}