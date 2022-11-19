// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HGameInterface.h"
#include "GameFramework/Actor.h"
#include "HInteractedItem.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class AActor;
class UBoxComponent;

UCLASS()
class HAOYUNLAI_API AHInteractedItem : public AActor, public IHGameInterface
{
	GENERATED_BODY()

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere, Category="Component")
	UCameraComponent* CameraComp;


public:
	// Sets default values for this actor's properties
	AHInteractedItem();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute")
	bool IsFocused;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Attribute")
	bool IsActive;
	
};
