// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractedItem.h"
#include "HDoor.generated.h"

class AHRoomBase;
class USphereComponent;
class UCapsuleComponent;
class UArrowComponent;
class AHDoor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorStateChange, AHDoor*, InstigatorDoor);

UCLASS()
class HAOYUNLAI_API AHDoor : public AHInteractedItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCapsuleComponent* InDoorPoint;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCapsuleComponent* OutDoorPoint;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UArrowComponent* ArrowCompIn;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UArrowComponent* ArrowCompOut;

	UPROPERTY(EditAnywhere, Category="Attribute")
	int32 DoorID;
	//匹配编码(编码为正整数)，拥有相同匹配码的两个门会互相连接；如果有两个以上的门拥有相同的匹配码，会随机弃用其他门。
	UPROPERTY(EditAnywhere, Category="Attribute")
	int32 MatchingCode;
	UPROPERTY(EditAnywhere, Category="Attribute")
	bool IsClose;
	UPROPERTY(EditAnywhere, Category="Attribute")
	bool IsBroken;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float Durability;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float MaxDurability;
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float OperatePowerCost;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHDoor* ConnectedDoor;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHRoomBase* OwnerRoom;

	UFUNCTION(BlueprintCallable, Category="Operation")
	void ActiveNextRoom();
	//开关门动画(在蓝图中实现)
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Animation")
	void AnimationDoor(bool IsClosed);

public:

	UFUNCTION(BlueprintCallable,Category="Initialized")
	void DoorInitialized();
	
	UFUNCTION(BlueprintCallable, Category="Operation")
	bool SwitchDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void BrokeDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	void FixDoor();
	UFUNCTION(BlueprintCallable, Category="Operation")
	bool AssimilateConnectedDoor();

	//门的状态发生变化时的委托事件
	UPROPERTY(BlueprintAssignable)
	FOnDoorStateChange OnDoorStateChange;
	UPROPERTY(BlueprintAssignable)
	FOnDoorStateChange OnDoorDutabilityChange;

	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetDoorIsBroken() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetDoorIsClosed() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	float GetPowerCost() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetMatchingCode();
	UFUNCTION(BlueprintCallable, Category="Get")
	AHDoor* GetConectedDoor();
	UFUNCTION(BlueprintCallable, Category="Get")
	AHRoomBase* GetOwnerRoom();
	UFUNCTION(BlueprintCallable, Category="Get")
	FVector GetInDoorLoaction();
	UFUNCTION(BlueprintCallable, Category="Get")
	FVector GetOutDoorLoaction();
	UFUNCTION(BlueprintCallable, Category="Get")
	FRotator GetInDoorRotatior();
	UFUNCTION(BlueprintCallable, Category="Get")
	FRotator GetOutDoorRotatior();
	UFUNCTION(BlueprintCallable, Category="Get")
	int32 GetDoorID() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	float GetDoorDurability() const;
	UFUNCTION(BlueprintCallable, Category="Get")
	float GetDoorMaxDurability() const;

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
	UFUNCTION(BlueprintCallable, Category="Set")
	void ApplyDoorDurabilityChanged(float Delta);
	UFUNCTION(BlueprintCallable, Category="Set")
	void ApplyDoorMaxDurabilityChanged(float Delta);

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	AHDoor();
};
