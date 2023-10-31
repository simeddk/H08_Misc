#include "Toy.h"
#include "LevelEditor.h"
#include "GameplayDebugger.h"
#include "AssetToolsModule.h"
#include "IAssetTypeActions.h"
#include "ToolBar/ButtonCommand.h"
#include "ToolBar/IconStyleSet.h"
#include "DebuggerCategory/DebuggerCategory.h"
#include "DetailPanel/DetailExtends.h"
#include "StaticMeshes/CMeshActor.h"
#include "Viewer/MeshViewer.h"
#include "AssetTools/CAssetAction.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	//ToolBar
	{
		UE_LOG(LogTemp, Error, TEXT("Startup Toy Module"));

		FIconStyleSet::Get();
		FButtonCommand::Register();
		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().CommandList, toolBarExtensionDelegate);

		FToolBarExtensionDelegate toolBarExtensionDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar2);
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().CommandList, toolBarExtensionDelegate2);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}
	
	//DebuggerCategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		IGameplayDebugger::FOnGetCategory makeInstanceDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);
		
		gameplayDebugger.Get().RegisterCategory
		(
			"AwesomeCategory",
			makeInstanceDelegate,
			EGameplayDebuggerCategoryState::EnabledInGameAndSimulate,
			5
		);

		gameplayDebugger.NotifyCategoriesChanged();
	}

	//DetailCustomization
	{
		FPropertyEditorModule& propertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		propertyEditor.RegisterCustomClassLayout
		(
			ACMeshActor::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FDetailExtends::MakeInstance)
		);
	}

	//AssetTool
	{
		IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		//EAssetTypeCategories::Type category = EAssetTypeCategories::Misc;
		EAssetTypeCategories::Type category = assetTools.RegisterAdvancedAssetCategory(NAME_None, FText::FromString("Awesome Category"));

		AssetToolsAction = MakeShareable(new CAssetAction(category));
		assetTools.RegisterAssetTypeActions(AssetToolsAction.ToSharedRef());
	}
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdow Toy Module"));

	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("AwesomeCategory");

	FMeshViewer::Shutdown();
	FIconStyleSet::Shutdown();
}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddSeparator();
	
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().CommandInfo,
		NAME_None,
		FText::FromString("Load Mesh"),
		FText::FromString("Load Mesh Data"),
		FIconStyleSet::Get()->ToolBar_Icon
	);
}

void FToyModule::AddToolBar2(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddToolBarButton
	(
		FButtonCommand::Get().CommandInfo2,
		NAME_None,
		FText::FromString("Open Viewer"),
		FText::FromString("Open Viewer"),
		FIconStyleSet::Get()->ToolBar_Icon2
	);
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FToyModule, Toy)