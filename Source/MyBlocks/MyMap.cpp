// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMap.h"
#include "MyBox.h"
#include "Components/BoxComponent.h"

// player's field size
const int32 COL = 36;  // number of blocks horizontally
const int32 ROW = 22;  // number of blocks vertically

// creating a field of the desired size
class AMyBox* Map[COL][ROW];

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

    GenerateMap();
}

// Called every frame
void AMyMap::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyMap::GenerateMap()
{
    // coordinates of the width and height of the block
    float DZ = 1.05f, DY = 1.05f;

    // we get the origin point and save it for restoration in the future
    FVector StartPointtmp = SpawnPoint->Bounds.Origin;
    // the variable by which we will calculate these blocks
    FVector StartPoint = SpawnPoint->Bounds.Origin;
    FRotator SpawnRotate = FRotator(0, 0, 0);  // setting the rotation position of the blocks

    FActorSpawnParameters SpawnParam;         // setting up an object for creating actors
    SpawnParam.Owner = this;                  // specifying who creates the object
    SpawnParam.Instigator = GetInstigator();  // who is the initiator of the block creation

    class UWorld* W = GetWorld();
    if (W)
    {
        // moving up vertically
        for (int32 yy = 0; yy < ROW; yy++)
        {
            for (int32 xx = 0; xx < COL; xx++)
            {
                // creating a block and saving it to an array
                Map[xx][yy] = GetWorld()->SpawnActor<AMyBox>(StartPoint, SpawnRotate);

                Map[xx][yy]->X = xx;         // position by X
                Map[xx][yy]->Y = yy;         // position by Y
                Map[xx][yy]->OwnMap = this;  // Map who created the block

                // calculating the new vertical coordinate
                StartPoint.Y += DY;
            }
            // returning the blocks to the initial position
            StartPoint.Y = StartPointtmp.Y;
            // setting the vertical position
            StartPoint.Z += DZ;
        }
   }
}


// a function that will get the coordinates of the block that the player clicked on
void AMyMap::SelectBlock(int32 X, int32 Y)
{
    // zeroing the block from the Map class

    Map[X][Y]->IndexCurrentMateril = 0;

 
}