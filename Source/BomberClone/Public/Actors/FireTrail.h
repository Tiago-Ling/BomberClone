// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "FireTrail.generated.h"

UCLASS()
class BOMBERCLONE_API AFireTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireTrail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void OnFireFinished(UParticleSystemComponent* PSystem);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	void HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* PSystem;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* OverlapComp;
	
};
