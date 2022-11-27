// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HEventManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventTrigger,FName, Instigator);

UCLASS()
class HAOYUNLAI_API AHEventManager : public AActor
{
	GENERATED_BODY()
	
public:
	AHEventManager();

	UPROPERTY(BlueprintAssignable,Category="Delegate")
	FOnEventTrigger OnEventTrigger;
	
	UFUNCTION(BlueprintCallable,Category="Event")
	void TriggerEvent(int32 EventID);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Effect")
	void TriggerEffect(FName EffectName);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Effect")
	void EventTriggerLogic(const FString& LogicName);

	

};
