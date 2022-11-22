// Fill out your copyright notice in the Description page of Project Settings.


#include "HItemOnTable.h"

#include "HPlayer.h"
#include "Kismet/KismetSystemLibrary.h"


void AHItemOnTable::Interact_Implementation(APawn* InstigatorActor)
{
	if (IsActive)
	{
		if (InstigatorActor)
		{
			if (!IsFocused)
			{
				AHPlayer* MyPlayer = Cast<AHPlayer>(InstigatorActor);
				if (MyPlayer)
				{
					MyPlayer->FocusOn(this);
					MyPlayer->SetPlayerState(HEPlayerState::PS_FocusOnTableItem);
				}
			}
			else
			{
				//在这里要调用函数本身才能被蓝图覆盖。Ps 不能调用FurtherInteraction_Implementation;
				FurtherInteraction(InstigatorActor);
			}
		}
	}
}

void AHItemOnTable::FurtherInteraction_Implementation(APawn* InstigatorActor)
{
	UKismetSystemLibrary::PrintString(this,TEXT("桌上物品的进一步交互"),true,false,FLinearColor::Yellow,3.0f);
}
