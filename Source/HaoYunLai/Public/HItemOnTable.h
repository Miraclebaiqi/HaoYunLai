// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractedItem.h"
#include "HItemOnTable.generated.h"

/**
 * 
 */
UCLASS()
class HAOYUNLAI_API AHItemOnTable : public AHInteractedItem
{
	GENERATED_BODY()

public:

	//BlueprintNativeEvent 如果蓝图覆盖则执行蓝图函数，若没有蓝图覆盖则执行XXXXX_Implementation函数
	UFUNCTION(BlueprintNativeEvent,Category="Function")
	void FurtherInteraction(APawn* InstigatorActor);
	
	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	
};
