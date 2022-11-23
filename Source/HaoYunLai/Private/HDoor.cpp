// Fill out your copyright notice in the Description page of Project Settings.


#include "HDoor.h"

#include "HPlayer.h"
#include "HRobot.h"
#include "HRoomBase.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AHDoor::AHDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	InDoorPoint = CreateDefaultSubobject<UCapsuleComponent>("InDoorPoint");
	InDoorPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InDoorPoint->SetCapsuleHalfHeight(88.0f);
	InDoorPoint->SetCapsuleRadius(34.0f);
	InDoorPoint->SetupAttachment(RootComponent);

	OutDoorPoint = CreateDefaultSubobject<UCapsuleComponent>("OutDoorPoint");
	OutDoorPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OutDoorPoint->SetCapsuleHalfHeight(88.0f);
	OutDoorPoint->SetCapsuleRadius(34.0f);
	OutDoorPoint->SetupAttachment(RootComponent);

	ArrowCompIn = CreateDefaultSubobject<UArrowComponent>("ArrowCompIn");
	ArrowCompIn->SetupAttachment(InDoorPoint);

	ArrowCompOut = CreateDefaultSubobject<UArrowComponent>("ArrowCompOut");
	ArrowCompOut->SetupAttachment(OutDoorPoint);

	IsClose = false;
	IsBroken = false;
	MatchingCode = -1;
	MaxDurability = 100.0f;
	Durability = 100.0f;
}


bool AHDoor::SwitchDoor()
{
	//如果门没坏，则切换门的开关状态
	if (!IsBroken)
	{
		SetDoorIsClose(!IsClose);
		AnimationDoor(IsClose);
		AssimilateConnectedDoor();
		return true;
	}
	//如果门坏了，则不能切换状态
	return false;
}

void AHDoor::BrokeDoor()
{
	//如果门是关闭状态，则会被强行打开
	if (IsClose)
	{
		SetDoorIsClose(false);
		AnimationDoor(false);
	}
	SetDoorIsBroken(true);
	AssimilateConnectedDoor();
}

void AHDoor::FixDoor()
{
	SetDoorIsBroken(false);
	Durability = MaxDurability;
}

//连接门的同化操作
bool AHDoor::AssimilateConnectedDoor()
{
	if (ConnectedDoor)
	{
		ConnectedDoor->SetDoorIsBroken(IsBroken);
		if (!IsBroken)
		{
			ConnectedDoor->SetDoorIsClose(IsClose);
			ConnectedDoor->AnimationDoor(IsClose);
		}
		return true;
	}
	return false;
}


//门触发了交互
void AHDoor::Interact_Implementation(APawn* InstigatorActor)
{
	if (IsActive)
	{
		AHRobot* ActorRobot = Cast<AHRobot>(UGameplayStatics::GetActorOfClass(this, AHRobot::StaticClass()));
		if (ActorRobot)
		{
			ActorRobot->MoveToTarget(this);
			UKismetSystemLibrary::PrintString(this,TEXT("机器人走到门前"), true, false, FLinearColor::White, 3.0f);
		}
		else
		{
			UKismetSystemLibrary::PrintString(this,TEXT("场景中没有可控制的机器人"), true, false, FLinearColor::Yellow, 10.0f);
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("你的门并没有激活"), true, false, FLinearColor::Yellow, 10.0f);
	}
}

//机器人进入新房间(聚焦新房间，失焦当前房间)
void AHDoor::ActiveNextRoom()
{
	if (ConnectedDoor)
	{
		GetOwnerRoom()->RoomOutOfFocus();
		ConnectedDoor->GetOwnerRoom()->RoomFocusOn();
	}
}


bool AHDoor::GetDoorIsBroken() const
{
	return IsBroken;
}

bool AHDoor::GetDoorIsClosed() const
{
	return IsClose;
}

int32 AHDoor::GetMatchingCode()
{
	return MatchingCode;
}

AHDoor* AHDoor::GetConectedDoor()
{
	return ConnectedDoor;
}

AHRoomBase* AHDoor::GetOwnerRoom()
{
	return OwnerRoom;
}

FVector AHDoor::GetInDoorLoaction()
{
	return InDoorPoint->GetComponentLocation();
}

FVector AHDoor::GetOutDoorLoaction()
{
	return OutDoorPoint->GetComponentLocation();
}

FRotator AHDoor::GetInDoorRotatior()
{
	return InDoorPoint->GetComponentRotation();
}

FRotator AHDoor::GetOutDoorRotatior()
{
	return OutDoorPoint->GetComponentRotation();
}

int32 AHDoor::GetDoorID() const
{
	return DoorID;
}

float AHDoor::GetDoorDurability() const
{
	return Durability;
}

float AHDoor::GetDoorMaxDurability() const
{
	return MaxDurability;
}

void AHDoor::SetDoorIsBroken(bool BeBroken)
{
	IsBroken = BeBroken;
	OnDoorStateChange.Broadcast(this);
}

void AHDoor::SetDoorIsClose(bool BeClosed)
{
	IsClose = BeClosed;
	OnDoorStateChange.Broadcast(this);
}

void AHDoor::SetMatchingCode(int32 Code)
{
	MatchingCode = Code;
}

void AHDoor::SetConectedDoor(AHDoor* Door)
{
	ConnectedDoor = Door;
}

void AHDoor::SetOwnerRoom(AHRoomBase* Room)
{
	OwnerRoom = Room;
}

void AHDoor::ApplyDoorDurabilityChanged(float Delta)
{
	Durability += Delta;
	Durability = FMath::Clamp(Durability, 0, MaxDurability);
	if (Durability <= 0)
	{
		SetDoorIsBroken(true);
	}
	//门的耐久度发生了变化,通知...
	OnDoorDutabilityChange.Broadcast(this);
}

void AHDoor::ApplyDoorMaxDurabilityChanged(float Delta)
{
	MaxDurability += Delta;
	Durability = FMath::Clamp(Durability, 0, MaxDurability);
	if (Durability <= 0)
	{
		SetDoorIsBroken(true);
	}
	//门的最大耐久度发生了变化,通知...
	OnDoorDutabilityChange.Broadcast(this);
}


void AHDoor::AnimationDoor_Implementation(bool IsClosed)
{
	if (IsClosed)
	{
		UKismetSystemLibrary::PrintString(this,TEXT("假装有关门动画"), true, false, FLinearColor::White, 3.0f);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("假装有开门动画"), true, false, FLinearColor::White, 3.0f);
	}
}

//注意一定要引用基类的Beginplay，不然此Actor不具备Tick功能。还会产生一些其他问题。
void AHDoor::BeginPlay()
{
	Super::BeginPlay();

	AnimationDoor(IsClose);
}
