﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "HeartGraphCanvasPin.h"
#include "UObject/Object.h"
#include "HeartCanvasConnectionVisualizer.generated.h"

USTRUCT(BlueprintType)
struct FHeartCanvasConnectionPinParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UHeartGraphCanvasPin> FromPin;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UHeartGraphCanvasPin> ToPin;
};

USTRUCT(BlueprintType)
struct FHeartCanvasConnectionSplineParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Thickness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHeartPinDirection FromDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EHeartPinDirection ToDirection;
};

/**
 *
 */
UCLASS(const, Blueprintable, Blueprintable)
class HEART_API UHeartCanvasConnectionVisualizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Heart|CanvasConnectionVisualizer")
	void DrawConnectionSpline(UPARAM(ref) FPaintContext& Context, const FVector2D& Start, const FVector2D& End,
							  const FHeartCanvasConnectionSplineParams& SplineParams) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, BlueprintNativeEvent, Category = "Heart|CanvasConnectionVisualizer")
	void PaintTimeDrawPinConnection(UPARAM(ref) FPaintContext& Context, const FVector2D& Start, const FVector2D& End,
									const FHeartCanvasConnectionPinParams& GeneralParams) const;

	// @todo  GraphDesktopGeometry is a hack because I dont know how to use the Context.AllocatedGeometry correctly
	void PaintTimeDrawPinConnections(UPARAM(ref) FPaintContext& Context, const FGeometry& GraphDesktopGeometry, TMap<UHeartGraphPin*, TPair<UHeartGraphCanvasPin*, FGeometry>> Pins);

	UFUNCTION(BlueprintCallable, BlueprintPure = false, BlueprintNativeEvent, Category = "Heart|CanvasConnectionVisualizer")
	void PaintTimeDrawPreviewConnection(UPARAM(ref) FPaintContext& Context, const FVector2D& Start, const FVector2D& End, UHeartGraphCanvasPin* FromPin) const;
};
