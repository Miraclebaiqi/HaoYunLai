// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HInteractedItem.h"
#include "HTable.generated.h"

/**
 * 
 */
UCLASS()
class HAOYUNLAI_API AHTable : public AHInteractedItem
{
	GENERATED_BODY()

public:
	virtual void Interact_Implementation(APawn* InstigatorActor) override;
};
