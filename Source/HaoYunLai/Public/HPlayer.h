// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HPlayer.generated.h"


class AActor;
class UCameraComponent;
class AHInteractedItem;

UENUM(BlueprintType)
enum  EPlayerState
{
	PS_Normal,
	PS_FocusOnTable,
	PS_FocusOnTableItem
};

UCLASS()
class HAOYUNLAI_API AHPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHPlayer();

	UFUNCTION(BlueprintCallable, Category="Operation")
	void FocusOn(AHInteractedItem* Item);
	UFUNCTION(BlueprintCallable, Category="Operation")
	void SwitchCurrentCamera(AActor* CurrentCamera);
	UFUNCTION(BlueprintCallable, Category="Interact")
	void PrimaryInteract();

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetPlayerState(EPlayerState PlayerCurrentState);
	
protected:

	UPROPERTY(VisibleAnywhere,Category="Component")
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AActor* ActiveCamera;
	UPROPERTY(EditAnywhere, Category="Attribute")
	AActor* Table;
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	float RayDistance;
	

	EPlayerState PS;
	
	AHInteractedItem* FocusedItem;
	
	void ClickLeft();
	void ClickRight();
	void ActiveCurrentCamera(AActor* CurrentCamera);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
