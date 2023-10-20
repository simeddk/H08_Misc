#include "ButtonCommand.h"

FButtonCommand::FButtonCommand()
	: TCommands("LoadMesh", FText::FromString("Load Mesh"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

FButtonCommand::~FButtonCommand()
{
}

void FButtonCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE ""
	UI_COMMAND(CommandInfo, "FriendlyName", "Load Mesh Data", EUserInterfaceActionType::Button,	FInputChord(),);
#undef LOCTEXT_NAMESPACE

}
