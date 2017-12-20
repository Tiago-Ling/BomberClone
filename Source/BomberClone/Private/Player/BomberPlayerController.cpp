// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberPlayerController.h"

void ABomberPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	int32 PlayerId = GetLocalPlayer()->GetControllerId();
	if (PlayerId == 0) {
		InputComponent->BindAxis("Forward_P1", this, &ABomberPlayerController::InputForward);
		InputComponent->BindAxis("Right_P1", this, &ABomberPlayerController::InputRight);
		InputComponent->BindAction("Action_P1", IE_Pressed, this, &ABomberPlayerController::InputAction);
	}
	else if (PlayerId == 1) {
		InputComponent->BindAxis("Forward_P2", this, &ABomberPlayerController::InputForward);
		InputComponent->BindAxis("Right_P2", this, &ABomberPlayerController::InputRight);
		InputComponent->BindAction("Action_P2", IE_Pressed, this, &ABomberPlayerController::InputAction);
	}
}

void ABomberPlayerController::InputForward(float Axis)
{
	if (Axis != 0.f)
	{
		ACharacter* Controlled = GetCharacter();
		const FRotator Rotation = Controlled->GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		Controlled->AddMovementInput(Direction, Axis);
	}
}

void ABomberPlayerController::InputRight(float Axis)
{
	if (Axis != 0.f)
	{
		ACharacter* Controlled = GetCharacter();
		const FRotator Rotation = Controlled->GetActorRotation() * (90.0f * Axis);
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		Controlled->AddMovementInput(Direction, Axis);
	}
}

void ABomberPlayerController::InputAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Action!"));

	FVector Location = GetCharacter()->GetActorLocation();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ABomb>(Location, Rotation, SpawnInfo);
}
