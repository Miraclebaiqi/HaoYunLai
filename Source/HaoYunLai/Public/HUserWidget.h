// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HAOYUNLAI_API UHUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Operation")
	void FindConnectedObject();
};
