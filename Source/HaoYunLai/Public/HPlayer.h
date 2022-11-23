// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HPlayer.generated.h"


class AActor;
class UCameraComponent;
class AHInteractedItem;

UENUM(BlueprintType)
enum class HEPlayerState:uint8
{
	PS_Normal,
	PS_FocusOnTable,
	PS_FocusOnTableItem,
	PS_FocusInRoom
};


UCLASS()
class HAOYUNLAI_API AHPlayer : public APawn
{
	GENERATED_BODY()

public:
	AHPlayer();

	UFUNCTION(BlueprintCallable, Category="Operation")
	void FocusOn(AHInteractedItem* Item, float Time = 2.0f);
	UFUNCTION(BlueprintCallable, Category="Operation")
	void FocusOut(AHInteractedItem* Item);
	UFUNCTION(BlueprintCallable, Category="Operation")
	void SwitchCurrentCamera(AActor* CurrentCamera, float Time = 0.0f);
	UFUNCTION(BlueprintCallable, Category="Interact")
	void PrimaryInteract();

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetPlayerState(HEPlayerState PlayerCurrentState);

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCameraComponent* CameraComp;

	//玩家当前视角使用的摄像机
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AActor* ActiveCamera;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHInteractedItem* FocusedItem;

	UPROPERTY(EditAnywhere, Category="Attribute")
	AActor* Table;
	UPROPERTY(EditAnywhere, Category="Attribute")
	AActor* Monitor;

	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	float RayDistance;

	UPROPERTY(BlueprintReadWrite, Category="Attribute")
	HEPlayerState PS;


	void ClickLeft();
	void ClickRight();
	void ActiveCurrentCamera(AActor* CurrentCamera, float BlendTime);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
