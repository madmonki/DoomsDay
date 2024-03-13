// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwingDoor.generated.h"

UCLASS()
class DOOMSDAYGE_API ASwingDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwingDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CloseDoor(float dt);
	UFUNCTION()
	void OpenDoor(float dt);
	UFUNCTION()
	void ToggleDoor(FVector ForwardVector);
	
	UPROPERTY(VisibleAnywhere, Category="Box Comps")
	class UBoxComponent* BoxComp;
	class UStaticMeshComponent* Door;

	bool Opening, Closing, isClosed;
	float DotP, MaxDegree, AddRotation, PosNeg, DoorCurrentRotation;

};
