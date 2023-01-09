// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDeco_IsInRange.h"
#include "../Actor/Character/DHCharacter.h"
#include "../Controller/NormalMonsterAICon.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDeco_IsInRange::UBTDeco_IsInRange()
{
	NodeName = TEXT("IsInRange");
}

bool UBTDeco_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	auto Target = Cast<ADHCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANormalMonsterAICon::TargetKey));
	if (nullptr == Target) return false;
	
	bResult = (Target->GetDistanceTo(ControllingPawn) <= 300.f);
	return bResult;
}