#include "DetailExtends.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "Serialization/BufferArchive.h"
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
	//----------------------------------------------------------------------------
	//@@ Get Mesh(Vertices) Data
	//----------------------------------------------------------------------------
	// -> Get Mesh Comp
	ACMeshActor* actor = Cast<ACMeshActor>(Objects[0]);
	UActorComponent* actorComp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* meshsComp = Cast<UStaticMeshComponent>(actorComp);
	if (meshsComp == nullptr) return FReply::Unhandled();

	// -> Get Mesh Asset
	UStaticMesh* meshAsset = meshsComp->GetStaticMesh();
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get();
	if (renderData->LODResources.Num() < 1) return FReply::Unhandled();
	
	// -> Get Vertex Data
	FStaticMeshLODResources& lod = renderData->LODResources[0];

	FPositionVertexBuffer& positionBuffer = lod.VertexBuffers.PositionVertexBuffer;
	FColorVertexBuffer& colorBuffer = lod.VertexBuffers.ColorVertexBuffer;
	FStaticMeshVertexBuffer& metaBuffer = lod.VertexBuffers.StaticMeshVertexBuffer;
	FRawStaticIndexBuffer& indexBuffer = lod.IndexBuffer;

	// -> Check Vertex Data
	if (positionBuffer.GetNumVertices() < 1) return FReply::Unhandled();
	if (indexBuffer.GetNumIndices() < 1) return FReply::Unhandled();

	uint32 vertexCount = positionBuffer.GetNumVertices();
	int32 indexCount = indexBuffer.GetNumIndices();

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);
	GLog->Logf(TEXT("Index Count : %d"), indexCount);

	//----------------------------------------------------------------------------
	//@@ Save File Dialog
	//----------------------------------------------------------------------------
	// -> Open Dialog Window
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	
	TArray<FString> savedFilePath;
	platform->SaveFileDialog(handle, "Save Dialog", path, "", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, savedFilePath);
	if (savedFilePath.Num() < 1) return FReply::Unhandled();
	
	// -> Save Vertex Data to data struct
	FVertexData data;
	
	TArray<FColor> colors;
	colorBuffer.GetVertexColors(colors);

	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i <vertexCount; i++)
			colors.Add(FColor::White);
	}

	for (uint32 i = 0; i < vertexCount; i++)
	{
		data.Positions.Add(positionBuffer.VertexPosition(i));
		data.Normals.Add(metaBuffer.VertexTangentZ(i));
		data.UVs.Add(metaBuffer.GetVertexUV(i, 0));
		data.Colors.Add(colors[i]);
	}

	TArray<uint32> indices;
	indexBuffer.GetCopy(indices);
	data.Indices.Insert((int32*)indices.GetData(), indexCount, 0);

	// -> data struct to Binary File(HDD)
	FBufferArchive fileBuffer;
	fileBuffer << data;

	FFileHelper::SaveArrayToFile(fileBuffer, *savedFilePath[0]);
	fileBuffer.FlushCache();
	fileBuffer.Empty();

	// -> data struct to PlaneText File(HDD)
	FString planeText;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");
		planeText.Append(data.Normals[i].ToString() + ",");
		planeText.Append(data.UVs[i].ToString() + ",");
		planeText.Append(data.Colors[i].ToString() + "\n");
	}
	
	FString withoutExtenstionPath = FPaths::GetBaseFilename(savedFilePath[0], false);
	FString csvSavePath = withoutExtenstionPath + ".csv";
	FFileHelper::SaveStringToFile(planeText, *csvSavePath);

	// -> Print Message
	FString str;
	str.Append(FPaths::GetCleanFilename(savedFilePath[0]));
	str.Append(" Binary File is Saved.");
	GLog->Log(str);

	str = "";
	str.Append(FPaths::GetCleanFilename(csvSavePath));
	str.Append(" Plane Text File is Saved.");
	GLog->Log(str);

	return FReply::Handled();
}
