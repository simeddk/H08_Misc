#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CObject.generated.h"

UENUM(BlueprintType)
enum class EMeshType : uint8
{
	StaticMesh, SkeletalMesh, ProceduralMesh
};

UCLASS()
class H08_MISC_API UCObject : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Render")
		FVector Location;

	UPROPERTY(EditAnywhere, Category = "Render")
		EMeshType MeshType;

	UPROPERTY(EditAnywhere, Category = "Misc")
		FName Description = TEXT("Robot Mesh");

	UPROPERTY(EditAnywhere, Category = "Misc", meta = (ClampMax = 1.00, ClampMin = 0.00))
		float Alpha = 0.1f;
};
