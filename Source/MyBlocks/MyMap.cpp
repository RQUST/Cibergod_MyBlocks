// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMap.h"
#include "MyBox.h"
#include "Components/BoxComponent.h"

//размер поля игрока
const int32 COL = 36;  //количество блоков по горизонтали
const int32 ROW = 22;  //количество блоков по вертикали

//создание поля нужного размера
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
    //координаты ширины и высоты блока
    float DZ = 1.05f, DY = 1.05f;

    //получаем точку начала координат сохраняем для востановления в будущем
    FVector StartPointtmp = SpawnPoint->Bounds.Origin;
    //переменная по которой будем расчитывать данные блоки
    FVector StartPoint = SpawnPoint->Bounds.Origin;
    FRotator SpawnRotate = FRotator(0, 0, 0);  //задаем позицию вращения блоков

    FActorSpawnParameters SpawnParam;    //настраиваем обьект создания актеров
    SpawnParam.Owner = this;             //указываем кто создает обьект
    SpawnParam.Instigator = GetInstigator();  //кто являеться инициатором создания блока

    class UWorld* W = GetWorld();
    if (W)
    {
        //двигаемся вверх по вертикали
        for (int32 yy = 0; yy < ROW; yy++)
        {
            for (int32 xx = 0; xx < COL; xx++)
            {
                //создаем блок и сохраняем его в масив
                Map[xx][yy] = GetWorld()->SpawnActor<AMyBox>(StartPoint, SpawnRotate);
 
                //расчитываем нокую координату по вертикали
                StartPoint.Y += DY;
            }
            //возвращаем блоки на начальную позицию
            StartPoint.Y = StartPointtmp.Y;
            //задаем позицию по вертикали
            StartPoint.Z += DZ;
        }
    }
}
