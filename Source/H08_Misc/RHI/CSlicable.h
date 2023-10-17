#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSlicable.generated.h"

UCLASS()
class H08_MISC_API ACSlicable : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSlicable();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* SrcMesh; //Source(원본)

	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* DstMesh; //Destination(사본)

};
