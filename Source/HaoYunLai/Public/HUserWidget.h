// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUserWidget.generated.h"

class AHEventManager;

UCLASS()
class HAOYUNLAI_API UHUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Manager")
	AHEventManager* EventManager;
	
	UFUNCTION(BlueprintCallable,Category="Operation")
	void FindEventManager();
};
