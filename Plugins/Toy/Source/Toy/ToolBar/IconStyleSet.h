#pragma once

#include "CoreMinimal.h"

class TOY_API FIconStyleSet
{
public:
	FIconStyleSet();
	~FIconStyleSet();

public:
	static TSharedPtr<FIconStyleSet> Get();
	static void Shutdown();

private:
	void RegisterIcon(const FString& InStyleName, const FString& InImagePath, const FVector2D& InImageSize, FSlateIcon& OutSlateIcon);

private:
	static TSharedPtr<FIconStyleSet> Instance;

private:
	const FName StyleSetName = "ToyStyle";
	TSharedPtr<class FSlateStyleSet> StyleSet;

public:
	FSlateIcon ToolBar_Icon;
	FSlateIcon ToolBar_Icon2;
};