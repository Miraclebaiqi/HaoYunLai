// Fill out your copyright notice in the Description page of Project Settings.


#include "HPlayer.h"

#include "HInteractedItem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

// Sets default values
AHPlayer::AHPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	RootComponent = CameraComp;

	ActiveCamera = this;
	RayDistance = 10000.0f;
	PS = EPlayerState::PS_Normal;
}

// 聚焦可交互物品的方法
void AHPlayer::FocusOn(AHInteractedItem* Item,float Time)
{
	if (ensure(Item))
	{
		if (!Item->IsFocused)
		{
			//如果聚焦到下一件物品则失焦当前物品
			if (FocusedItem != nullptr)
			{
				FocusOut(FocusedItem);
			}
			FocusedItem = Item;
			SwitchCurrentCamera(FocusedItem,Time);
			FocusedItem->IsFocused = true;
			FocusedItem->EnableInput(UGameplayStatics::GetPlayerController(this,0));
		}
	}
}

void AHPlayer::FocusOut(AHInteractedItem* Item)
{
	if(ensure(Item))
	{
		Item->IsFocused = false;
		Item->DisableInput(UGameplayStatics::GetPlayerController(this,0));
	}
}

//切换摄像机 多用于房间
void AHPlayer::SwitchCurrentCamera(AActor* CurrentCamera,float Time)
{
	if (ensure(CurrentCamera))
	{
		ActiveCamera = CurrentCamera;
		ActiveCurrentCamera(ActiveCamera,Time);
	}
}


//切换摄像机视角功能实现
void AHPlayer::ActiveCurrentCamera(AActor* CurrentCamera,float BlendTime)
{
	if (ensure(CurrentCamera))
	{
		APlayerController* APC = UGameplayStatics::GetPlayerController(this, 0);
		if (ensure(APC))
		{
			APC->SetViewTargetWithBlend(CurrentCamera, BlendTime);
		}
	}
}

//检测交互
void AHPlayer::PrimaryInteract()
{
	if (ensure(ActiveCamera))
	{
		FVector WorldLocation;
		FVector WorldDirection;

		if (UGameplayStatics::GetPlayerController(this, 0)->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			//设定射线的检测类型;
			FCollisionObjectQueryParams ObjectQueryParams;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);

			//设定射线形状
			FCollisionShape Shape;
			Shape.SetSphere(20.0f);
			FVector Start = WorldLocation;
			FVector End = WorldLocation + WorldDirection * RayDistance;
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
			FHitResult OutHit;
			if (GetWorld()->SweepSingleByObjectType(OutHit, Start, End, FQuat::Identity, ObjectQueryParams, Shape))
			{
				AActor* HitACtor = OutHit.GetActor();
				if (HitACtor)
				{
					//HitActor是否实现了HGameplayInterface。ps在这里检测类是否实现了接口用U开头，调用的时候用I开头
					if (HitACtor->Implements<UHGameInterface>())
					{
						IHGameInterface::Execute_Interact(HitACtor, this);
						DrawDebugSphere(GetWorld(), OutHit.Location, 5.0f, 8, FColor::Green, false, 5);
						// if (HitACtor->GetComponentByClass(UCameraComponent::StaticClass()))
						// {
						// 	FocusOn(Cast<AHInteractedItem>(HitACtor));
						// }
					}
				}
			}
		}
	}
}

void AHPlayer::SetPlayerState(EPlayerState PlayerCurrentState)
{
	PS = PlayerCurrentState;
}

// Called when the game starts or when spawned
void AHPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ClickLeft", IE_Pressed, this, &AHPlayer::ClickLeft);
	PlayerInputComponent->BindAction("ClickRight", IE_Pressed, this, &AHPlayer::ClickRight);
	
}

void AHPlayer::ClickLeft()
{
	PrimaryInteract();
}

void AHPlayer::ClickRight()
{
	if (PS == EPlayerState::PS_FocusOnTableItem)
	{
		if (ensure(Table))
		{
			FocusOn(Cast<AHInteractedItem>(Table));
			PS = EPlayerState::PS_FocusOnTable;
		}
	}
	else if (PS == EPlayerState::PS_FocusInRoom)
	{
		if (ensure(Monitor))
		{
			FocusOn(Cast<AHInteractedItem>(Monitor),0.0f);
			PS = EPlayerState::PS_FocusOnTableItem;
		}
	}
}