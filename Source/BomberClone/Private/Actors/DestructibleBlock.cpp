// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleBlock.h"


// Sets default values
ADestructibleBlock::ADestructibleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags.Add(FName(TEXT("DestructibleBlock")));
	
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAP COMP"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionObjectType(ECC_WorldDynamic);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	OverlapComp->SetBoxExtent(FVector(50.0f));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleBlock::HandleOverlap);
	RootComponent = OverlapComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH COMP"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	Mesh->SetStaticMesh(MeshAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Concrete_Grime.M_Concrete_Grime"));
	Mesh->SetMaterial(0, MaterialAsset.Object);

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("P_Explosion"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	Explosion->SetTemplate(ParticleAsset.Object);
	Explosion->bAutoActivate = false;
	Explosion->bAutoDestroy = true;
	Explosion->SetupAttachment(RootComponent);
	Explosion->OnSystemFinished.AddDynamic(this, &ADestructibleBlock::OnExplosionFinished);

}

// Called when the game starts or when spawned
void ADestructibleBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructibleBlock::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BLOCK Overlapped!"));
	
	if (OtherActor->ActorHasTag(FName(TEXT("DestructibleBlock"))))
		return;

	Mesh->DestroyComponent();
	Explosion->Activate(true);

	// TODO: Chance to spawn power-up
	
}

void ADestructibleBlock::OnExplosionFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

// Called every frame
void ADestructibleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}