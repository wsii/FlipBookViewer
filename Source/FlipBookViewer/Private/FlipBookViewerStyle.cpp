// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipBookViewerStyle.h"
#include "FlipBookViewer.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FFlipBookViewerStyle::StyleInstance = nullptr;

void FFlipBookViewerStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FFlipBookViewerStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FFlipBookViewerStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("FlipBookViewerStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FFlipBookViewerStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("FlipBookViewerStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("FlipBookViewer")->GetBaseDir() / TEXT("Resources"));

	Style->Set("FlipBookViewer.OpenFlipBookViewer", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FFlipBookViewerStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FFlipBookViewerStyle::Get()
{
	return *StyleInstance;
}
