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

    //рассчитываем координаты точки с права
    T.XX = coord.XX - 1;  //заполняем Х
    T.YY = coord.YY;      //заполняем У
    //проверяем левую сторону поля X >=0
    if (T.XX >= 0) Result.Add(T);  //добавляем точку в список

    /* __
    __ __ ___
    __ __ _X_
       __
    */

    //рассчитываем координаты точки слева
    T.XX = coord.XX + 1;  //заполняем Х
    T.YY = coord.YY;      //заполняем У
    //проверяем правую сторону X< количество столбцов
    if (T.XX < COL) Result.Add(T);  //добавляем точку в список

    /*  ___
    ___ _X_ ___
    ___ ___ ___
    ___
    */

    //рассчитываем координаты точки сверху
    T.XX = coord.XX;      //заполняем Х
    T.YY = coord.YY + 1;  //заполняем У
    //проверяем правую сторону Y < количества строк
    if (T.YY < ROW) Result.Add(T);  //добавляем точку в список

    /*  ___
    ___ ___ ___
    ___ ___ ___
    _X_
    */

    //рассчитываем координаты точки снизу
    T.XX = coord.XX;      //заполняем Х
    T.YY = coord.YY - 1;  //заполняем У
    //проверяем левую сторону поля Y >=0
    if (T.YY >= 0) Result.Add(T);  //добавляем точку в список

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
 
//функция которая будет получать координаты блока на который нажал игрок
void AMyMap::SelectBlock(int32 X, int32 Y)
{
    //обнуляем блок из класса Map
    // Map[X][Y]->IndexCurrentMateril = 0;

    //обнуляем список претиндентов
    DeletePretindent.Empty();

    //получим цвет точки
    int32 ColorIndex = Map[X][Y]->IndexCurrentMateril;

    //запускаем поиск блоков
    TestBlok(X, Y, ColorIndex);

    //если блоков найдено больше 2 значит удаляем их
    if (DeletePretindent.Num() > 2)
    {
        //обнулим блоки
        for (int b = 0; b < DeletePretindent.Num(); b++)
        {
            //обнуляем блок из класса Map
            Map[DeletePretindent[b].XX][DeletePretindent[b].YY]->IndexCurrentMateril = 0;
        }
        ScorePlayer += DeletePretindent.Num();

        //обновляем текстовые поля
        MyScoreText->SetText(FText::AsNumber(ScorePlayer));
    }

    while (SerchZeroBloks())
    {
        MoveBlockDown();
    }
}

/** функция движения блоков вниз */
void AMyMap::MoveBlockDown()
{
    //перебираем все блоки поля
    for (int32 yy = 0; yy < ROW; yy++)
    {
        for (int32 xx = 0; xx < COL; xx++)
        {
            //если есть пустой блок
            if (Map[xx][yy]->IndexCurrentMateril == 0)
            {
                //расчитываем новую точку
                int32 DY = yy + 1;
                //проверяем что над нами находиться
                if (DY < ROW)
                {
                    //забираем цвет у верхнего блока
                    Map[xx][yy]->IndexCurrentMateril = Map[xx][DY]->IndexCurrentMateril;
                    //Затираем цвет верхнего блока
                    Map[xx][DY]->IndexCurrentMateril = 0;
                }
                else
                {
                    //задаем блоку случайный цвет
                    Map[xx][yy]->RandomColor();
                }
            }
        }
    }
}

/** функция проверки пустых блоков */
bool AMyMap::SerchZeroBloks()
{
    //перебираем все блоки поля
    for (int32 yy = 0; yy < ROW; yy++)
    {
        for (int32 xx = 0; xx < COL; xx++)
        {
            //если есть пустой блок то возвращаем true
            if (Map[xx][yy]->IndexCurrentMateril == 0) return true;
        }
    }
    //если нет пустых блоков значит льжь
    return false;
}

void AMyMap::GreateMyScoreText()
{
    //создаем обьект текста текст
    MyScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));

    //получаем начальные координаты карты
    FVector StartPointtmp = SpawnPoint->Bounds.Origin;

    StartPointtmp.Z -= 2.f;   //опускаем координату по Z вниз на 1 сантиметр
    StartPointtmp.Y += 15.f;  //разместим по центру блока

    //разворачиваем текст на 180 градусов
    FRotator SpawnRotate = FRotator(0, 180, 0);

    //задаем угол поворота текста  относительно камеры
    MyScoreText->SetRelativeRotation(SpawnRotate);

    //задаем координаты для текста
    MyScoreText->SetRelativeLocation(StartPointtmp);

    MyScoreText->SetXScale(0.05f);
    MyScoreText->SetYScale(0.05f);

    //привязываем текст к корневой точке нашей карты
    MyScoreText->AttachTo(SpawnPoint);

    //заполняем текст символом 0
    MyScoreText->SetText("123456789");
}