#include "MeshViewer_Viewport_Client.h"
#include "MeshViewer_Viewport.h"

FMeshViewer_Viewport_Client::FMeshViewer_Viewport_Client(FPreviewScene* InPreviewScene, const TSharedRef<SMeshViewer_Viewport>& InEditorViewportWidget)
	: FEditorViewportClient(nullptr, InPreviewScene, StaticCastSharedRef<SMeshViewer_Viewport>(InEditorViewportWidget))
{
	SetViewMode(VMI_Lit);

	SetViewRotation(FRotator(-20, -90, 0));
	SetViewLocationForOrbiting(FVector(0, 0, 100), 1000);
}

