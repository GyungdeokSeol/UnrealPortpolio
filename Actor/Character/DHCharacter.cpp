// Fill out your copyright notice in the Description page of Project Settings.


#include "DHCharacter.h"
#include "DHCharacterStat.h"
#include "DHAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "../../Item/DHSword.h"
#include "../../Item/DHShield.h"
#include "Components/WidgetComponent.h"
#include "../../UI/DHCharacterWidget.h"
#include "../../Item/ItemBase.h"
#include "InventoryComponent.h"

// Sets default values
ADHCharacter::ADHCharacter()
{
	Tags.Add(FName("Player"));
	PrimaryActorTick.bCanEverTick = true;
	//component setup
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterStat = CreateDefaultSubobject<UDHCharacterStat>(TEXT("CHARCTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	HPBarWidget->SetupAttachment(RootComponent);

	//springarm-movement setup
	SpringArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 50.f), FRotator(-15.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

	//mesh setup
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WARRIOR(TEXT("/Game/ThirdPersonBP/Blueprints/charactor/Sword_char/Paladin_Character.Paladin_Character"));
	if (SK_WARRIOR.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_WARRIOR.Object);
	}
	//anim setup
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_WARRIOR(TEXT("/Game/ThirdPersonBP/Blueprints/charactor/Sword_char/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (ANIM_WARRIOR.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ANIM_WARRIOR.Class);
	}
	//UI Setup
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBAR(TEXT("/Game/UI/HPBAR.HPBar_C"));
	if (UI_HPBAR.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HPBAR.Class);
	}




	//variable initialize
	IsAttacking = false;
	MaxCombo = 3;
	AttackRange = 170.f;
	AttackRadius = 80.f;
	IsShieldUp = false;
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	//collision profile
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("DHCharacter"));	
}

// Called when the game starts or when spawned
void ADHCharacter::BeginPlay()
{
	Super::BeginPlay();

	//character widget bind/add viewport
	auto CharacterWidget = Cast<UDHCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != CharacterWidget)
	{
		CharacterWidget->BindCharacterStat(CharacterStat);
	}
	CharacterWidget->AddToViewport();
}

// Called every frame
void ADHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

// Called to bind functionality to input
void ADHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ADHCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ADHCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ADHCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADHCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("ShieldUp"), IE_Pressed, this, &ADHCharacter::ShieldUp);
	PlayerInputComponent->BindAction(TEXT("ShieldUp"), IE_Released, this, &ADHCharacter::ShieldDown);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ADHCharacter::Attack);

}
	
void ADHCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DHAnim = Cast<UDHAnimInstance>(GetMesh()->GetAnimInstance());
	DHCHECK(nullptr != DHAnim);
	DHAnim->OnMontageEnded.AddDynamic(this, &ADHCharacter::OnAttackMontageEnded);
	//OnNextAttackCheck가 Broadcast될 때 IsComboInputOn이라면 Montage의 섹션을 CurrentCombo로 진행
	DHAnim->OnNextAttackCheck.AddLambda([this]() -> void {
		CanNextCombo = false;
		if (IsComboInputOn)
		{
			AttackStartComboState();
			DHAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});
	DHAnim->OnAttackHitCheck.AddUObject(this, &ADHCharacter::AttackCheck);
	//HP 0일때
	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		DHLOG(Warning, TEXT("OnHPIsZero"));
		DHAnim->SetDeadAnim();
		HPBarWidget->SetHiddenInGame(true);
		SetActorEnableCollision(false);
		isdead = true;
		});
}

void ADHCharacter::UpDown(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void ADHCharacter::LeftRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void ADHCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void ADHCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

bool ADHCharacter::CanSetWeapon()
{
	return (nullptr == CurrentWeapon);
}

bool ADHCharacter::CanSetShield()
{
	return (nullptr == CurrentShield);
}

void ADHCharacter::SetWeapon(class ADHSword* NewWeapon)
{
	DHCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	FName WeaponSocket(TEXT("WeaponHold"));
	if (nullptr != NewWeapon)
	{
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
	}
}

void ADHCharacter::SetShield(class ADHShield* NewShield)
{
	DHCHECK(nullptr != NewShield && nullptr == CurrentShield);
	FName ShieldSocket(TEXT("ShieldHold"));
	if (nullptr != NewShield)
	{
		NewShield->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ShieldSocket);
		NewShield->SetOwner(this);
		CurrentShield = NewShield;
	}
}

void ADHCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	DHCHECK(IsAttacking);
	DHCHECK(CurrentCombo > 0);
	IsAttacking = false;
	AttackEndComboState();
	OnAttackEnd.Broadcast();
}

void ADHCharacter::Attack()
{
	if(CurrentWeapon != nullptr && !IsShieldUp)
	{
		//공격 도중 인풋이 들어온다면 IsComboInputOn을 true로
		if (IsAttacking)
		{
			DHCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
			if (CanNextCombo)
			{
				IsComboInputOn = true;
			}
		}
		//공격 도중이 아니라면
		else
		{
			DHCHECK(CurrentCombo == 0);
			AttackStartComboState();
			DHAnim->PlayAttackMontage();
			DHAnim->JumpToAttackMontageSection(CurrentCombo);
			IsAttacking = true;
		}
		GetCharacterMovement()->DisableMovement();
	}
}

void ADHCharacter::UseItem(class UItemBase* Item)
{
	if (Item)
	{
		Item->Use(this);
	}
}

void ADHCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	DHCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo -1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo +1, 1, MaxCombo);
}

void ADHCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ADHCharacter::AttackCheck()
{
	TArray <FHitResult> HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
	HitResult,
	GetActorLocation(),
	GetActorLocation() + GetActorForwardVector() * AttackRange,
	FQuat::Identity,
	ECollisionChannel::ECC_GameTraceChannel3,
	FCollisionShape::MakeSphere(AttackRadius),
	Params);

//#if ENABLE_DRAW_DEBUG
//	FVector TraceVec = GetActorForwardVector() * AttackRange;
//	FVector Center = GetActorLocation() + TraceVec * 0.5f;
//	float HalfHeight = AttackRange * 0.5f + AttackRadius;
//	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
//	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
//	float DebugLifeTime = 0.5f;
//
//	DrawDebugCapsule(GetWorld(),
//		Center,
//		HalfHeight,
//		AttackRadius,
//		CapsuleRot,
//		DrawColor,
//		false,
//		DebugLifeTime);
//#endif

	if (bResult)
	{
		for (auto& hitresult : HitResult)
		{
			if (hitresult.Actor.IsValid())
			{
				FDamageEvent DamageEvent;
				//CharacterStat의 Attack수치만큼 대미지
				hitresult.GetActor()->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
			}
		}
	}
}

void ADHCharacter::ShieldUp()
{
	if (!CanSetShield() && !IsAttacking)
	{
		IsShieldUp = true;
		DHAnim->SetShieldUp();
		GetCharacterMovement()->DisableMovement();
	}
}

void ADHCharacter::ShieldDown()
{
	if (!CanSetShield() && !IsAttacking)
	{
		IsShieldUp = false;
		DHAnim->SetShieldDown();
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

float ADHCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//방어중&&올바른 방향이라면
	if (IsShieldUp == true && ShieldAngleCheck(DamageCauser) == true)
	{
		return FinalDamage;
	}
	else
	{	//방어안함||올바른 방향이 아니면
		CharacterStat->SetDamage(FinalDamage);
		return FinalDamage;
	}
}

float ADHCharacter::TakeHeal(float HealAmout)
{
	CharacterStat->SetHeal(HealAmout);
	return HealAmout;
}

bool ADHCharacter::ShieldAngleCheck(AActor* DamageCauser)
{
	float Defendangle = GetActorRotation().Yaw - DamageCauser->GetActorRotation().Yaw;
	if (Defendangle > 150.f && Defendangle < 210.f)
	{
		return true;
	}
	if (Defendangle < -150.f && Defendangle > -210.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}