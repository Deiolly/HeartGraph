﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "HeartSceneGenerator.h"

#include "HeartSceneModule.h"
#include "HeartSceneNode.h"
#include "GraphRegistry/HeartRegistryRuntimeSubsystem.h"

#include "Model/HeartGraph.h"
#include "Model/HeartGraphNode.h"

UHeartSceneGenerator::UHeartSceneGenerator()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UHeartGraph* UHeartSceneGenerator::GetHeartGraph() const
{
	return Graph;
}

void UHeartSceneGenerator::SetDisplayedGraph(UHeartGraph* NewGraph)
{
	if (IsValid(Graph))
	{
		OnReset();
	}

	Graph = NewGraph;
}

void UHeartSceneGenerator::Regenerate()
{
	OnReset();
	Generate();
}

UHeartSceneNode* UHeartSceneGenerator::GetSceneNode(const FHeartNodeGuid& NodeGuid) const
{
	if (auto&& Node = SceneNodes.Find(NodeGuid))
	{
		return *Node;
	}
	return nullptr;
}

void UHeartSceneGenerator::OnReset_Implementation()
{
}

void UHeartSceneGenerator::Generate_Implementation()
{
}

TSubclassOf<UHeartSceneNode> UHeartSceneGenerator::GetVisualClassForNode(const UHeartGraphNode* GraphNode) const
{
	auto&& RegistrySubsystem = GEngine->GetEngineSubsystem<UHeartRegistryRuntimeSubsystem>();

	if (!IsValid(RegistrySubsystem))
	{
		UE_LOG(LogHeartGraphScene, Error,
			TEXT("Registry Subsystem not found! Make sure to enable `CreateRuntimeRegistrySubsystem` in project settings to access the subsystem!\n"
					"This error occured in UHeartSceneGenerator::GetVisualClassForNode. You can override this function to not use the registry subsystem if `CreateRuntimeRegistrySubsystem` is disabled on purpose!"))
		return nullptr;
	}

	return RegistrySubsystem->GetRegistry(Graph->GetClass())
								->GetVisualizerClassForGraphNode<UHeartSceneNode>(GraphNode->GetClass());
}

UHeartSceneNode* UHeartSceneGenerator::AddNodeToDisplay(UHeartGraphNode* GraphNode)
{
	// This function is only used internally, so Node should *always* be validated prior to this point.
	check(GraphNode);

	if (const TSubclassOf<UHeartSceneNode> VisualizerClass = GetVisualClassForNode(GraphNode))
	{
		auto&& SceneNode = NewObject<UHeartSceneNode>(GetOwner(), VisualizerClass);
		check(SceneNode);

		SceneNode->Generator = this;
		SceneNode->GraphNode = GraphNode;

		SceneNodes.Add(GraphNode->GetGuid(), SceneNode);

		SceneNode->RegisterComponent();

		SceneNode->NativeOnCreated();

		return SceneNode;
	}
	else
	{
		UE_LOG(LogHeartGraphScene, Warning, TEXT("Unable to determine Visual Class. Node '%s' will not be displayed"), *GraphNode->GetName())
		return nullptr;
	}
}