// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* MeshComp = FindComponentByClass<USkeletalMeshComponent>();
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	MeshComp->SetSkeletalMesh(MeshAsset.Object);

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimAsset(TEXT("/Game/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint"));
	MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	MeshComp->SetAnimInstanceClass(AnimAsset.Object->GeneratedClass);
	MeshComp->AddRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Forward", this, &APlayerCharacter::InputForward);
	InputComponent->BindAxis("Right", this, &APlayerCharacter::InputRight);
	InputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::InputAction);

}

void APlayerCharacter::InputForward(float Axis)
{
	if (Controller && Axis != 0.f)
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::InputRight(float Axis)
{
	if (Axis != 0.f)
	{
		const FRotator Rotation = GetActorRotation() * (90.0f * Axis);
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(Direction, Axis);
	}
}

void APlayerCharacter::InputAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Action!"));
}

