// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "GameFramework/Actor.h"
#include "DHShield.generated.h"

UCLASS()
class DUNGEONHERO1_API ADHShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADHShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Shield;

};
