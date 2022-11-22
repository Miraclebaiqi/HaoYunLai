// Fill out your copyright notice in the Description page of Project Settings.


#include "HItemInRoom.h"

#include "HGameMode.h"
#include "HRobot.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AHItemInRoom::AHItemInRoom()
{
	InteractPoint = CreateDefaultSubobject<UCapsuleComponent>("InteractPoint");
	InteractPoint->SetCapsuleHalfHeight(88.0f);
	InteractPoint->SetCapsuleRadius(34.0f);
	InteractPoint->SetupAttachment(RootComponent);

	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComp");
	ArrowComp->SetupAttachment(InteractPoint);
}


FVector AHItemInRoom::GetInteractPointLocation()
{
	return InteractPoint->GetComponentLocation();
}
FRotator AHItemInRoom::GetInteractPointRotator()
{
	return InteractPoint->GetComponentRotation();
}

void AHItemInRoom::Interact_Implementation(APawn* InstigatorActor)
{
	if (IsActive)
	{
		AHRobot* ActorRobot = Cast<AHRobot>(UGameplayStatics::GetActorOfClass(this, AHRobot::StaticClass()));
		if (ActorRobot)
		{
			ActorRobot->MoveToTarget(this);
			UKismetSystemLibrary::PrintString(this,TEXT("机器人走到交互物前"), true, false, FLinearColor::White, 3.0f);
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("该房间物品未激活"), true, false, FLinearColor::Yellow, 10.0f);
	}
}



void AHItemInRoom::MyInteraction_Implementation(APawn* InstigatorActor)
{
	UKismetSystemLibrary::PrintString(this,TEXT("物品交互特有逻辑:(比如影响一些全局变量)"), true, false, FLinearColor::White, 3.0f);
}

void AHItemInRoom::VisualFeedback_Implementation()
{
	UKismetSystemLibrary::PrintString(this,TEXT("物品交互视觉反馈:(比如影响一些全局变量)"), true, false, FLinearColor::White, 3.0f);
}


