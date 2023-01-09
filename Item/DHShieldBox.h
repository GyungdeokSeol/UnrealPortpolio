// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DungeonHero1.h"
#include "GameFramework/Actor.h"
#include "DHShieldBox.generated.h"

UCLASS()
class DUNGEONHERO1_API ADHShieldBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADHShieldBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	USphereComponent* Trigger1;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class ADHShield> WeaponItemClass;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = UI)
	class UWidgetComponent* NamePlate;

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCharcterInRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCharacterOutRange(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
