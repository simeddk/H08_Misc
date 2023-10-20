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
	
	//Todo. ��ư�� �̹� �ִµ�(����?), ��Ÿ���� ����...
	//InToolBarBuilder.AddToolBarButton
	//(
	//	FButtonCommand::Get().CommandInfo, //������� ��ư ��ü
	//	,
	//);
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FToyModule, Toy)