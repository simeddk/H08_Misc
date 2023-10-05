#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertex.generated.h"

UCLASS()
class H08_MISC_API ACVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	ACVertex();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;

private:
	FOccluderVertexArray Positions;
	FJsonSerializableArrayInt Indices;
	FOccluderVertexArray Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> Colors;
};
