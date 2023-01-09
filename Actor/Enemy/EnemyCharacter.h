// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DungeonHero1.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCloseAttackEndDelegate);

UCLASS()
class DUNGEONHERO1_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UDHMonsterStat* MonsterStat;
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	UPROPERTY(VisibleAnywhere, Category = Collision)
	USphereComponent* UITrigger;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	bool IsAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	UFUNCTION()
	virtual void SetDead();
	void CloseAttack();
	void CloseAttackCheck();
	bool IsDead();
	FOnCloseAttackEndDelegate OnAttackEnd;

protected:
	bool IsDeath;
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
	class ANormalMonsterAICon* AICon;
	UPROPERTY()
	class UNormalMonsterAnim* NormAnim;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
	void OnCharacterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCharacterOutRange(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};