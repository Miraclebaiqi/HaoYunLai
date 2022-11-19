// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HGameInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHGameInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HAOYUNLAI_API IHGameInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(APawn* InstigatorActor);
};