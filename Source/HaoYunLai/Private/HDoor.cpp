// Fill out your copyright notice in the Description page of Project Settings.


#include "HDoor.h"

#include "HPlayer.h"
#include "HRoomBase.h"


AHDoor::AHDoor()
{
	IsClose = false;
	IsBroken = false;
	MatchingCode = -1;
}

bool AHDoor::SwitchDoor()
{
	//如果门没坏，则切换门的开关状态
	if (!IsBroken)
	{
		IsClose = !IsClose;
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
		IsClose = false;
		AnimationDoor(false);
	}
	IsBroken = true;
}

void AHDoor::FixDoor()
{
	IsBroken = false;
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
	if(IsActive)
	{
		if (IsClose)
		{
			UE_LOG(LogTemp, Log, TEXT("门是关闭状态的，无法通过"));
		}
		else
		{
			if (ensure(ConnectedDoor))
			{
				AHRoomBase* NextRoom = ConnectedDoor->GetOwnerRoom();
				if (ensure(NextRoom))
				{
					AHPlayer* PlayerPawn = Cast<AHPlayer>(InstigatorActor);
					if (PlayerPawn)
					{
						PlayerPawn->SwitchCurrentCamera(Cast<AActor>(NextRoom));
						OwnerRoom->RoomOutOfFocus();
						NextRoom->RoomFocusOn();
						UE_LOG(LogTemp, Log, TEXT("门是打开状态的，进入下一个房间"));
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("你的门没有连接任何房间"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("你的门并没有设置连接门"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("你的门并没有激活"));
	}
}

bool AHDoor::GetDoorIsClose()
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

void AHDoor::SetDoorIsBroken(bool BeBroken)
{
	IsBroken = BeBroken;
}

void AHDoor::SetDoorIsClose(bool BeClosed)
{
	IsClose = BeClosed;
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


void AHDoor::BeginPlay()
{
	AnimationDoor(IsClose);
}
