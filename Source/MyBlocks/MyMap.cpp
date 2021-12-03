// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMap.h"
#include "MyBox.h"
#include "Components/BoxComponent.h"

//������ ���� ������
const int32 COL = 36;  //���������� ������ �� �����������
const int32 ROW = 22;  //���������� ������ �� ���������

//�������� ���� ������� �������
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
    //���������� ������ � ������ �����
    float DZ = 1.05f, DY = 1.05f;

    //�������� ����� ������ ��������� ��������� ��� ������������� � �������
    FVector StartPointtmp = SpawnPoint->Bounds.Origin;
    //���������� �� ������� ����� ����������� ������ �����
    FVector StartPoint = SpawnPoint->Bounds.Origin;
    FRotator SpawnRotate = FRotator(0, 0, 0);  //������ ������� �������� ������

    FActorSpawnParameters SpawnParam;    //����������� ������ �������� �������
    SpawnParam.Owner = this;             //��������� ��� ������� ������
    SpawnParam.Instigator = GetInstigator();  //��� ��������� ����������� �������� �����

    class UWorld* W = GetWorld();
    if (W)
    {
        //��������� ����� �� ���������
        for (int32 yy = 0; yy < ROW; yy++)
        {
            for (int32 xx = 0; xx < COL; xx++)
            {
                //������� ���� � ��������� ��� � �����
                Map[xx][yy] = GetWorld()->SpawnActor<AMyBox>(StartPoint, SpawnRotate);
 
                //����������� ����� ���������� �� ���������
                StartPoint.Y += DY;
            }
            //���������� ����� �� ��������� �������
            StartPoint.Y = StartPointtmp.Y;
            //������ ������� �� ���������
            StartPoint.Z += DZ;
        }
    }
}
