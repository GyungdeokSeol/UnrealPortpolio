// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DungeonHero1.h"
#include "Animation/AnimInstance.h"
#include "NormalMonsterAnim.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API UNormalMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UNormalMonsterAnim();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayAttackMontage();
	void SetDeadAnim() { IsDead = true; }

	FOnAttackHitCheckDelegate OnAttackHitCheck;

protected:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Montage_1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Montage_2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Montage_3;
};
