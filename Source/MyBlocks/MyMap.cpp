// Fill out your copyright notice in the Description page of Project Settings.

#include "MyMap.h"
#include "MyBox.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// player's field size
const int32 COL = 36;  // number of blocks horizontally
const int32 ROW = 22;  // number of blocks vertically

// creating a field of the desired size
class AMyBox* Map[COL][ROW];

struct MyPoint
{
    int32 XX, YY;

    MyPoint()
    {
        XX = 0;
        YY = 0;
    }

    inline bool operator==(MyPoint a) { return ((a.XX == XX) && (a.YY == YY)); }
};

TArray<MyPoint> DeletePretindent;

TArray<MyPoint> TestPointList(MyPoint coord)
{
    MyPoint T;
    TArray<MyPoint> Result;

    /*  __
    ___ __ __
    _X_ __ __
    __
        */

    //������������ ���������� ����� � �����
    T.XX = coord.XX - 1;  //��������� �
    T.YY = coord.YY;      //��������� �
    //��������� ����� ������� ���� X >=0
    if (T.XX >= 0) Result.Add(T);  //��������� ����� � ������

    /* __
    __ __ ___
    __ __ _X_
       __
    */

    //������������ ���������� ����� �����
    T.XX = coord.XX + 1;  //��������� �
    T.YY = coord.YY;      //��������� �
    //��������� ������ ������� X< ���������� ��������
    if (T.XX < COL) Result.Add(T);  //��������� ����� � ������

    /*  ___
    ___ _X_ ___
    ___ ___ ___
    ___
    */

    //������������ ���������� ����� ������
    T.XX = coord.XX;      //��������� �
    T.YY = coord.YY + 1;  //��������� �
    //��������� ������ ������� Y < ���������� �����
    if (T.YY < ROW) Result.Add(T);  //��������� ����� � ������

    /*  ___
    ___ ___ ___
    ___ ___ ___
    _X_
    */

    //������������ ���������� ����� �����
    T.XX = coord.XX;      //��������� �
    T.YY = coord.YY - 1;  //��������� �
    //��������� ����� ������� ���� Y >=0
    if (T.YY >= 0) Result.Add(T);  //��������� ����� � ������

    return Result;
};

// the function returns the index of the found element
int32 SerchPoint(MyPoint P)
{
    // sorting through all the blocks collected in the array
    for (int s = 0; s < DeletePretindent.Num(); s++)
        // if you found the same point
        if (P == DeletePretindent[s])
            // we will return the point number
            return s;
    // we will return -1 if we did not find the point
    return -1;
}

// block verification function
void TestBlok(int32 _X, int32 _Y, int32 IndexColor)
{
    MyPoint coord;  // collecting a point
    coord.XX = _X;  // setting the X coordinate
    coord.YY = _Y;  // setting the Y coordinate
    // check if there is such a point in the list
    int32 Find = SerchPoint(coord);
    // if you have found it, then there is a reason to check the point
    if (Find == -1)
    {
        // get the color of the point
        int32 ColorIndex = Map[_X][_Y]->IndexCurrentMateril;
        // If the color fits then we will do something
        if (IndexColor == ColorIndex)
        {
            // adding the applicant to the list
            DeletePretindent.Add(coord);
            // calculating neighboring points
            TArray<MyPoint> test = TestPointList(coord);
            // we get the number of points found
            for (int TestPoint = 0; TestPoint < test.Num(); TestPoint++)
            {
                // iterating through the list of points with a check of points
                TestBlok(test[TestPoint].XX, test[TestPoint].YY, IndexColor);
            }
        }
    }
}

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
 
//������� ������� ����� �������� ���������� ����� �� ������� ����� �����
void AMyMap::SelectBlock(int32 X, int32 Y)
{
    //�������� ���� �� ������ Map
    // Map[X][Y]->IndexCurrentMateril = 0;

    //�������� ������ ������������
    DeletePretindent.Empty();

    //������� ���� �����
    int32 ColorIndex = Map[X][Y]->IndexCurrentMateril;

    //��������� ����� ������
    TestBlok(X, Y, ColorIndex);

    //���� ������ ������� ������ 2 ������ ������� ��
    if (DeletePretindent.Num() > 2)
    {
        //������� �����
        for (int b = 0; b < DeletePretindent.Num(); b++)
        {
            //�������� ���� �� ������ Map
            Map[DeletePretindent[b].XX][DeletePretindent[b].YY]->IndexCurrentMateril = 0;
        }
        ScorePlayer += DeletePretindent.Num();

        //��������� ��������� ����
        MyScoreText->SetText(FText::AsNumber(ScorePlayer));
    }

    while (SerchZeroBloks())
    {
        MoveBlockDown();
    }
}

/** ������� �������� ������ ���� */
void AMyMap::MoveBlockDown()
{
    //���������� ��� ����� ����
    for (int32 yy = 0; yy < ROW; yy++)
    {
        for (int32 xx = 0; xx < COL; xx++)
        {
            //���� ���� ������ ����
            if (Map[xx][yy]->IndexCurrentMateril == 0)
            {
                //����������� ����� �����
                int32 DY = yy + 1;
                //��������� ��� ��� ���� ����������
                if (DY < ROW)
                {
                    //�������� ���� � �������� �����
                    Map[xx][yy]->IndexCurrentMateril = Map[xx][DY]->IndexCurrentMateril;
                    //�������� ���� �������� �����
                    Map[xx][DY]->IndexCurrentMateril = 0;
                }
                else
                {
                    //������ ����� ��������� ����
                    Map[xx][yy]->RandomColor();
                }
            }
        }
    }
}

/** ������� �������� ������ ������ */
bool AMyMap::SerchZeroBloks()
{
    //���������� ��� ����� ����
    for (int32 yy = 0; yy < ROW; yy++)
    {
        for (int32 xx = 0; xx < COL; xx++)
        {
            //���� ���� ������ ���� �� ���������� true
            if (Map[xx][yy]->IndexCurrentMateril == 0) return true;
        }
    }
    //���� ��� ������ ������ ������ ����
    return false;
}

void AMyMap::GreateMyScoreText()
{
    //������� ������ ������ �����
    MyScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));

    //�������� ��������� ���������� �����
    FVector StartPointtmp = SpawnPoint->Bounds.Origin;

    StartPointtmp.Z -= 2.f;   //�������� ���������� �� Z ���� �� 1 ���������
    StartPointtmp.Y += 15.f;  //��������� �� ������ �����

    //������������� ����� �� 180 ��������
    FRotator SpawnRotate = FRotator(0, 180, 0);

    //������ ���� �������� ������  ������������ ������
    MyScoreText->SetRelativeRotation(SpawnRotate);

    //������ ���������� ��� ������
    MyScoreText->SetRelativeLocation(StartPointtmp);

    MyScoreText->SetXScale(0.05f);
    MyScoreText->SetYScale(0.05f);

    //����������� ����� � �������� ����� ����� �����
    MyScoreText->AttachTo(SpawnPoint);

    //��������� ����� �������� 0
    MyScoreText->SetText("123456789");
}