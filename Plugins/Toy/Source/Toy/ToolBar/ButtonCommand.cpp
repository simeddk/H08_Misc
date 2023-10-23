#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("LoadMesh", FText::FromString("Load Mesh"), NAME_None, FEditorStyle::GetStyleSetName())
{
	CommandList = MakeShareable(new FUICommandList());
}

FButtonCommand::~FButtonCommand()
{
	if (CommandList.IsValid())
		CommandList.Reset();
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(CommandInfo, "LoadMesh", "Load Mesh Data", EUserInterfaceActionType::Button,	FInputChord());
	UI_COMMAND(CommandInfo2, "OpenViewer", "Open Viewer", EUserInterfaceActionType::Button,	FInputChord());
#undef LOCTEXT_NAMESPACE

	CommandList->MapAction
	(
		CommandInfo,
		FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked),
		FCanExecuteAction()
	);

	CommandList->MapAction
	(
		CommandInfo2,
		FExecuteAction::CreateRaw(this, &FButtonCommand::OnClicked2),
		FCanExecuteAction()
	);

}

void FButtonCommand::OnClicked()
{
	//UE_LOG(LogTemp, Error, TEXT("Toy Button Clicked"));

	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);

	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Error, TEXT("%s"), *brush->GetResourceName().ToString());
}

void FButtonCommand::OnClicked2()
{
	UE_LOG(LogTemp, Error, TEXT("Open Viewer Button is Clicked"));
}
