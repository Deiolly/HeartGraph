﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "PreviewSceneConfig.generated.h"

class AHeartSceneActor;

UCLASS()
class HEARTSCENEEDITOR_API UPreviewSceneConfig : public UActorComponent
{
	GENERATED_BODY()

public:
	UPreviewSceneConfig();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	DECLARE_DELEGATE_OneParam(FOnConfigEdit, const FPropertyChangedEvent&);
	FOnConfigEdit OnConfigEdit;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AHeartSceneActor> SceneClassOverride;
};
