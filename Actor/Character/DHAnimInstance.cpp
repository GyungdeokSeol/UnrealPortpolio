// Fill out your copyright notice in the Description page of Project Settings.


#include "DHAnimInstance.h"


UDHAnimInstance::UDHAnimInstance()
{
	CurrentSpeed = 0;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/ThirdPersonBP/Blueprints/charactor/Sword_char/Animation/SwordManAttack.SwordManAttack"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UDHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;

	if (!IsDead)
	{
		CurrentSpeed = Pawn->GetVelocity().Size();
	}
}

void UDHAnimInstance::PlayAttackMontage()
{
	DHCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.5f);
}

void UDHAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	DHCHECK(!IsDead);
	DHCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UDHAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UDHAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UDHAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	DHCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 3), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}