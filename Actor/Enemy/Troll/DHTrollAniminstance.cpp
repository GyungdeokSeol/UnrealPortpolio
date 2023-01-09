// Fill out your copyright notice in the Description page of Project Settings.


#include "DHTrollAniminstance.h"

UDHTrollAniminstance::UDHTrollAniminstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage1(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/Enemy_Troll_Poison_Animation/TrollAttack1.TrollAttack1"));
	if (Montage1.Succeeded())
	{
		Montage_1 = Montage1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage2(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/Enemy_Troll_Poison_Animation/TrollAttack2.TrollAttack2"));
	if (Montage2.Succeeded())
	{
		Montage_2 = Montage2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage3(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/Enemy_Troll_Poison_Animation/TrollAttack3.TrollAttack3"));
	if (Montage3.Succeeded())
	{
		Montage_3 = Montage3.Object;
	}
}

void UDHTrollAniminstance::PlayAttackMontage()
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