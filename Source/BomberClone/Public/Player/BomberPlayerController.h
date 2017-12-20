// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Bomb.h"
#include "BomberPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERCLONE_API ABomberPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
	virtual void SetupInputComponent() override;
	
	void InputForward(float Axis);
	void InputRight(float Axis);
	void InputAction();
};
