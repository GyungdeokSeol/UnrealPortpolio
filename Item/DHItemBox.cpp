// Fill out your copyright notice in the Description page of Project Settings.


#include "DHItemBox.h"
#include "DHSword.h"
#include "../Actor/Character/DHCharacter.h"
#include "Components/WidgetComponent.h"

// Sets default values
ADHItemBox::ADHItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//subobject설정
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger1 = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER1"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	NamePlate = CreateDefaultSubobject<UWidgetComponent>(TEXT("NAMEPLATE"));
	//컴포넌트 붙이기
	RootComponent = Trigger;
	Trigger1->SetupAttachment(RootComponent);
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);
	NamePlate->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.f, 42.f, 30.f));
	Trigger1->InitSphereRadius(500.f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	Box->SetRelativeLocation(FVector(0.f, -3.5f, -30.f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Trigger1->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = ADHSword::StaticClass();
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	NamePlate->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	NamePlate->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_NAMEPLATE(TEXT("/Game/UI/UI_WeaponBox.UI_WeaponBox_C"));
	if (UI_NAMEPLATE.Succeeded())
	{
		NamePlate->SetWidgetClass(UI_NAMEPLATE.Class);
		NamePlate->SetDrawSize(FVector2D(300.f, 60.f));
	}
	NamePlate->SetHiddenInGame(true);



}

// Called when the game starts or when spawned
void ADHItemBox::BeginPlay()
{
	Super::BeginPlay();

}

void ADHItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADHItemBox::OnCharacterOverlap);
	Trigger1->OnComponentBeginOverlap.AddDynamic(this, &ADHItemBox::OnCharcterInRange);
	Trigger1->OnComponentEndOverlap.AddDynamic(this, &ADHItemBox::OnCharacterOutRange);
}

void ADHItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DHLOG(Warning, TEXT("WeaponOverlap"));

	auto DHCharacter = Cast<ADHCharacter>(OtherActor);
	DHCHECK(nullptr != DHCharacter);

	if (nullptr != DHCharacter && nullptr != WeaponItemClass)
	{
		if (DHCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<ADHSword>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			DHCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			NamePlate->SetHiddenInGame(true);

			Effect->OnSystemFinished.AddDynamic(this, &ADHItemBox::OnEffectFinished);
		}
		else
		{
			DHLOG(Warning, TEXT("%s can't equip weapon"), *DHCharacter->GetName());
		}
	}
}

void ADHItemBox::OnCharcterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		NamePlate->SetHiddenInGame(false);
	}
}

void ADHItemBox::OnCharacterOutRange(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		NamePlate->SetHiddenInGame(true);
	}
}

void ADHItemBox::OnEffectFinished(class UParticleSystemComponent* PSystem)
{
	Destroy();
}