// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractedItem.h"
#include "HItemInRoom.generated.h"

class UCapsuleComponent;
class UArrowComponent;

UCLASS()
class HAOYUNLAI_API AHItemInRoom : public AHInteractedItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCapsuleComponent* InteractPoint;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UArrowComponent* ArrowComp;

public:
	UFUNCTION(BlueprintCallable, Category="Get")
	FVector GetInteractPointLocation();
	UFUNCTION(BlueprintCallable, Category="Get")
	FRotator GetInteractPointRotator();

	//BlueprintNativeEvent 如果蓝图覆盖则执行蓝图函数，若没有蓝图覆盖则执行XXXXX_Implementation函数

	//每个物品自己特殊的交互逻辑，比如影响一些全局变量
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Function")
	void MyInteraction(APawn* InstigatorActor = nullptr);

	//在物品被交互之后产生的某些视觉效果的变化
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Function")
	void VisualFeedback();

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	AHItemInRoom();
};
