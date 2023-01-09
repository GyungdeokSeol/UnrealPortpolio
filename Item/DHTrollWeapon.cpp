// Fill out your copyright notice in the Description page of Project Settings.


#include "DHTrollWeapon.h"

// Sets default values
ADHTrollWeapon::ADHTrollWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WEAPON(TEXT("/Game/InfinityBladeAdversaries/Enemy/Enemy_Troll/Meshes/SM_Troll_hammer.SM_Troll_hammer"));
	if (SM_WEAPON.Succeeded())
	{
		Weapon->SetStaticMesh(SM_WEAPON.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	ACollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ACOLLISION"));
	ACollision->SetupAttachment(RootComponent);
	ACollision->SetRelativeLocationAndRotation(FVector(-10.f, -75.f, 0.f), FRotator(-90.f, 90.f, 0.f));
	ACollision->SetCapsuleSize(30.f, 70.f);
	ACollision->SetCollisionProfileName(TEXT("ACollision"));


}

// Called when the game starts or when spawned
void ADHTrollWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

