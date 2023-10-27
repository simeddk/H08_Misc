#include "MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");

void FMeshViewer::OpenWindow(UObject* InAsset)
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();

		Instance.Reset();
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());
	Instance->Open_Internal(InAsset);
}

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
		Instance->CloseWindow();
}

void FMeshViewer::Open_Internal(UObject* InAsset)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
		);

	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone,
		TSharedPtr<IToolkitHost>(),
		ToolkitName,
		layout,
		true,
		true,
		InAsset
	);
}

FName FMeshViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText::FromName(ToolkitName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return ToolkitName.ToString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor(1, 0, 0, 1);
}
