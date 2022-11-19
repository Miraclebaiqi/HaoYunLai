// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HRoomBase.generated.h"

class UCameraComponent;
class AHDoor;
class AHItemInRoom;
class AHSpreadBase;
class ACameraActor;
class USceneCaptureComponent2D;
UCLASS()
class HAOYUNLAI_API AHRoomBase : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere,Category="Component")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere,Category="Component")
	USceneCaptureComponent2D* CaptureComp2D;

	//存放房间里的所有门
	UPROPERTY(EditAnywhere,Category="Attribute")
	TArray<AHDoor*> Doors;
	//存放房间里所有可交互的物品
	UPROPERTY(EditAnywhere,Category="Attribute")
	TArray<AHItemInRoom*> Items;
	//存放房间里所有的蔓延物
	UPROPERTY(VisibleAnywhere,Category="Attribute")
	TArray<AHSpreadBase*> Spreads;

	UFUNCTION(BlueprintCallable,Category="Initialize")
	void InitializeDoors();
	UFUNCTION(BlueprintCallable,Category="Initialize")
	void InitializeItems();

	virtual void PostInitializeComponents() override;
	
public:

	AHRoomBase();
	
	UFUNCTION(BlueprintCallable,Category="Operation")
	void AddSpread(AHSpreadBase* Spread);
	UFUNCTION(BlueprintCallable,Category="Operation")
	void RemoveSpread(AHSpreadBase* Spread);
	
	UFUNCTION(BlueprintCallable,Category="Operation")
	void RoomFocusOn();
	UFUNCTION(BlueprintCallable,Category="Operation")
	void RoomOutOfFocus();


	
};
