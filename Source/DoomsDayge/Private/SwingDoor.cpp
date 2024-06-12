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
	BoxComp->InitBoxExtent(FVector(85, 75, 100));
	BoxComp->SetCollisionProfileName("Trigger");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASwingDoor::OverlappedBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ASwingDoor::OverlappedEnd);
	RootComponent = BoxComp;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DOOR"));
	Door->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.Sm_Door"));

	if(DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
		Door->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		Door->SetWorldScale3D(FVector(1.f));
	}

	isClosed = true;
	Opening = false;
	Closing = false;

	// DotP = 0.f;
	MaxLocation = 0.f;
	// PosNeg = 0.f;
	// DoorCurrentLocation = FVector(0., 0., 0.);
}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(),
		BoxComp->GetScaledBoxExtent(),
		FQuat(GetActorRotation()),
		FColor::Turquoise, true,
		-1.f, 0.f, 2.f);
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Opening)
	{
		OpenDoor(DeltaTime);
	}

	if (Closing)
	{
		CloseDoor(DeltaTime);
	}
}

void ASwingDoor::OpenDoor(float dt)
{
	DoorCurrentLocation = Door->GetRelativeLocation();

	AddLocation = dt * 1.f;

	if (FMath::IsNearlyEqual(DoorCurrentLocation.Z, MaxLocation,
				.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Opening)
	{
		const FVector NewLocation = FVector(DoorCurrentLocation.X, DoorCurrentLocation.Y,
											AddLocation);
		Door->SetRelativeLocation(FVector(NewLocation) , false,
			nullptr,
			ETeleportType::None);
	}
}

void ASwingDoor::CloseDoor(float dt)
{
	DoorCurrentLocation = Door->GetRelativeLocation();

	AddLocation = -dt * 1.f;
	/*if (DoorCurrentLocation > 0.f)
	{
		AddLocation = -dt * 10.f;
	}
	else
	{
		AddLocation = dt * 10.f;
	}*/

	if (FMath::IsNearlyEqual(DoorCurrentLocation.Z, 0.f, .5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Closing)
	{
		const FVector NewLocation = FVector(0., 0.,
											AddLocation);
		Door->SetRelativeLocation(FVector(NewLocation), false,
			nullptr,
			ETeleportType::None);
	}
}

void ASwingDoor::ToggleDoor(const FVector &ForwardVector)
{
	// DotP = FVector::DotProduct(BoxComp->GetForwardVector(), ForwardVector);

	// PosNeg = FMath::Sign(DotP);

	// MaxLocation = PosNeg * 90.f;

	MaxLocation = 160.f;
	
	if (isClosed)
	{
		isClosed = false;
		Closing = false;
		Opening = true;
	}
	else
	{
		Opening = false;
		isClosed = true;
		Closing = true;
	}
}

void ASwingDoor::OverlappedBegin(UPrimitiveComponent* OverlappedComp,
	AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ASwingDoor::OverlappedEnd(UPrimitiveComponent* OverlappedComp,
	AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

