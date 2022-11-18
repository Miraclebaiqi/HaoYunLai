// Fill out your copyright notice in the Description page of Project Settings.


#include "HRoomBase.h"

#include "HDoor.h"
#include "HSpreadBase.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AHRoomBase::AHRoomBase()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	RootComponent = CameraComp;

	CaptureComp2D = CreateDefaultSubobject<USceneCaptureComponent2D>("CaptureComp2D");
	CaptureComp2D->SetupAttachment(CameraComp);
	
}


void AHRoomBase::InitializeDoor()
{
	for (int Index = 0; Index < Doors.Num(); Index++)
	{
		if (Doors[Index] == nullptr)
		{
			break;
		}
		Doors[Index]->SetOwnerRoom(this);
	}
}

void AHRoomBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InitializeDoor();
}

//给房间添加蔓延物 同种蔓延物不会重复添加
void AHRoomBase::AddSpread(AHSpreadBase* Spread)
{
	for (int Index = 0; Index < Spreads.Num(); ++Index)
	{
		if(Spreads[Index]->GetSpreadName() == Spread->GetSpreadName())
		{
			UE_LOG(LogTemp,Log,TEXT("蔓延物已经存在，不再重复添加"))
			return;
		}
	}
	Spread->SetOwnerRoom(this);
	Spreads.Add(Spread);
}

//给房间移除蔓延物
void AHRoomBase::RemoveSpread(AHSpreadBase* Spread)
{
	for (int Index = 0; Index < Spreads.Num(); ++Index)
	{
		if(Spreads[Index]->GetSpreadName() == Spread->GetSpreadName())
		{
			UE_LOG(LogTemp,Log,TEXT("蔓延物从房间移除"))
			Spreads.RemoveAt(Index);
			return;
		}
	}
}

ACameraActor* AHRoomBase::GetCamera()
{
	return Cast<ACameraActor>(CameraComp);
}

