// Fill out your copyright notice in the Description page of Project Settings.


#include "DHTroll.h"
#include "DHTrollAniminstance.h"
#include "../../../Item/DHTrollWeapon.h"
#include "Components/WidgetComponent.h"
#include "../../../Controller/TrollAIController.h"


ADHTroll::ADHTroll()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Troll(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/SK_Troll_Poison.SK_Troll_Poison"));
	if (SK_Troll.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Troll.Object);
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_TROLL(TEXT("/Game/ABP_Troll.ABP_Troll_C"));
	if (ANIM_TROLL.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_TROLL.Class);
	}
	GetCapsuleComponent()->InitCapsuleSize(100.f, 100.f);
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 300.f));

	AIControllerClass = ATrollAIController::StaticClass();

}

void ADHTroll::BeginPlay()
{
	Super::BeginPlay();
	FName WeaponSocket(TEXT("b_MF_Weapon_R_Socket"));
	auto CurrentWeapon = GetWorld()->SpawnActor<ADHTrollWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		CurrentWeapon->SetOwner(this);
		Weapon = CurrentWeapon;
	}

}

void ADHTroll::SetDead()
{
	Super::SetDead();
	Weapon->SetLifeSpan(5);
}