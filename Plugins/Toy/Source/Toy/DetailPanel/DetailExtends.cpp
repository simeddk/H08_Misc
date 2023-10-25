#include "DetailExtends.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "StaticMeshes/CMeshActor.h"

TSharedRef<class IDetailCustomization> FDetailExtends::MakeInstance()
{
	return MakeShareable(new FDetailExtends());
}

void FDetailExtends::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("ToyPlugIn");

	//Shuffle Material Button
	category.AddCustomRow(FText::FromString("Shuffle Material"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Shuffle Material"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.HAlign(HAlign_Fill)
	.MaxDesiredWidth(250.f)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FDetailExtends::OnClicked_ShuffleMaterial)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Shuffle"))
		]
	];

	//Save Mesh Data
	category.AddCustomRow(FText::FromString("Save Mesh Data"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(FText::FromString("Save Mesh Data"))
	]
	.ValueContent()
	.VAlign(VAlign_Center)
	.HAlign(HAlign_Fill)
	.MaxDesiredWidth(250.f)
	[
		SNew(SButton)
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.OnClicked(this, &FDetailExtends::OnClicked_SaveMeshData)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Save To Binary File"))
		]
	];



	DetailBuilder.GetObjectsBeingCustomized(Objects);
}


FReply FDetailExtends::OnClicked_ShuffleMaterial()
{
	ACMeshActor* staticMeshActor = Cast<ACMeshActor>(Objects[0]);
	if (staticMeshActor == nullptr) return FReply::Unhandled();
		
	staticMeshActor->ShuffleMaterialParameter();

	return FReply::Handled();
}

FReply FDetailExtends::OnClicked_SaveMeshData()
{
	//Todo. Read Vertex(Mesh) -> Mem -> HDD


	//Save File Dialog
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	
	TArray<FString> savedFilePath;
	platform->SaveFileDialog(handle, "Save Dialog", path, "", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, savedFilePath);
	if (savedFilePath.Num() < 1) return FReply::Unhandled();

	GLog->Log(*savedFilePath[0]);

	return FReply::Handled();
}
