// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipBookViewerCommands.h"

#define LOCTEXT_NAMESPACE "FFlipBookViewerModule"

void FFlipBookViewerCommands::RegisterCommands()
{
	UI_COMMAND(OpenFlipBookViewer, "FlipBookViewer", "Execute FlipBookViewer action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
