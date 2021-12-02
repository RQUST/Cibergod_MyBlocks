// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
    //отображаем курсор или прячем курсор
    ShowMouseCursor = true;
}

void AMyPlayerController::ShowHideCursor()
{
    //если стоит галка то курсор отображаеться
    if (ShowMouseCursor)
    {
        bShowMouseCursor = true;                  //включаем показ курсора
        bEnableClickEvents = true;                //разрешаем событие щелчек мышкой по объектам
        DefaultMouseCursor = EMouseCursor::Hand;  //задаем изображение курсора
    }
    else
    {
        ///прячем курсор мыши
        bShowMouseCursor = false;                 //включаем показ курсора
        bEnableClickEvents = false;               //разрешаем событие щелчек мышкой по объектам
        DefaultMouseCursor = EMouseCursor::Hand;  //задаем изображение курсора
    }
}