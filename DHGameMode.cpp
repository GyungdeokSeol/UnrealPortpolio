// Fill out your copyright notice in the Description page of Project Settings.


#include "DHGameMode.h"
#include "Actor/Character/DHCharacter.h"
#include "Controller/DHPlayerController.h"

ADHGameMode::ADHGameMode()
{
	static ConstructorHelpers::FClassFinder<ADHCharacter> BP_Char(TEXT("Blueprint'/Game/MyDHCharacter.MyDHCharacter'"));
	if (BP_Char.Succeeded())
	{
		DefaultPawnClass = BP_Char.Class;
	}
	PlayerControllerClass = ADHPlayerController::StaticClass();
}