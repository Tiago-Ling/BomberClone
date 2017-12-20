// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "DestructibleBlock.generated.h"

UCLASS()
class BOMBERCLONE_API ADestructibleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleBlock();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UParticleSystemComponent* Explosion;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	void HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void OnExplosionFinished(UParticleSystemComponent* PSystem);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
