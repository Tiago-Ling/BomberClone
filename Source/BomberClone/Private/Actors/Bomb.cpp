// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"


// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH COMP"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	Mesh->AddRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	Mesh->SetStaticMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Concrete_Tiles.M_Concrete_Tiles"));
	Mesh->SetMaterial(0, MaterialAsset.Object);

	RootComponent = Mesh;

	Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("P_Explosion"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	Explosion->SetTemplate(ParticleAsset.Object);
	Explosion->bAutoActivate = false;
	Explosion->bAutoDestroy = true;
	Explosion->SetupAttachment(RootComponent);
	Explosion->OnSystemFinished.AddDynamic(this, &ABomb::OnExplosionFinished);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
	//Start bomb timer
	GetWorld()->GetTimerManager().SetTimer(BombTimer, this, &ABomb::OnTimerFinished, 5.0f, false);
}

void ABomb::OnTimerFinished()
{
	// TODO : Explode bomb
	Explosion->Activate(true);
	Mesh->ToggleVisibility(false);

	// TODO : Spawn 4 trails, up, down, left and right
	FVector Location = GetActorLocation();
	FRotator FRotation = GetActorForwardVector().ToOrientationRotator();
	FRotator BRotation = (GetActorForwardVector() * -1).ToOrientationRotator();
	FRotator RRotation = GetActorRightVector().ToOrientationRotator();
	FRotator LRotation = (GetActorRightVector() * -1).ToOrientationRotator();
	FActorSpawnParameters SpawnInfo;
	
	Trails.Add(GetWorld()->SpawnActor<AFireTrail>(Location + FVector(50.0f, 0.0f, 0.0f), FRotation, SpawnInfo));
	Trails.Add(GetWorld()->SpawnActor<AFireTrail>(Location + FVector(-50.0f, 0.0f, 0.0f), BRotation, SpawnInfo));
	Trails.Add(GetWorld()->SpawnActor<AFireTrail>(Location + FVector(0.0f, 50.0f, 0.0f), RRotation, SpawnInfo));
	Trails.Add(GetWorld()->SpawnActor<AFireTrail>(Location + FVector(0.0f, -50.0f, 0.0f), LRotation, SpawnInfo));

}

void ABomb::OnExplosionFinished(UParticleSystemComponent * PSystem)
{
	// TODO : Destroy all trails and the bomb itself
	for (int32 i = 0; i < Trails.Num(); i++) {
		AFireTrail* Trail = Trails[i];
		Trail->PSystem->Deactivate();
	}
	Destroy();

	// TODO : Stop and clear timer

}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

