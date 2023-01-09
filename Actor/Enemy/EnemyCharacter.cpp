// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "DHMonsterStat.h"
#include "NormalMonsterAnim.h"
#include "../../UI/DHMonsterWidget1.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "../../Controller/NormalMonsterAICon.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Monster"));
	MonsterStat = CreateDefaultSubobject<UDHMonsterStat>(TEXT("MONSTERSTAT"));
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(GetMesh());
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBAR(TEXT("/Game/UI/MonsterHPBar.MonsterHPBar_C"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	if (UI_HPBAR.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HPBAR.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.f, 50.f));
	}
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("DHCharacter"));
	GetCapsuleComponent()->InitCapsuleSize(100.f, 100.f);

	AttackRange = 250.f;
	AttackRadius = 100.f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	HPBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 180.f));


	UITrigger = CreateDefaultSubobject<USphereComponent>(TEXT("UITRIGGER"));
	UITrigger->SetupAttachment(RootComponent);
	UITrigger->InitSphereRadius(500.f);
	UITrigger->SetCollisionProfileName(TEXT("ItemBox"));

	AIControllerClass = ANormalMonsterAICon::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto MonsterWidget = Cast<UDHMonsterWidget1>(HPBarWidget->GetUserWidgetObject());
	if (nullptr != MonsterWidget)
	{
		MonsterWidget->BindMonsterStat(MonsterStat);
	}
	HPBarWidget->SetHiddenInGame(true);

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	NormAnim = Cast<UNormalMonsterAnim>(GetMesh()->GetAnimInstance());
	DHCHECK(nullptr != NormAnim);
	NormAnim->OnMontageEnded.AddDynamic(this, &AEnemyCharacter::OnAttackMontageEnded);
	MonsterStat->OnHPIsZero.AddUObject(this, &AEnemyCharacter::SetDead);
	NormAnim->OnAttackHitCheck.AddUObject(this, &AEnemyCharacter::CloseAttackCheck);
	UITrigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnCharacterInRange);
	UITrigger->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnCharacterOutRange);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::CloseAttack()
{
	if (!IsAttacking)
	{
		NormAnim->PlayAttackMontage();
		IsAttacking = true;
	}
}

void AEnemyCharacter::CloseAttackCheck()
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
		for (auto& HitResults : HitResult)
		{
			if (HitResults.Actor.IsValid())
			{
				if(HitResults.GetActor()->ActorHasTag("Player"))
				{
					FDamageEvent DamageEvent;
					HitResults.GetActor()->TakeDamage(MonsterStat->GetAttack(), DamageEvent, GetController(), this);
				}
			}
		}
	}
}

bool AEnemyCharacter::IsDead()
{
	return IsDeath;
}

void AEnemyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

float AEnemyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	MonsterStat->SetDamage(FinalDamage);
	return FinalDamage;
}

void AEnemyCharacter::SetDead()
{
	NormAnim->SetDeadAnim();
	HPBarWidget->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	SetLifeSpan(5);
	IsDeath = true;
	GetCharacterMovement()->DisableMovement();
}

void AEnemyCharacter::OnCharacterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		HPBarWidget->SetHiddenInGame(false);
	}
}

void AEnemyCharacter::OnCharacterOutRange(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		HPBarWidget->SetHiddenInGame(true);
	}
}