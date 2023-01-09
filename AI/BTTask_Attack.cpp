// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../Controller/NormalMonsterAICon.h"
#include "../Actor/Enemy/EnemyCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	IsAttacking = false;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto DHEnemy = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == EnemyCharacter) return EBTNodeResult::Failed;

	EnemyCharacter->CloseAttack();
	IsAttacking = true;
	EnemyCharacter->OnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
		});
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}