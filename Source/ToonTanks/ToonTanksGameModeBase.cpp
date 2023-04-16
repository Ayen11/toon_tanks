// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedActor = Cast<ATower>(DeadActor))
	{
		DestroyedActor->HandleDestruction();
		--TargetTowers;
		if (TargetTowers <= 0.f)
		{
			GameOver(true);
			if (ToonTanksPlayerController)
			{
				ToonTanksPlayerController->SetPlayerEnabledState(false);
			}
		}
	}
}

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
}

void AToonTanksGameModeBase::HandleGameStart()
{	
	TargetTowers = GetTargetTowersCount();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();

	
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}

	FTimerHandle PlayerEnableTimerHandle; //our reference/name for the timer
	
	FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject( 
		ToonTanksPlayerController, //the object we want to pass the function into
		&AToonTanksPlayerController::SetPlayerEnabledState, //the function we want to initiate once the timer is up
		true //the value we want to pass into the function and the reason we packed this info into a TimerDelegate
		);
	
	GetWorldTimerManager().SetTimer(
		PlayerEnableTimerHandle, //calling the name of the handle we want (like the function name when creating 'timer by function name')
		PlayerEnableTimerDelegate, //passing the object we want to run the timer on (in bp we always used 'this' aka 'self' but here we want to call a function in a different class)
		StartDelay,
		false);
}

int32 AToonTanksGameModeBase::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(),Towers);
	return Towers.Num();
}
