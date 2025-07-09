// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "FlipBookViewerStyle.h"

class FFlipBookViewerCommands : public TCommands<FFlipBookViewerCommands>
{
public:

	FFlipBookViewerCommands()
		: TCommands<FFlipBookViewerCommands>(TEXT("FlipBookViewer"), NSLOCTEXT("Contexts", "FlipBookViewer", "FlipBookViewer Plugin"), NAME_None, FFlipBookViewerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenFlipBookViewer;
};
