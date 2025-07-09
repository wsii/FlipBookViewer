// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlipBookViewer.h"

#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "FlipBookViewerStyle.h"
#include "FlipBookViewerCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "WidgetBlueprint.h"

static const FName FlipBookViewerTabName("FlipBookViewer");

#define LOCTEXT_NAMESPACE "FFlipBookViewerModule"

void FFlipBookViewerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFlipBookViewerStyle::Initialize();
	FFlipBookViewerStyle::ReloadTextures();

	FFlipBookViewerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFlipBookViewerCommands::Get().OpenFlipBookViewer,
		FExecuteAction::CreateRaw(this, &FFlipBookViewerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFlipBookViewerModule::RegisterMenus));
}

void FFlipBookViewerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFlipBookViewerStyle::Shutdown();

	FFlipBookViewerCommands::Unregister();
}

void FFlipBookViewerModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	const FString LoadingWidgetStr = "/Script/Blutility.EditorUtilityWidgetBlueprint'/FlipBookViewer/EUB_FlipBook.EUB_FlipBook'";
	FSoftObjectPath WidgetSoftObjectPath = FSoftObjectPath(LoadingWidgetStr);

	UWidgetBlueprint* WidgetBlueprintTemp = Cast<UWidgetBlueprint>(WidgetSoftObjectPath.TryLoad());

	if (!IsValidChecked(WidgetBlueprintTemp) || WidgetBlueprintTemp->IsUnreachable())return;
	if (!WidgetBlueprintTemp->GeneratedClass->IsChildOf(UEditorUtilityWidget::StaticClass()))return;
	
	if (UEditorUtilityWidgetBlueprint* EUWBPTemp = static_cast<UEditorUtilityWidgetBlueprint*>(WidgetBlueprintTemp))
	{
		UEditorUtilitySubsystem* EditorUtilitySubsystemTemp = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		// EditorUtilitySubsystemTemp->SpawnAndRegisterTab(EUWBPTemp);
		UEditorUtilityWidget* SpawnedWidget = EditorUtilitySubsystemTemp->SpawnAndRegisterTab(EUWBPTemp);
		if (SpawnedWidget)
		{
			SpawnedWidget->SetDesiredSizeInViewport(FVector2D(800, 600));
		}
	}
}

void FFlipBookViewerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFlipBookViewerCommands::Get().OpenFlipBookViewer, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFlipBookViewerCommands::Get().OpenFlipBookViewer));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFlipBookViewerModule, FlipBookViewer)