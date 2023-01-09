// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAnimInstance.h"

UBearAnimInstance::UBearAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear_Animations/AttackMontage.AttackMontage"));
	if (Montage1.Succeeded())
	{
		Montage_1 = Montage1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage2(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear_Animations/AttackMontage_B.AttackMontage_B"));
	if (Montage2.Succeeded())
	{
		Montage_2 = Montage2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage3(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Bear/Enemy_Bear_Animations/JumpAttackMontage.JumpAttackMontage"));
	if (Montage3.Succeeded())
	{
		Montage_3 = Montage3.Object;
	}
}

void UBearAnimInstance::PlayAttackMontage()
{
	if (IsDead == false)
	{
		int32 RandNumber = FMath::RandRange(0, 2);
		switch (RandNumber)
		{
			case 0:
				Montage_Play(Montage_1, 1.5f);
			break;
			case 1:
				Montage_Play(Montage_2, 1.5f);
			break;
			case 2:
				Montage_Play(Montage_3, 1.5f);
			break;
		}		
	}
}

