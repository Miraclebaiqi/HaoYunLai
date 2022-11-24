// Fill out your copyright notice in the Description page of Project Settings.


#include "HRobot.h"

#include "HRoomBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHRobot::AHRobot()
{
	MaxDurability = 100.0f;
	Durability = 100.0f;
	BeginRoomID = 0;
}

void AHRobot::RobotInitialized()
{
	TArray<AActor*> Rooms;
	UGameplayStatics::GetAllActorsOfClass(this,AHRoomBase::StaticClass(),Rooms);

	for (AActor* RoomActor : Rooms)
	{
		AHRoomBase* Room = Cast<AHRoomBase>(RoomActor);
		if (Room && Room->GetRoomID() == BeginRoomID)
		{
			Room->RoomFocusOn();
			UKismetSystemLibrary::PrintString(this,TEXT("成功聚焦起始房间"), true, false, FLinearColor::White, 3.0f);
			return;
		}
	}
	UKismetSystemLibrary::PrintString(this,TEXT("未能找到起始房间，请重新配置相关参数"), true, false, FLinearColor::Red, 30.0f);
}

void AHRobot::ApplyDurabilityChanged(float Delta)
{
	Durability += Delta;
	Durability = FMath::Clamp(Durability,0,MaxDurability);
	OnRobotDurabilityChanged.Broadcast(this);
}


void AHRobot::ApplyMaxDurabilityChanged(float Delta)
{
	MaxDurability += Delta;
	OnRobotDurabilityChanged.Broadcast(this);
}

float AHRobot::GetDurability() const
{
	return Durability;
}

float AHRobot::GetMaxDurability() const
{
	return MaxDurability;
}