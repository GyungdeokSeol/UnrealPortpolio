// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServ_Detect.h"
#include "../Actor/Character/DHCharacter.h"
#include "../Controller/NormalMonsterAICon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTServ_Detect::UBTServ_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTServ_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;
	if (nullptr == World) return;

	TArray <FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
	OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(DetectRadius), CollisionQueryParam);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			ADHCharacter* DHCharacter = Cast<ADHCharacter>(OverlapResult.GetActor());
			if (DHCharacter && DHCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANormalMonsterAICon::TargetKey, DHCharacter);
				//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				//DrawDebugPoint(World, DHCharacter->GetTargetLocation(), 10.f, FColor::Blue, false, 0.2f);
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), DHCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				//return;
			}
		}
	}
	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}