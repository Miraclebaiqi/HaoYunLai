// Fill out your copyright notice in the Description page of Project Settings.


#include "HRoomBase.h"

#include "HDoor.h"
#include "HItemInRoom.h"
#include "HSpreadBase.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHRoomBase::AHRoomBase()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	RootComponent = CameraComp;

	CaptureComp2D = CreateDefaultSubobject<USceneCaptureComponent2D>("CaptureComp2D");
	CaptureComp2D->SetupAttachment(CameraComp);

	IsFocused = false;
	IsView = false;
	IsBroken = false;
	
}



void AHRoomBase::InitializeDoors()
{
	for (AHDoor* Door : Doors)
	{
		if (Door != nullptr)
		{
			Door->SetOwnerRoom(this);
			Door->IsActive = false;
		}
	}
}

void AHRoomBase::InitializeItems()
{
	for (AHItemInRoom* Item : Items)
	{
		if (Item != nullptr)
		{
			Item->IsActive = false;
		}
	}
}

void AHRoomBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InitializeDoors();
	InitializeItems();
}

//给房间添加蔓延物 同种蔓延物不会重复添加
void AHRoomBase::AddSpread(AHSpreadBase* Spread)
{
	for (AHSpreadBase* TempSpread : Spreads)
	{
		if(TempSpread->GetSpreadName() == Spread->GetSpreadName())
		{
			UKismetSystemLibrary::PrintString(this,TEXT("蔓延物已经存在，不再重复添加"), true, false, FLinearColor::White, 3.0f);
			return;
		}
	}
	Spread->SetOwnerRoom(this);
	Spreads.Add(Spread);
	UKismetSystemLibrary::PrintString(this,TEXT("蔓延物添加到房间"), true, false, FLinearColor::White, 3.0f);
	// 蔓延物发生变化时通知UI，UI根据自己的ID是否与房间匹配进行相应的变化
	OnRoomSpreadChanged.Broadcast(this);
}

//给房间移除蔓延物
void AHRoomBase::RemoveSpread(AHSpreadBase* Spread)
{
	for (int Index = 0; Index < Spreads.Num(); ++Index)
	{
		if(Spreads[Index]->GetSpreadName() == Spread->GetSpreadName())
		{
			UKismetSystemLibrary::PrintString(this,TEXT("蔓延物从房间移除"), true, false, FLinearColor::White, 3.0f);
			Spreads.RemoveAt(Index);
			
			// 蔓延物发生变化时通知UI，UI根据自己的ID是否与房间匹配进行相应的变化
			OnRoomSpreadChanged.Broadcast(this);
			return;
		}
	}
}

//聚焦该房间，房间内物品变得可交互
void AHRoomBase::RoomFocusOn()
{
	for (AHDoor* Door : Doors)
	{
		if (Door != nullptr)
		{
			Door->IsActive = true;
		}
	}
	for (AHItemInRoom* Item : Items)
	{
		if (Item != nullptr)
		{
			Item->IsActive = true;
		}
	}
	
	IsFocused = true;
	
	//当房间的聚焦情况发生变化时通知UI，UI根据自己的ID是否与房间匹配进行相应的变化
	OnRoomFocusChanged.Broadcast(this);
}

//失焦该房间，房间内物品均不可交互
void AHRoomBase::RoomOutOfFocus()
{
	for (AHDoor* Door : Doors)
	{
		if (Door != nullptr)
		{
			Door->IsActive = false;
		}
	}
	for (AHItemInRoom* Item : Items)
	{
		if (Item != nullptr)
		{
			Item->IsActive = false;
		}
	}
	
	IsFocused = false;
	
	//当房间的聚焦情况(激活情况)发生变化时通知UI，UI根据自己的ID是否与房间匹配进行相应的变化
	OnRoomFocusChanged.Broadcast(this);
}

void AHRoomBase::ApplyRoomLight(bool IsHidden)
{
	for (AActor* Light : Lights)
	{
		if (IsValid(Light))
		{
			Light->SetActorHiddenInGame(IsHidden);
		}
	}
}

void AHRoomBase::SetIsView(bool IsViewCamera)
{
	IsView = IsViewCamera;

	//当房间的摄像机视角发生变化时通知UI，UI根据自己的ID是否与房间匹配进行相应的变化
	OnRoomViewChanged.Broadcast(this);
}

void AHRoomBase::SetIsBroken(bool IsCameraBroken)
{
	IsBroken = IsCameraBroken;

	//当房间摄像机使用情况发生变化时通知UI,UI根据自己的ID是否与房间匹配进行相应的变化
	OnRoomBrokenChanged.Broadcast(this);
}

void AHRoomBase::SetRoomIsInfected(bool IsRoomInfected)
{
	IsInfected = IsRoomInfected;
	//当房间被菌毯感染的时候
	OnRoomInfectedChanged.Broadcast(this);
}

int32 AHRoomBase::GetRoomID() const
{
	return RoomID;
}

bool AHRoomBase::GetIsFocused() const
{
	return IsFocused;
}

bool AHRoomBase::GetIsView() const
{
	return IsView;
}

bool AHRoomBase::GetIsBroken() const
{
	return IsBroken;
}

bool AHRoomBase::GetIsInfected() const
{
	return IsInfected;
}

TArray<AHDoor*> AHRoomBase::GetDoors()
{
	return Doors;
}

TArray<AHSpreadBase*> AHRoomBase::GetSpreads()
{
	return Spreads;
}







