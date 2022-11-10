﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "HeartWidgetInputBindingBase.generated.h"

class UHeartWidgetInputLinker;
class UHeartWidgetInputCondition;

/**
 *
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class HEARTCORE_API UHeartWidgetInputBindingBase : public UObject
{
	GENERATED_BODY()

public:
	virtual bool Bind(UHeartWidgetInputLinker* Linker) { return false; }
	virtual bool Unbind(UHeartWidgetInputLinker* Linker) { return false; }

	// Optionally set condition
	UPROPERTY(EditAnywhere, Instanced, meta = (DisplayPriority = 100))
	TObjectPtr<UHeartWidgetInputCondition> Condition;
};
