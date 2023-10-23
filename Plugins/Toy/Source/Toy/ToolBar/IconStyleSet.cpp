#include "IconStyleSet.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyleSet> FIconStyleSet::Instance = nullptr;

TSharedPtr<FIconStyleSet> FIconStyleSet::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyleSet());
	
	return Instance;
}

void FIconStyleSet::Shutdown()
{
	if (Instance.IsValid())
		Instance.Reset();
}


FIconStyleSet::FIconStyleSet()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();
	path /= "Resources";
	StyleSet->SetContentRoot(path);

	RegisterIcon("ToolBarIcon", path / "Icon.png", FVector2D(48), ToolBar_Icon);
	RegisterIcon("ToolBarIcon2", path / "Icon2.png", FVector2D(48), ToolBar_Icon2);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FIconStyleSet::RegisterIcon(const FString& InStyleName, const FString& InImagePath, const FVector2D& InImageSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InImagePath, InImageSize);
	
	FString name = StyleSetName.ToString() + "."  + InStyleName;
	StyleSet->Set(FName(name), brush);

	OutSlateIcon = FSlateIcon(FName(StyleSetName), FName(name));
}

FIconStyleSet::~FIconStyleSet()
{
	if (StyleSet.IsValid() == false) return;
	
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);
	StyleSet.Reset();
}