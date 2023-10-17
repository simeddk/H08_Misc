#include "CSlicable.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

ACSlicable::ACSlicable()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &SrcMesh, "SrcMesh", Root);
	CHelpers::CreateSceneComponent(this, &DstMesh, "DstMesh", Root);

	UStaticMesh* smAsset;
	CHelpers::GetAsset<UStaticMesh>(&smAsset, "StaticMesh'/Game/StaticMeshes/1M_Cube_Chamfer_CPUAccess.1M_Cube_Chamfer_CPUAccess'");
	SrcMesh->SetStaticMesh(smAsset);
	SrcMesh->SetVisibility(false);
	SrcMesh->SetCollisionProfileName("NoCollision");

	DstMesh->SetSimulatePhysics(true);
	DstMesh->bUseComplexAsSimpleCollision = false;
}

void ACSlicable::OnConstruction(const FTransform& Transform)
{
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent
	(
		SrcMesh,
		0,
		DstMesh,
		true
	);
}

void ACSlicable::BeginPlay()
{
	Super::BeginPlay();
	
}

