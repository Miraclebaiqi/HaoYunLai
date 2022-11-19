// Fill out your copyright notice in the Description page of Project Settings.


#include "HItemInRoom.h"

#include "Kismet/KismetSystemLibrary.h"


void AHItemInRoom::Interact_Implementation(APawn* InstigatorActor)
{
	if (IsActive)
	{
		MyInteraction(InstigatorActor);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("该房间物品未激活"), true, false, FLinearColor::Yellow, 3.0f);
	}
}

void AHItemInRoom::MyInteraction_Implementation(APawn* InstigatorActor)
{
	UKismetSystemLibrary::PrintString(this,TEXT("房间内物品交互:(比如打开输入)"), true, false, FLinearColor::Blue, 3.0f);
}


