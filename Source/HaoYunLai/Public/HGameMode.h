// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HGameMode.generated.h"

class AHGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameDataChanged,AHGameMode*,Instigator);

UCLASS()
class HAOYUNLAI_API AHGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	int32 GameRealTime;
	FTimerHandle GameTimeCount;

	UPROPERTY(EditDefaultsOnly, Category="GameParam")
	float MaintenancePowerCost;
	UPROPERTY(EditDefaultsOnly, Category="GameParam")
	float DefaultPowerCost;
	UPROPERTY(VisibleAnywhere, Category="Gameparam")
	float PowerRecover;

	float CalculatePowerChanged();
	void WriteGameRealTime();
	void MatchDoor();


public:
	AHGameMode();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GameData")
	FName RobotName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GameData")
	float Electricity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GameData")
	float MaxElectricity;

	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnGameDataChanged OnElectricityChanged;

	UFUNCTION(BlueprintCallable, Category="Timer")
	void ContinueGameRealTime();
	UFUNCTION(BlueprintCallable, Category="Timer")
	void PauseGameRealTime();

	UFUNCTION(BlueprintCallable, Category="Set")
	void ApplyElectricityChanged(float Detal);
	UFUNCTION(BlueprintCallable, Category="Set")
	void ApplyMaxElectricityChanged(float Detal);
	UFUNCTION(BlueprintCallable, Category="Set")
	void ApplyPowerRecoverChanged(float Delta);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetRobotName(FName BotName);

	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetGameRealTime() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	float GetMaintenancePowerCost() const;

	UFUNCTION(BlueprintCallable, Category="GameProcess")
	void GameOver();

	virtual void StartPlay() override;
};
