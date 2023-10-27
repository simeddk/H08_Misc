#include "CMeshActor_Loaded.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACMeshActor_Loaded::ACMeshActor_Loaded()
{
	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");
}

void ACMeshActor_Loaded::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection
	(
		0,
		Positions,
		Indices,
		Normals,
		UVs,
		Colors,
		TArray<FProcMeshTangent>(),
		true
	);

	CHelpers::GetAssetDynamic(&Material, "MaterialInstanceConstant'/Game/StaticMeshes/SM_Merged.M_SM_Merged'");
	ProcMesh->SetMaterial(0, Material);
}

void ACMeshActor_Loaded::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACMeshActor_Loaded::SetPositions(const TArray<FVector>& InPositions)
{
	Positions = InPositions;
}

void ACMeshActor_Loaded::SetNormals(const TArray<FVector>& InNormals)
{
	Normals = InNormals;
}

void ACMeshActor_Loaded::SetColors(const TArray<FColor>& InColors)
{
	Colors = InColors;
}

void ACMeshActor_Loaded::SetUVs(const TArray<FVector2D>& InUVs)
{
	UVs = InUVs;
}

void ACMeshActor_Loaded::SetIndices(const TArray<int32>& InIndices)
{
	Indices = InIndices;
}