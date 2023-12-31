#include "MeshViewer.h"
#include "MeshViewer_Viewport.h"
#include "AdvancedPreviewSceneModule.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");
const static FName ViewPortTabID = TEXT("Viewport");
const static FName PreviewTabID = TEXT("Preview");
const static FName DetailsTabID = TEXT("Details");

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
	//Create ViewportWidget
	ViewportWidget = SNew(SMeshViewer_Viewport);

	//Create PreviewSceneSettingsWidget
	FAdvancedPreviewSceneModule& scene = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");
	PreviewSceneSettingsWidget = scene.CreateAdvancedPreviewSceneSettingsWidget(ViewportWidget->GetScene());

	//Create DetailsViewWidget
	FPropertyEditorModule& propertEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs detailsViewArgs(true, true, true, FDetailsViewArgs::ObjectsUseNameArea);
	DetailsViewWidget = propertEditor.CreateDetailView(detailsViewArgs);
	DetailsViewWidget->SetObject(InAsset);

	//Layout
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
		(
			//Canvas
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)

			// -> ToolBar
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
			)

			// -> Panel
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.75f)

				// ->-> Viewport
				->Split
				(
					FTabManager::NewStack()
					->AddTab(ViewPortTabID, ETabState::OpenedTab)
				)

				// ->-> Right Panel
				->Split
				(
					// ->->-> Preview
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.25f)
					->Split
					(
						FTabManager::NewStack()
						->AddTab(PreviewTabID, ETabState::OpenedTab)
					)

					// ->->-> Details
					->Split
					(
						FTabManager::NewStack()
						->AddTab(DetailsTabID, ETabState::OpenedTab)
					)

				) //End Right Panel
			) //End Panel
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

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	
	//Viewport Attach to Layout
	FOnSpawnTab viewPortSpawnTab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);
	TabManager->RegisterTabSpawner(ViewPortTabID, viewPortSpawnTab);

	//PreviewSceneSettsings Attach to Layout
	FOnSpawnTab previewSceneSettingsSpawnTab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_PreviewSettingsTab);
	TabManager->RegisterTabSpawner(PreviewTabID, previewSceneSettingsSpawnTab);

	//DetailsView Attach to Layout
	FOnSpawnTab detailsViewSpawnTab = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_DetailsViewTab);
	TabManager->RegisterTabSpawner(DetailsTabID, detailsViewSpawnTab);
}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			ViewportWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMeshViewer::Spawn_PreviewSettingsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			PreviewSceneSettingsWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMeshViewer::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			DetailsViewWidget.ToSharedRef()
		];
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
