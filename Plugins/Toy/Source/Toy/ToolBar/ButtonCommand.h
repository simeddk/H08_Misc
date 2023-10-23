#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;

private:
	void OnClicked();
	void OnClicked2();

public:
	TSharedPtr<FUICommandInfo> CommandInfo;
	TSharedPtr<FUICommandInfo> CommandInfo2;

	TSharedPtr<FUICommandList> CommandList;
};
