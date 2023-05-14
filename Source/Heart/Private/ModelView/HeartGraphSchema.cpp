﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "ModelView/HeartGraphSchema.h"
#include "Model/HeartGraphNode.h"

UHeartGraphSchema::UHeartGraphSchema()
{
#if WITH_EDITORONLY_DATA
	DefaultEditorStyle = "Horizontal";
#endif
}

bool UHeartGraphSchema::TryGetWorldForGraph_Implementation(const UHeartGraph* HeartGraph, UWorld*& World) const
{
	return false;
}

UObject* UHeartGraphSchema::GetConnectionVisualizer() const
{
	if (auto&& Class = GetConnectionVisualizerClass())
	{
		return Class->GetDefaultObject();
	}

	return nullptr;
}

bool UHeartGraphSchema::TryConnectPins_Implementation(UHeartGraph* Graph, FHeartGraphPinReference PinA, FHeartGraphPinReference PinB) const
{
	UHeartGraphNode* NodeA = Graph->GetNode(PinA.NodeGuid);
	UHeartGraphNode* NodeB = Graph->GetNode(PinB.NodeGuid);

	const FHeartConnectPinsResponse Response = CanPinsConnect(Graph, PinA, PinB);

	bool bModified = false;

	switch (Response.Response)
	{
	case EHeartCanConnectPinsResponse::Allow:
		Graph->ConnectPins(PinA, PinB);
		bModified = true;
		break;

	case EHeartCanConnectPinsResponse::AllowBreakA:
		Graph->DisconnectAllPins(PinA);
		Graph->ConnectPins(PinA, PinB);
		bModified = true;
		break;

	case EHeartCanConnectPinsResponse::AllowBreakB:
		Graph->DisconnectAllPins(PinB);
		Graph->ConnectPins(PinA, PinB);
		bModified = true;
		break;

	case EHeartCanConnectPinsResponse::AllowBreakAB:
		Graph->DisconnectAllPins(PinA);
		Graph->DisconnectAllPins(PinB);
		Graph->ConnectPins(PinA, PinB);
		bModified = true;
		break;

	/**
	case CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE:
		bModified = CreateAutomaticConversionNodeAndConnections(PinA, PinB);
		break;

	case CONNECT_RESPONSE_MAKE_WITH_PROMOTION:
		bModified = CreatePromotedConnection(PinA, PinB);
		break;
	*/

	case EHeartCanConnectPinsResponse::Disallow:
	default:
		break;
	}

	if (bModified)
	{
		NodeA->NotifyPinConnectionsChanged(PinA.PinGuid);
		NodeB->NotifyPinConnectionsChanged(PinB.PinGuid);
		Graph->NotifyNodeConnectionsChanged({NodeA, NodeB}, {PinA.PinGuid, PinB.PinGuid});
	}

	return bModified;
}
FHeartConnectPinsResponse UHeartGraphSchema::CanPinsConnect_Implementation(const UHeartGraph* Graph, FHeartGraphPinReference PinA, FHeartGraphPinReference PinB) const
{
	return FHeartConnectPinsResponse{EHeartCanConnectPinsResponse::Allow};
}

void UHeartGraphSchema::CreateDefaultNodesForGraph_Implementation(UHeartGraph* Graph) const
{
	// Does nothing by default
}

UClass* UHeartGraphSchema::GetConnectionVisualizerClass_Implementation() const
{
	return nullptr;
}
