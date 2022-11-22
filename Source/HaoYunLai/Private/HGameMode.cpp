// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameMode.h"

#include "HDoor.h"
#include "Kismet/GameplayStatics.h"

void AHGameMode::StartPlay()
{
	Super::StartPlay();

	MatchDoor();
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

void AHGameMode::ApplyElectricityChanged(float Detal)
{
	Electricity += Detal;
	Electricity = FMath::Clamp(Electricity, 0, MAXElectricity);
}

void AHGameMode::ApplyMaxElectricityChanged(float Detal)
{
	MAXElectricity += Detal;
	Electricity = FMath::Clamp(Electricity, 0, MAXElectricity);
}
