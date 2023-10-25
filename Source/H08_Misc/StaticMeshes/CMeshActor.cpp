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

#if WITH_EDITOR
void ACMeshActor::ShuffleMaterialParameter()
{
	int32 random = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1);

	//Texture Parameter Set
	for (const FTextureParameterValue& param : Material->TextureParameterValues)
	{
		if (param.ParameterInfo.Name.Compare("BaseMap") == 0)
			Material->SetTextureParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].BaseMap);

		if (param.ParameterInfo.Name.Compare("NormalMap") == 0)
			Material->SetTextureParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].NormalMap);

		if (param.ParameterInfo.Name.Compare("RoughnessMap") == 0)
			Material->SetTextureParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].RoughnessMap);
	}

	//Scalar Parameter Set
	for (const FScalarParameterValue& param : Material->ScalarParameterValues)
	{
		if (param.ParameterInfo.Name.Compare("Matalic") == 0)
			Material->SetScalarParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].Metalic);

		if (param.ParameterInfo.Name.Compare("Roughness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].Roughness_Min);

		if (param.ParameterInfo.Name.Compare("Roughness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(param.ParameterInfo, MaterialParameters[random].Roughness_Max);
	}
}
#endif

