// Fill out your copyright notice in the Description page of Project Settings.

#include "BomberCloneGameModeBase.h"

ABomberCloneGameModeBase::ABomberCloneGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = ABomberPlayerController::StaticClass();
}

void ABomberCloneGameModeBase::BeginPlay()
{
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	Super::BeginPlay();
}

void ABomberCloneGameModeBase::SetupLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting level up!"));

	// Simple, temporary and naive implementation of random block placement
	for (int32 i = 0; i < 15; i++) {
		for (int32 j = 0; j < 9; j++) {

			//Place indestructible blocks in odd positions in the map
			if (i % 2 != 0 && j % 2 != 0) {
				FVector Location(j * 100.0f, i * 100.0f, 55.0f);
				Location.Y -= 700.0f;
				Location.X -= 400.0f;
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				GetWorld()->SpawnActor<AIndestructibleBlock>(Location, Rotation, SpawnInfo);

				continue;
			}

			// Avoids placing over player starts
			if ((i == 2 && j == 4) || (i == 12 && j == 4))
				continue;

			// 30% chance of placing destructible blocks 
			float Chance = FMath::RandRange(0.0f, 1.0f);
			if (Chance > 0.7f) {
				FVector Location(j * 100.0f, i * 100.0f, 55.0f);
				Location.Y -= 700.0f;
				Location.X -= 400.0f;
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				GetWorld()->SpawnActor<ADestructibleBlock>(Location, Rotation, SpawnInfo);
			}
		}
	}
}

AActor* ABomberCloneGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*> Starts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), Starts);

	APlayerController* PlayerController = Cast<APlayerController>(Player);
	ULocalPlayer* P = PlayerController->GetLocalPlayer();
	if (PlayerController && P) {
		
		int32 PId = P->GetControllerId();
		APlayerStart* SelectedStart = Cast<APlayerStart>(Starts[0]);
		for (int32 i = 0; i < Starts.Num(); i++) {
			APlayerStart* PStart = Cast<APlayerStart>(Starts[i]);
			if (PId == 0 && PStart->PlayerStartTag.IsEqual(FName(TEXT("P1")))) {
				SelectedStart = PStart;
				break;
			}
			else if (PId == 1 && PStart->PlayerStartTag.IsEqual(FName(TEXT("P2")))) {
				SelectedStart = PStart;
				break;
			}
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}
