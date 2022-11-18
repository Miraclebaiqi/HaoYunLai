// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HRoomBase.generated.h"

class UCameraComponent;
class AHDoor;
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
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	TArray<AHDoor*> Doors;
	UPROPERTY(VisibleAnywhere,Category="Attribute")
	TArray<AHSpreadBase*> Spreads;

	UFUNCTION(BlueprintCallable,Category="Initialize")
	void InitializeDoor();

	virtual void PostInitializeComponents() override;
	
public:

	UFUNCTION(BlueprintCallable,Category="Get")
	ACameraActor* GetCamera();
	
	UFUNCTION(BlueprintCallable,Category="Operation")
	void AddSpread(AHSpreadBase* Spread);
	UFUNCTION(BlueprintCallable,Category="Operation")
	void RemoveSpread(AHSpreadBase* Spread);
	
	AHRoomBase();
};
