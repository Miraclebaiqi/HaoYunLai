// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameMode.h"

#include "HDoor.h"
#include "Kismet/GameplayStatics.h"

AHGameMode::AHGameMode()
{
	RobotName = "Robot";
	Electricity = 100.0f;
	MaxElectricity = 100.0f;
	PowerRecover = 0.0;
	DefaultPowerCost = 1.5;
	MaintenancePowerCost = 3.0f;
}

void AHGameMode::StartPlay()
{
	Super::StartPlay();

	MatchDoor();

	GetWorldTimerManager().SetTimer(GameTimeCount, this, &AHGameMode::WriteGameRealTime, 1.0f, true);
}

float AHGameMode::CalculatePowerChanged()
{
	return PowerRecover - DefaultPowerCost;
}

void AHGameMode::WriteGameRealTime()
{
	GameRealTime += 1;
	ApplyElectricityChanged(CalculatePowerChanged());
}

void AHGameMode::MatchDoor()
{
	TArray<AActor*> ActorDoors;
	UGameplayStatics::GetAllActorsOfClass(this, AHDoor::StaticClass(), ActorDoors);

	for (AActor* ActorDoor : ActorDoors)
	{
		AHDoor* Door = Cast<AHDoor>(ActorDoor);
		if (Door)
		{
			//如果Door MatchingCode 为-1 则不进行匹配(若编码为正整数则认为是有效编码)
			if (Door->GetMatchingCode() > 0 && Door->GetConectedDoor() == nullptr)
			{
				bool DoOnceMatch = true;
				for (AActor* ActorDoor2 : ActorDoors)
				{
					AHDoor* Door2 = Cast<AHDoor>(ActorDoor2);
					if (Door2)
					{
						//寻找除自己外与自己匹配码相同的门
						if (Door2 != Door && Door2->GetMatchingCode() == Door->GetMatchingCode())
						{
							if (DoOnceMatch)
							{
								Door->SetConectedDoor(Door2);
								Door2->SetConectedDoor(Door);
								DoOnceMatch = false;
							}
							else
							{
								Door2->SetMatchingCode(-2);
							}
						}
					}
				}
			}
		}
	}
}


void AHGameMode::ContinueGameRealTime()
{
	GetWorldTimerManager().UnPauseTimer(GameTimeCount);
}

void AHGameMode::PauseGameRealTime()
{
	GetWorldTimerManager().PauseTimer(GameTimeCount);
}

void AHGameMode::ApplyElectricityChanged(float Detal)
{
	AHGameMode::Electricity += Detal;
	Electricity = FMath::Clamp(Electricity, 0, MaxElectricity);
	OnElectricityChanged.Broadcast(this);
	if (Electricity <= 0)
	{
		GameOver();
	}
}

void AHGameMode::ApplyMaxElectricityChanged(float Detal)
{
	MaxElectricity += Detal;
	Electricity = FMath::Clamp(Electricity, 0, MaxElectricity);
	OnElectricityChanged.Broadcast(this);
	if (Electricity <= 0)
	{
		GameOver();
	}
}

void AHGameMode::ApplyPowerRecoverChanged(float Delta)
{
	PowerRecover += Delta;
	FMath::Clamp(PowerRecover, 0, 20);
}

void AHGameMode::SetRobotName(FName BotName)
{
	RobotName = BotName;
}

int32 AHGameMode::GetGameRealTime() const
{
	return GameRealTime;
}

float AHGameMode::GetMaintenancePowerCost() const
{
	return MaintenancePowerCost;
}

void AHGameMode::GameOver()
{
	UE_LOG(LogTemp, Log, TEXT("你寄了"));
}
