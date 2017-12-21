// Fill out your copyright notice in the Description page of Project Settings.

#include "IndestructibleBlock.h"


// Sets default values
AIndestructibleBlock::AIndestructibleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags.Add(FName("IndestructibleBlock"));

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAP COMP"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OverlapComp->SetCollisionObjectType(ECC_WorldStatic);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	OverlapComp->SetBoxExtent(FVector(50.0f));
	OverlapComp->ComponentTags.Add(FName("IndestructibleBlock"));
	RootComponent = OverlapComp;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH COMP"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	Mesh->SetStaticMesh(MeshAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Concrete_Panels.M_Concrete_Panels"));
	Mesh->SetMaterial(0, MaterialAsset.Object);
}

// Called when the game starts or when spawned
void AIndestructibleBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndestructibleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

