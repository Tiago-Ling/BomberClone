// Fill out your copyright notice in the Description page of Project Settings.

#include "FireTrail.h"


// Sets default values
AFireTrail::AFireTrail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAP COMP"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionObjectType(ECC_WorldDynamic);
	OverlapComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(40.0f));
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFireTrail::HandleOverlap);
	OverlapComp->bHiddenInGame = false;
	RootComponent = OverlapComp;

	PSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("P_Fire"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	PSystem->SetTemplate(ParticleAsset.Object);
	PSystem->bAutoActivate = false;
	PSystem->bAutoDestroy = true;
	PSystem->SetupAttachment(RootComponent);
	PSystem->OnSystemFinished.AddDynamic(this, &AFireTrail::OnFireFinished);
}

// Called when the game starts or when spawned
void AFireTrail::BeginPlay()
{
	Super::BeginPlay();

	const FVector RayStart = GetActorLocation();
	const FVector Direction = GetActorRotation().Vector();
	const FVector RayEnd = RayStart + (Direction * 150.0f);

	FCollisionQueryParams RayParameters(TEXT("TraceWallCollision"), true, this);
	RayParameters.bTraceAsyncScene = false;
	RayParameters.bReturnPhysicalMaterial = false;
	RayParameters.bTraceComplex = false;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, RayStart, RayEnd, ECC_Visibility, RayParameters);
	DrawDebugLine(GetWorld(), RayStart, RayEnd, FColor::Green, false, 10.0f);

	const FVector Extents = FVector((RayEnd - RayStart).Size() / 2, 40.0f, 40.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Box Extents length : %f, %f, %f"), Extents.X, Extents.Y, Extents.Z);

	FVector BoxLocation = RayStart + (Direction * 75.0f);
	BoxLocation.Z = 60.0f;
	OverlapComp->SetWorldLocation(BoxLocation, false, nullptr, ETeleportType::TeleportPhysics);
	OverlapComp->SetBoxExtent(Extents);

	//DrawDebugSolidBox(GetWorld(), RayStart, Extents, FColor::Blue, false, 10.0f);

	PSystem->Activate(true);
}

// Called every frame
void AFireTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireTrail::OnFireFinished(UParticleSystemComponent * PSystem)
{
	UE_LOG(LogTemp, Warning, TEXT("Trail Stopped"));
	//Destroy();
}

void AFireTrail::HandleOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Trail Overlapped!"));
}

