// Fill out your copyright notice in the Description page of Project Settings.


#include "HUserWidget.h"

#include "Kismet/KismetSystemLibrary.h"


void UHUserWidget::FindConnectedObject_Implementation()
{
	UKismetSystemLibrary::PrintString(this,TEXT("蓝图中实现自身功能，寻找对应的操作物体，并设定"), true, false, FLinearColor::White, 3.0f);
}
