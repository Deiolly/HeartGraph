﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "ModelView/HeartNodeLocationAccessor.h"
#include "HeartNodeLocationModifier_SnapToHex.generated.h"

/**
 * Rounds locations to snap to a hex grid
 */
UCLASS(DisplayName = "Modifier - Snap to Hex")
class HEART_API UHeartNodeLocationModifier_SnapToHex : public UHeartNodeLocationModifier
{
	GENERATED_BODY()

public:
	virtual FVector2D LocationToProxy(const FVector2D& Location) const override;
	virtual FVector2D ProxyToLocation(const FVector2D& Proxy) const override;

	virtual FVector LocationToProxy3D(const FVector& Location) const override;
	virtual FVector ProxyToLocation3D(const FVector& Proxy) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "SnapToHex", meta = (ClampMin = 1.0))
	double GridSize = 50;
};
