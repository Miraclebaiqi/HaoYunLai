// Fill out your copyright notice in the Description page of Project Settings.


#include "HSpreadBase.h"

#include "HRoomBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHSpreadBase::AHSpreadBase()
{
	SpreadName = "Spread";
	SpreadDamage = 0.0f;
	ActiveTimeInterval = 5.0f;
}

void AHSpreadBase::SpreadLogic()
{
	UKismetSystemLibrary::PrintString(this,TEXT("这里是蔓延物逻辑运行,请在子类中重写该函数"), true, false, FLinearColor::White, 3.0f);
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

float AHSpreadBase::GetActiveTimeInterval() const
{
	return ActiveTimeInterval;
}
