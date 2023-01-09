// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DungeonHero1.h"
#include "GameFramework/Character.h"
#include "DHCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


UCLASS()
class DUNGEONHERO1_API ADHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADHCharacter();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UDHCharacterStat* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class ADHSword* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class ADHShield* CurrentShield;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	FOnAttackEndDelegate OnAttackEnd;

	//카메라 줌 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float ArmLegnthTo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float ArmLocationTo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	float ArmLocationNow = 50.f;

	bool CanSetWeapon();
	bool CanSetShield();
	void SetWeapon(class ADHSword* NewWeapon);
	void SetShield(class ADHShield* NewShield);
	void Attack();
	UFUNCTION(BlueprintCallable, Category = Items)
	void UseItem(class UItemBase* Item);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	float TakeHeal(float HealAmout);

private:
	UPROPERTY()
	class UDHAnimInstance* DHAnim;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsShieldUp;
	bool isdead;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void ShieldUp();
	void ShieldDown();
	bool ShieldAngleCheck(AActor* DamageCauser);


};
