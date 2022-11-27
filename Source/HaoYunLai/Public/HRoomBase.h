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
class AHRoomBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoomStateChanged, AHRoomBase*, InstigatorRoom);

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
	//当前房间是否处于激活状态(机器人是否在当前房间)
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	bool IsFocused;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	bool IsBroken;
	//当前房间的摄像机是否是玩家使用的摄像机
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	bool IsView;
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
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	bool IsInfected;

	UFUNCTION(BlueprintCallable, Category="Initialize")
	void InitializeDoors();
	UFUNCTION(BlueprintCallable, Category="Initialize")
	void InitializeItems();

	virtual void PostInitializeComponents() override;

public:
	AHRoomBase();

	//房间状态发生变化时的委托事件
	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnRoomStateChanged OnRoomSpreadChanged;
	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnRoomStateChanged OnRoomFocusChanged;
	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnRoomStateChanged OnRoomViewChanged;
	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnRoomStateChanged OnRoomBrokenChanged;
	UPROPERTY(BlueprintAssignable, Category="Delegate")
	FOnRoomStateChanged OnRoomInfectedChanged;

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

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetIsView(bool IsViewCamera);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetIsBroken(bool IsCameraBroken);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetRoomIsInfected(bool IsRoomInfected);

	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetRoomID() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetIsFocused() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetIsView() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetIsBroken() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetIsInfected() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	TArray<AHDoor*> GetDoors();
	UFUNCTION(BlueprintCallable, Category="Get")
	TArray<AHSpreadBase*> GetSpreads();
};
