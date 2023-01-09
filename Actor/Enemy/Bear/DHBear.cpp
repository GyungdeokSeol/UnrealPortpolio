// Fill out your copyright notice in the Description page of Project Settings.


#include "DHBear.h"
#include "../DHMonsterStat.h"
#include "../NormalMonsterAnim.h"
#include "../../../UI/DHMonsterWidget1.h"
#include "Components/WidgetComponent.h"
#include "../../../Controller/BearAIController.h"

ADHBear::ADHBear()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BEAR(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear.Enemy_Bear"));
	if (SK_BEAR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BEAR.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_BEAR(TEXT("/Game/BearAnimBlueprint.BearAnimBlueprint_C"));
	if (ANIM_BEAR.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_BEAR.Class);
	}

	AIControllerClass = ABearAIController::StaticClass();
}
