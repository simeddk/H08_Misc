#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMeshActor.generated.h"

UCLASS()
class H08_MISC_API ACMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMeshActor();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;
};
