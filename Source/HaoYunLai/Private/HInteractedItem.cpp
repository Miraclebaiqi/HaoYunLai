// Fill out your copyright notice in the Description page of Project Settings.


#include "HInteractedItem.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"




// Sets default values
AHInteractedItem::AHInteractedItem()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetCollisionProfileName("Interacted");
	RootComponent = BoxComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(RootComponent);
	
	IsFocused = false;
	IsActive = true;
}
void AHInteractedItem::Interact_Implementation(APawn* InstigatorActor)
{
	//子类交互逻辑
}