// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HRobot.generated.h"

class UCameraComponent;
class AHInteractedItem;
class AHRoomBase;
UCLASS()
class HAOYUNLAI_API AHRobot : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float Durability;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float MaxDurability;
	UPROPERTY(EditAnywhere,Category="Attribute")
	int32 BeginRoomID;

	virtual void BeginPlay() override;
public:
	AHRobot();

	//机器人向着目标移动
	UFUNCTION(BlueprintImplementableEvent, Category="Animation")
	void MoveToTarget(AHInteractedItem* InteractedItem_Instigator);
};
