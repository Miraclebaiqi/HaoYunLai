// Fill out your copyright notice in the Description page of Project Settings.


#include "HEventManager.h"

#include "Kismet/KismetSystemLibrary.h"
// Sets default values

AHEventManager::AHEventManager()
{

}


void AHEventManager::TriggerEvent(int32 EventID)
{
	if (EventID>0)
	{
		OnEventTrigger.Broadcast(FName(FString::FromInt(EventID)));
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("事件ID为0，不触发任何事件"), true, false, FLinearColor::White, 3.0f);
	}
}

void AHEventManager::EventTriggerLogic_Implementation(FName LogicType, FName Param1 , FName Param2)
{
	UKismetSystemLibrary::PrintString(this,TEXT("需要在蓝图中重写事件触发逻辑"), true, false, FLinearColor::Yellow, 10.0f);
}


void AHEventManager::TriggerEffect_Implementation(FName EffectName)
{
	UKismetSystemLibrary::PrintString(this,TEXT("需要在蓝图中重写效果触发函数"), true, false, FLinearColor::Yellow, 10.0f);
}


