// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMap.h"
#include "MyBox.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyMap::AMyMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("PointSpawnMyMap"));

	RootComponent = SpawnPoint;

}

// Called when the game starts or when spawned
void AMyMap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

