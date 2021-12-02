// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyPlayerController.h" 

AMyGameMode::AMyGameMode() 
{
    //there is no default player
    DefaultPawnClass = NULL;

    PlayerControllerClass = AMyPlayerController::StaticClass();
}