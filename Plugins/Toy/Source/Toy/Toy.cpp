#include "Toy.h"
#include "LevelEditor.h"
#include "ToolBar/ButtonCommand.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("Startup Toy Module"));

	Extender = MakeShareable(new FExtender());

	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar);
	Extender->AddToolBarExtension("Compile", EExtensionHook::Before, nullptr, toolBarExtensionDelegate);

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);

	
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdow Toy Module"));
}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{
	InToolBarBuilder.AddSeparator();
	
	//Todo. 버튼은 이미 있는데(과연?), 스타일이 없군...
	//InToolBarBuilder.AddToolBarButton
	//(
	//	FButtonCommand::Get().CommandInfo, //만들어진 버튼 객체
	//	,
	//);
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FToyModule, Toy)