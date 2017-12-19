// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleBlock.h"


// Sets default values
ADestructibleBlock::ADestructibleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAP COMP"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(50.0f));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ADestructibleBlock::HandleOverlap);
	RootComponent = OverlapComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH COMP"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	UStaticMesh* MeshObject = MeshAsset.Object;
	Mesh->SetStaticMesh(MeshObject);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Concrete_Grime.M_Concrete_Grime"));
	UMaterialInterface* MaterialObject = MaterialAsset.Object;
	Mesh->SetMaterial(0, MaterialObject);

}

// Called when the game starts or when spawned
void ADestructibleBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructibleBlock::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped!"));

	// TODO: Handle fire trail overlaps by destroying this block

	// TODO: Chance to spawn power-up
}

// Called every frame
void ADestructibleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}