#include "ButtonCommand.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "Serialization/BufferArchive.h"
#include "DetailPanel/DetailExtends.h"
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "Misc/FileHelper.h"
#include "StaticMeshes/CMeshActor_Loaded.h"
#include "Viewer/MeshViewer.h"
#include "Objects/CObject.h"

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
	//----------------------------------------------------------------------------
	//@@ Load File Dialog
	//----------------------------------------------------------------------------
	// -> Open Dialog Window
	FString path;

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	TArray<FString> loadedFilePath;
	platform->OpenFileDialog(handle, "Load Dialog", path, "", "Mesh Binary File(*.bin)|*.bin", EFileDialogFlags::None, loadedFilePath);
	if (loadedFilePath.Num() < 1) return;

	//----------------------------------------------------------------------------
	//@@ Data struct from File
	//----------------------------------------------------------------------------
	// -> Load File(HDD)
	FBufferArchive fileBuffer;
	FFileHelper::LoadFileToArray(fileBuffer, *loadedFilePath[0]);
	FMemoryReader memoryReader = FMemoryReader(fileBuffer, true);
	fileBuffer.Seek(0);

	FVertexData data;
	memoryReader << data;
	memoryReader.FlushCache();
	memoryReader.Close();

	// -> Print Message
	GLog->Logf(TEXT("Vertex Count : %d"), data.Positions.Num());
	GLog->Logf(TEXT("Index Count : %d"), data.Indices.Num());

	// -> data struct data to PlaneText(*.csv)
	FString planeText;
	for (int32 i = 0; i < data.Positions.Num(); i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");
		planeText.Append(data.Normals[i].ToString() + ",");
		planeText.Append(data.UVs[i].ToString() + ",");
		planeText.Append(data.Colors[i].ToString() + "\n");
	}
	FString withoutExtenstionPath = FPaths::GetBaseFilename(loadedFilePath[0], false);
	FString csvSavePath = withoutExtenstionPath + "_Loaed.csv";
	FFileHelper::SaveStringToFile(planeText, *csvSavePath);

	//----------------------------------------------------------------------------
	//@@ Spawm
	//----------------------------------------------------------------------------
	// -> LineTrace
	FLevelEditorViewportClient* viewportClient = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();

	FVector start = viewportClient->GetViewLocation();
	FVector end = start + viewportClient->GetViewRotation().RotateVector(FVector(10000, 0, 0));

	UWorld* editorWorld = GEditor->GetEditorWorldContext().World();

	FHitResult hitResult;
	editorWorld->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility);
	if (hitResult.bBlockingHit == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Out of range"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Spawn Succeed On %s"), *hitResult.ImpactPoint.ToString());

	// -> Make Transform
	FTransform transform;

	FVector direction = hitResult.TraceEnd - hitResult.TraceStart;
	direction.Normalize();

	//FVector location = hitResult.TraceStart + direction * (hitResult.Distance);
	transform.SetLocation(hitResult.ImpactPoint);

	FRotator rotation = FRotator(0, direction.Rotation().Yaw, 0);
	transform.SetRotation(FQuat(rotation));
	transform.SetScale3D(FVector(0.5f));

	// -> Spawn Deffered from data struct
	ACMeshActor_Loaded* loadedActor = editorWorld->SpawnActorDeferred<ACMeshActor_Loaded>
	(
		ACMeshActor_Loaded::StaticClass(),
		transform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);

	loadedActor->SetPositions(data.Positions);
	loadedActor->SetNormals(data.Normals);
	loadedActor->SetColors(data.Colors);
	loadedActor->SetUVs(data.UVs);
	loadedActor->SetIndices(data.Indices);

	loadedActor->FinishSpawning(transform);
}	


	
void FButtonCommand::OnClicked2()
{
	FMeshViewer::OpenWindow(NewObject<UCObject>());
}
