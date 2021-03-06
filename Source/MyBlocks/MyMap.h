// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMap.generated.h"

UCLASS()
class MYBLOCKS_API AMyMap : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyMap();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySpawnPoint", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* SpawnPoint;

    void GenerateMap();

    // a function that will get the coordinates of the block that the player clicked on
    UFUNCTION()
    void SelectBlock(int32 X, int32 Y);

    //?? ????? ?????????? ?????? ???????? ????? ???? ???? ??? ????
    void MoveBlockDown();

    //??????? ???? ?? ?????? ?????
    bool SerchZeroBloks();

    //????? ? ??????????? ????? ?????
    class UTextRenderComponent* MyScoreText;

    //??????? ???????? ??????
    void GreateMyScoreText();

    //?????????? ?????? ????????
    int32 ScorePlayer = 0;
};
