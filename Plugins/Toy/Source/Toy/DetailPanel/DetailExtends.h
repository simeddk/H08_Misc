#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FVertexData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive& InArchive, FVertexData& InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.Colors
			<< InData.UVs
			<< InData.Indices;
	}
};

class TOY_API FDetailExtends : public IDetailCustomization
{
public:
	static TSharedRef<class IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveMeshData();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
