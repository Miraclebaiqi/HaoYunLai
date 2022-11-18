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

public:
	// Sets default values for this actor's properties
	AHSpreadBase();


	UFUNCTION(BlueprintCallable, Category="Operation")
	void SpreadLogic();

	UFUNCTION(BlueprintCallable, Category="Set")
	void SetOwnerRoom(AHRoomBase* Room);
	UFUNCTION(BlueprintCallable, Category="Get")
	AHRoomBase* GetOwnerRoom();
	UFUNCTION(BlueprintCallable, Category="Get")
	FName GetSpreadName();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Attribute")
	FName SpreadName;
	UPROPERTY(VisibleAnywhere, Category="Attribute")
	AHRoomBase* OwnerRoom;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
