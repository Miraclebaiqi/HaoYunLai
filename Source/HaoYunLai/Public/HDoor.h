// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractedItem.h"
#include "HDoor.generated.h"

class AHRoomBase;
UCLASS()
class HAOYUNLAI_API AHDoor : public AHInteractedItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Attribute")
	bool IsClose;
	UPROPERTY(EditAnywhere, Category="Attribute")
	bool IsBroken;
	//匹配编码(编码为正整数)，拥有相同匹配码的两个门会互相连接；如果有两个以上的门拥有相同的匹配码，会随机弃用其他门。
	UPROPERTY(EditAnywhere, Category="Attribute")
	int32 MatchingCode;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHDoor* ConnectedDoor;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHRoomBase* OwnerRoom;

	//开关门动画(在蓝图中实现)
	UFUNCTION(BlueprintImplementableEvent, Category="Animation")
	void AnimationDoor(bool IsClosed);

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category="Operation")
	bool SwitchDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void BrokeDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void FixDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	bool AssimilateConnectedDoor();

	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetDoorIsClose();
	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetMatchingCode();
	UFUNCTION(BlueprintCallable, Category="Get")
	AHDoor* GetConectedDoor();
	UFUNCTION(BlueprintCallable, Category="Get")
	AHRoomBase* GetOwnerRoom();

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetDoorIsBroken(bool BeBroken);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetDoorIsClose(bool BeClosed);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetMatchingCode(int32 Code);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetConectedDoor(AHDoor* Door);
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetOwnerRoom(AHRoomBase* Room);

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	AHDoor();
};
