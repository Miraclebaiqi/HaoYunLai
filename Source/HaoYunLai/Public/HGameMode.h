// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGameMode.generated.h"

//游戏全局数据
static float Electricity;
static float MAXElectricity;

UCLASS()
class HAOYUNLAI_API AHGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:


	UFUNCTION()
	void MatchDoor();


public:
	
	UFUNCTION(BlueprintCallable,Category="Set")
	static void  ApplyElectricityChanged(float Detal);
	UFUNCTION(BlueprintCallable,Category="Set")
	static void  ApplyMaxElectricityChanged(float Detal) ;

	
	virtual void StartPlay() override;
};


