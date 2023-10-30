#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class TOY_API SMeshViewer_Viewport : public SEditorViewport, public FGCObject
{
public:
	SMeshViewer_Viewport();

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	class UStaticMeshComponent* RobotMesh;
	class UStaticMeshComponent* FloorMesh;
};
