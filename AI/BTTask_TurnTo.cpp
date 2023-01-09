// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnTo.h"
#include "../Controller/NormalMonsterAICon.h"
#include "../Actor/Enemy/EnemyCharacter.h"
#include "../Actor/Character/DHCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_TurnTo::UBTTask_TurnTo()
{
	NodeName = TEXT("TurnTo");
}

EBTNodeResult::Type UBTTask_TurnTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter)
	{
		DHLOG(Warning, TEXT("EnemyCharacter == nullptr"))
		return EBTNodeResult::Failed;
	}
	auto Target = Cast<ADHCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANormalMonsterAICon::TargetKey));
	if (nullptr == EnemyCharacter)
	{
		DHLOG(Warning, TEXT("DHCharacter == nullptr"));
		return EBTNodeResult::Failed;
	}

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(EnemyCharacter->GetActorLocation(), Target->GetActorLocation());
	EnemyCharacter->SetActorRotation(LookAt);
	return EBTNodeResult::Succeeded;
}