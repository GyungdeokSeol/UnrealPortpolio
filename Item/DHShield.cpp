// Fill out your copyright notice in the Description page of Project Settings.


#include "DHShield.h"

// Sets default values
ADHShield::ADHShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Shield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHIELD"));
	RootComponent = Shield;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SHIELD(TEXT("/Game/ThirdPersonBP/Blueprints/charactor/NewFolder/SK_Shield_Heater_mdl.SK_Shield_Heater_mdl"));
	if (SM_SHIELD.Succeeded())
	{
		Shield->SetStaticMesh(SM_SHIELD.Object);
	}
	Shield->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void ADHShield::BeginPlay()
{
	Super::BeginPlay();
	
}


