// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBox.h"
#include "MyMap.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyBox::AMyBox()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CreateBlock();
    LoadListMaterial();
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
    Super::BeginPlay();

    RandomColor();
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    BlockMesh->SetMaterial(0, MyListMaterial[IndexCurrentMateril]);
}

void AMyBox::CreateBlock()
{
    DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));

    RootComponent = DummyRoot;

    class UStaticMesh* BlocStatickMesh;

    BlocStatickMesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("StaticMesh'/Game/Shape_Cube.Shape_Cube'")).Get();

    BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
    BlockMesh->SetStaticMesh(BlocStatickMesh);

    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/RedMaterial.RedMaterial'")).Get();

    BlockMesh->SetMaterial(0, tempMaterial);
    BlockMesh->AttachTo(DummyRoot);

    BlockMesh->OnClicked.AddDynamic(this, &AMyBox::BlockClicked);
}

/// function for loading a list of materials
void AMyBox::LoadListMaterial()

{
    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/0.0'")).Get();
    MyListMaterial.Add(tempMaterial);

    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/BlueMaterial.BlueMaterial'")).Get();
    MyListMaterial.Add(tempMaterial);

    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/RedMaterial.RedMaterial'")).Get();
    MyListMaterial.Add(tempMaterial);

    tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/WhiteMaterial.WhiteMaterial'")).Get();
    MyListMaterial.Add(tempMaterial);

    tempMaterial =
        ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/Material/YellowMaterial.YellowMaterial'")).Get();
    MyListMaterial.Add(tempMaterial);
}

void AMyBox::RandomColor()
{
    int32 ListMaterialLengh = MyListMaterial.Num() - 1;
    IndexCurrentMateril = FMath::RandRange(1, ListMaterialLengh);
}

void AMyBox::BlockClicked(UPrimitiveComponent* ClickedComp, FKey inKey)
{
    OwnMap->SelectBlock(X, Y);
}