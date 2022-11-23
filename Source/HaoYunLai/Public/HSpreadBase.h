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
	float SpreadDamage;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float ActiveTimeInterval;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHRoomBase* OwnerRoom;

	
public:
	
	AHSpreadBase();

	//蔓延逻辑
	UFUNCTION(BlueprintCallable, Category="Operation")
	virtual void SpreadLogic();

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetOwnerRoom(AHRoomBase* Room);
	
	UFUNCTION(BlueprintCallable, Category="Get")
	AHRoomBase* GetOwnerRoom() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	FName GetSpreadName() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	float GetActiveTimeInterval() const;

	
};
