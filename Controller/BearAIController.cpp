// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ABearAIController::ABearAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/AI/BT_Bear.BT_Bear"));
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

