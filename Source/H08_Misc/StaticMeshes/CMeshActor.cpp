#include "CMeshActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACMeshActor::ACMeshActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh");

	UStaticMesh* meshAsset;
	CHelpers::GetAsset(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");
	Mesh->SetStaticMesh(meshAsset);

	CHelpers::GetAsset(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Gold.MAT_Gold'");
	Mesh->SetMaterial(0, Material);

	Mesh->SetRelativeScale3D(FVector(0.25f));
}

void ACMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

