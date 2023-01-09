// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../DungeonHero1.h"
#include "../EnemyCharacter.h"
#include "DHTroll.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONHERO1_API ADHTroll : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ADHTroll();
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class ADHTrollWeapon* Weapon;

	virtual void SetDead() override;
};
