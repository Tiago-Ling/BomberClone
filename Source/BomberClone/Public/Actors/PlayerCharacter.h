// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "Bomb.h"
#include "BomberPlayerController.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BOMBERCLONE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USkeletalMeshComponent* MeshComp;

	UMaterialInstanceDynamic* P1Material;
	UMaterialInstanceDynamic* P2Material;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
