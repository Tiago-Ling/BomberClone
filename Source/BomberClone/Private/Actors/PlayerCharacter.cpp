// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = FindComponentByClass<USkeletalMeshComponent>();
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	MeshComp->SetSkeletalMesh(MeshAsset.Object);

	//Loading both player materials
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> P1MaterialAsset(TEXT("/Game/MaterialInstances/P1_Material.P1_Material"));
	P1Material = UMaterialInstanceDynamic::Create(P1MaterialAsset.Object, NULL);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> P2MaterialAsset(TEXT("/Game/MaterialInstances/P2_Material.P2_Material"));
	P2Material = UMaterialInstanceDynamic::Create(P2MaterialAsset.Object, NULL);

	// Animation blueprints must be loaded in a different way than other assets, otherwise they'll crash a packaged game (but will mislead you by working in the editor!)
	FString AnimClassStringTest = "Class'/Game/AnimStarterPack/CharacterAnimBP.CharacterAnimBP_C'";
	UClass* AnimationClass = LoadObject<UClass>(NULL, *AnimClassStringTest);
	if (!AnimationClass) return;

	MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	MeshComp->SetAnimInstanceClass(AnimationClass);
	MeshComp->AddRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	// Regular way of loading assets in constructor - won't work with animation blueprints !!!
	//MeshComp = FindComponentByClass<USkeletalMeshComponent>();
	//const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimAsset(TEXT("AnimBlueprint'/Game/AnimStarterPack/CharacterAnimBP.CharacterAnimBP'"));
	//MeshComp->SetAnimInstanceClass(AnimAsset.Object->GeneratedClass);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	APlayerController* PController = Cast<APlayerController>(Controller);
	if (MeshComp && PController) {
		int32 PId = PController->GetLocalPlayer()->GetControllerId();
		UE_LOG(LogTemp, Warning, TEXT("Controller ID : %i"), PId);
		if (PId == 0) {
			MeshComp->SetMaterial(0, P1Material);
		}
		else {
			MeshComp->SetMaterial(0, P2Material);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Material not set!!!"));
	}

	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

