#include "Toy.h"
#include "LevelEditor.h"
#include "ToolBar/ButtonCommand.h"
#include "ToolBar/IconStyleSet.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
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

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdow Toy Module"));

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