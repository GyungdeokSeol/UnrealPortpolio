// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterAnim.h"

UNormalMonsterAnim::UNormalMonsterAnim()
{
	CurrentSpeed = 0;
	IsDead = false;

	//¸ùÅ¸ÁÖ Ãß°¡
}

void UNormalMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
	if (!IsDead)
	{
		CurrentSpeed = Pawn->GetVelocity().Size();
	}
}

void UNormalMonsterAnim::PlayAttackMontage()
{

}

void UNormalMonsterAnim::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
