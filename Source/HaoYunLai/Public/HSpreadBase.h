// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HSpreadBase.generated.h"

class AHRoomBase;
UCLASS()
class HAOYUNLAI_API AHSpreadBase : public AActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	FName SpreadName;
	
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float SpreadDamageForDoor;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float SpreadDamageForRobot;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float SpreadTime;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float DamageTime;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHRoomBase* OwnerRoom;

	FTimerHandle SpreadTimerHandle;
	FTimerHandle DamageTimerHandle;

	void DestroyedSpreadSelf();
public:
	
	AHSpreadBase();

	//蔓延逻辑
	UFUNCTION(BlueprintCallable, Category="Operation")
	void SpreadLogic();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void DamageLogic();
	
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetOwnerRoom(AHRoomBase* Room);
	
	UFUNCTION(BlueprintCallable, Category="Get")
	AHRoomBase* GetOwnerRoom() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	FName GetSpreadName() const;

	virtual void BeginPlay() override;
};
