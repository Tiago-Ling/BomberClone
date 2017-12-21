// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharacter.h"
#include "BomberPlayerController.h"
#include "DestructibleBlock.h"
#include "IndestructibleBlock.h"
#include "GameFramework/PlayerStart.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
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
	
	ABomberCloneGameModeBase();

	virtual void BeginPlay() override;

	//APlayerStart* P1Start;
	//APlayerStart* P2Start;

protected:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
};
