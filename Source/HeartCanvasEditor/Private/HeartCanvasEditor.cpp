﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "HeartCanvasEditorModule.h"
#include "HeartEditorModule.h"

#include "Preview/ApplicationMode_PreviewCanvas.h"

#include "Model/HeartGraph.h"
#include "HeartCanvasExtension.h"


#define LOCTEXT_NAMESPACE "HeartCanvasEditorModule"

void FHeartCanvasEditorModule::StartupModule()
{
	// Register 3D scene preview application mode
	FHeartEditorModule& HeartEditorModule = FModuleManager::LoadModuleChecked<FHeartEditorModule>("HeartEditor");

	FHeartRegisteredApplicationMode PreviewCanvas;
	PreviewCanvas.LocalizedName = LOCTEXT("ApplicationMode_PreviewCanvas.LocalizedName", "Canvas");
	PreviewCanvas.TooltipText = LOCTEXT("ApplicationMode_PreviewCanvas.TooltipText", "Switch to Preview Canvas Mode");
	PreviewCanvas.CreateModeInstance.BindLambda(
		[](const TSharedRef<Heart::AssetEditor::FHeartGraphEditor>& Editor)
		{
			return MakeShareable(new Heart::AssetEditor::FApplicationMode_PreviewCanvas(Editor));
		});
	PreviewCanvas.SupportsAsset.BindLambda(
		[](const UHeartGraph* Asset)
		{
			return IsValid(Asset->GetExtension<UHeartCanvasExtension>());
		});

	HeartEditorModule.RegisterApplicationMode(Heart::AssetEditor::FApplicationMode_PreviewCanvas::ModeID, PreviewCanvas);
}

void FHeartCanvasEditorModule::ShutdownModule()
{
	// Remove registered application mode
	FHeartEditorModule& HeartEditorModule = FModuleManager::LoadModuleChecked<FHeartEditorModule>("HeartEditor");
	HeartEditorModule.DeregisterApplicationMode(Heart::AssetEditor::FApplicationMode_PreviewCanvas::ModeID);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FHeartCanvasEditorModule, HeartCanvasEditor)