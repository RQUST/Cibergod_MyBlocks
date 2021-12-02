// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
    // displaying the cursor or hiding the cursor
    ShowMouseCursor = true;
}

void AMyPlayerController::ShowHideCursor()
{
    // if there is a jackdaw, the cursor is displayed
    if (ShowMouseCursor)
    {
        bShowMouseCursor = true;                  // enabling cursor display
        bEnableClickEvents = true;                // enabling the mouse click event on objects
        DefaultMouseCursor = EMouseCursor::Hand;  // setting the cursor image
    }
    else
    {
        /// hiding the mouse cursor
        bShowMouseCursor = false;
        bEnableClickEvents = false;
        DefaultMouseCursor = EMouseCursor::Hand;
    }
}