// Fill out your copyright notice in the Description page of Project Settings.


#include "HUserWidget.h"

#include "HEventManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UHUserWidget::FindEventManager()
{
	EventManager = Cast<AHEventManager>(UGameplayStatics::GetActorOfClass(this, AHEventManager::StaticClass()));
	if (EventManager)
	{
		UKismetSystemLibrary::PrintString(this,TEXT("成功设定EventManager"), true, false, FLinearColor::White, 3.0f);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,TEXT("未找到EventManager，请确认场景中物体"), true, false, FLinearColor::Red, 30.0f);
	}
}
