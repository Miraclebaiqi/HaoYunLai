// Fill out your copyright notice in the Description page of Project Settings.


#include "HSpreadBase.h"

#include "HRoomBase.h"

// Sets default values
AHSpreadBase::AHSpreadBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpreadName = "Spread";
}


//蔓延逻辑
void AHSpreadBase::SpreadLogic()
{
}


void AHSpreadBase::SetOwnerRoom(AHRoomBase* Room)
{
	OwnerRoom = Room;
}

AHRoomBase* AHSpreadBase::GetOwnerRoom()
{
	return OwnerRoom;
}

FName AHSpreadBase::GetSpreadName()
{
	return SpreadName;
}


// Called when the game starts or when spawned
void AHSpreadBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHSpreadBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
