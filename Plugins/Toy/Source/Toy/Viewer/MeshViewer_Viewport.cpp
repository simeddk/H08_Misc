#include "MeshViewer_Viewport.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);
	Collector.AddReferencedObject(FloorMesh);
}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	return MakeShareable(new FEditorViewportClient());
}

SMeshViewer_Viewport::~SMeshViewer_Viewport()
{
}
