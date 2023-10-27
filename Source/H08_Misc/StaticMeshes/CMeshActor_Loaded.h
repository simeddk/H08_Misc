#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeshActor_Loaded.generated.h"

UCLASS()
class H08_MISC_API ACMeshActor_Loaded : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMeshActor_Loaded();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	void SetPositions(const TArray<FVector>& InPositions);
	void SetNormals(const TArray<FVector>& InNormals);
	void SetColors(const TArray<FColor>& InColors);
	void SetUVs(const TArray<FVector2D>& InUVs);
	void SetIndices(const TArray<int32>& InIndices);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

private:
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;
};
