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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoomStateChanged);

UCLASS()
class HAOYUNLAI_API AHRoomBase : public AActor
{
	GENERATED_BODY()


	
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, Category="Component")
	USceneCaptureComponent2D* CaptureComp2D;

	//房间编号
	UPROPERTY(EditAnywhere, Category="Attribute")
	int32 RoomID;
	//存放房间里面的光照信息
	UPROPERTY(EditAnywhere, Category="Attribute")
	TArray<AActor*> Lights;
	//存放房间里的所有门
	UPROPERTY(EditAnywhere, Category="Attribute")
	TArray<AHDoor*> Doors;
	//存放房间里所有可交互的物品
	UPROPERTY(EditAnywhere, Category="Attribute")
	TArray<AHItemInRoom*> Items;
	//存放房间里所有的蔓延物
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	TArray<AHSpreadBase*> Spreads;

	UFUNCTION(BlueprintCallable, Category="Initialize")
	void InitializeDoors();
	UFUNCTION(BlueprintCallable, Category="Initialize")
	void InitializeItems();

	virtual void PostInitializeComponents() override;

public:
	AHRoomBase();

	UPROPERTY(BlueprintAssignable)
	FOnRoomStateChanged OnroomStateChanged;
	
	UFUNCTION(BlueprintCallable, Category="Operation")
	void AddSpread(AHSpreadBase* Spread);
	UFUNCTION(BlueprintCallable, Category="Operation")
	void RemoveSpread(AHSpreadBase* Spread);

	UFUNCTION(BlueprintCallable, Category="Operation")
	void RoomFocusOn();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void RoomOutOfFocus();

	UFUNCTION(BlueprintCallable, Category="Operation")
	void ApplyRoomLight(bool IsHidden);

	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetRoomID()	const;
};
