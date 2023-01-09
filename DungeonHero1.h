// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(DungeonHero1, Log, All);

#define DHLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define DHLOG_S(Verbosity) UE_LOG(DungeonHero1, Verbosity, TEXT("%s"), *DHLOG_CALLINFO)
#define DHLOG(Verbosity, Format, ...) UE_LOG(DungeonHero1, Verbosity, TEXT("%s %s"), *DHLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define DHCHECK(Expr, ...) {if(!(Expr)) {DHLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}