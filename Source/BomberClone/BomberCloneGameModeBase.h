// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberCloneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERCLONE_API ABomberCloneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = BomberGame)
	void SetupLevel();
	
	
};
