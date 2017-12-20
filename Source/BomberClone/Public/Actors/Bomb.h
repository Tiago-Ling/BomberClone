// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "FireTrail.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERCLONE_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle BombTimer;
	TArray<AFireTrail*> Trails;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void OnTimerFinished();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void OnExplosionFinished(UParticleSystemComponent* PSystem);

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* Explosion;


	
};
