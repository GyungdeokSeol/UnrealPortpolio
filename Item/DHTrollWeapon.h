// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "GameFramework/Actor.h"
#include "DHTrollWeapon.generated.h"

UCLASS()
class DUNGEONHERO1_API ADHTrollWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADHTrollWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Weapon;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UCapsuleComponent* ACollision;

};
