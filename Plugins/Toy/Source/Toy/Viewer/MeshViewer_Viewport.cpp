#include "MeshViewer_Viewport.h"
#include "MeshViewer_Viewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Components/StaticMeshComponent.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
}

void SMeshViewer_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(InArgs);

	//FloorMesh
	UStaticMesh* floorMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'"));
	FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	FloorMesh->SetStaticMesh(floorMeshAsset);

	FTransform transform;
	transform.SetScale3D(FVector(5, 5, 1));
	Scene->AddComponent(FloorMesh, transform);

	//RobotMesh
	UStaticMesh* robotMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Robot/SM_Robot.SM_Robot'"));
	RobotMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	RobotMesh->SetStaticMesh(robotMeshAsset);

	transform.SetLocation(FVector(0, 0, 150));
	transform.SetScale3D(FVector(1));
	Scene->AddComponent(RobotMesh, transform);
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);
	Collector.AddReferencedObject(FloorMesh);
}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FMeshViewer_Viewport_Client(Scene.Get(), SharedThis(this)));

	return ViewportClient.ToSharedRef();
}


