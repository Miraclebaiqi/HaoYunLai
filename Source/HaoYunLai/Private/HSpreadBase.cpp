// Fill out your copyright notice in the Description page of Project Settings.


#include "HSpreadBase.h"

#include "HDoor.h"
#include "HRobot.h"
#include "HRoomBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AHSpreadBase::AHSpreadBase()
{
	SpreadName = "Spread";
	SpreadDamageForDoor = 10.0f;
	SpreadDamageForRobot = 1.0f;
	SpreadTime = 15.0f;
	DamageTime = 1.0f;
}

void AHSpreadBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpreadTimerHandle,this,&AHSpreadBase::SpreadLogic,SpreadTime,true);
	GetWorldTimerManager().SetTimer(DamageTimerHandle,this,&AHSpreadBase::DamageLogic,DamageTime,true);
}

void AHSpreadBase::SpreadLogic()
{
	if (OwnerRoom)
	{
		bool IsAlive = false;
		for (AHDoor* Door : OwnerRoom->GetDoors())
		{
			if (!Door->GetDoorIsClosed())
			{
				Door->GetOwnerRoom()->AddSpread(this);
				IsAlive = true;
			}
		}
		if (!IsAlive)
		{
			OwnerRoom->RemoveSpread(this);
			DestroyedSpreadSelf();
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("蔓延物没有属于任何房间，即将销毁"), true, false, FLinearColor::White, 3.0f);
		DestroyedSpreadSelf();
	}
		
}

void AHSpreadBase::DamageLogic()
{
	//对机器人造成伤害
	if (OwnerRoom->GetIsFocused())
	{
		AHRobot* Robot = Cast<AHRobot>(UGameplayStatics::GetActorOfClass(this,AHRobot::StaticClass()));
		if (Robot)
		{
			Robot->ApplyDurabilityChanged(-SpreadDamageForRobot);
		}
	}
	//对门造成伤害
	for (AHDoor* Door : OwnerRoom->GetDoors())
	{
		if (!Door->GetDoorIsBroken())
		{
			Door->ApplyDoorDurabilityChanged(-SpreadDamageForDoor);
		}
	}
}

void AHSpreadBase::SetOwnerRoom(AHRoomBase* Room)
{
	OwnerRoom = Room;
}

AHRoomBase* AHSpreadBase::GetOwnerRoom() const
{
	return OwnerRoom;
}

FName AHSpreadBase::GetSpreadName() const
{
	return SpreadName;
}

void AHSpreadBase::DestroyedSpreadSelf()
{
	GetWorldTimerManager().ClearTimer(SpreadTimerHandle);
	GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	Destroy();
}


