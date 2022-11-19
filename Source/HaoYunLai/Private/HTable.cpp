// Fill out your copyright notice in the Description page of Project Settings.


#include "HTable.h"

#include "HPlayer.h"

void AHTable::Interact_Implementation(APawn* InstigatorActor)
{
	if(IsActive)
	{
		if (InstigatorActor)
		{
			AHPlayer* MyPlayer = Cast<AHPlayer>(InstigatorActor);
			if (MyPlayer)
			{
				MyPlayer->FocusOn(this);
				MyPlayer->SetPlayerState(EPlayerState::PS_FocusOnTable);
			}
		}
	}
}
