// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingDoor.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASwingDoor::ASwingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX COMP"));
	BoxComp->InitBoxExtent(FVector(150, 100, 100));
	BoxComp->SetCollisionProfileName("Trigger");
	RootComponent = BoxComp;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR"));
	Door->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.Sm_Door"));

	if(DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
		Door->SetRelativeLocation(FVector(0.f, 50.f, -100.f));
		Door->SetWorldScale3D(FVector(1.f));
	}

	isClosed = true;
	Opening = false;
	Closing = false;

	DotP = 0.f;
	MaxDegree = 0.f;
	PosNeg = 0.f;
	DoorCurrentRotation = 0.f;
}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwingDoor::OpenDoor(float dt)
{
	
}

void ASwingDoor::CloseDoor(float dt)
{
	
}

void ASwingDoor::ToggleDoor(FVector ForwardVector)
{
	
}

