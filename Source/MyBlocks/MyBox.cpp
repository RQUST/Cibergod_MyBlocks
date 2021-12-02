// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBox.h"

// Sets default values
AMyBox::AMyBox()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CreateBlock();
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyBox::CreateBlock()
{
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));

    RootComponent = DummyRoot;

    class UStaticMesh* BlocStatickMesh;

    BlocStatickMesh =
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("StaticMesh'/Game/Shape_Cube.Shape_Cube'")).Get();

    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));  
    BlockMesh->SetStaticMesh(BlocStatickMesh);
      
    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/RedMaterial.RedMaterial'")).Get();

    BlockMesh->SetMaterial(0, tempMaterial);  
    BlockMesh->AttachTo(DummyRoot);  
}