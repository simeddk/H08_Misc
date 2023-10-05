#include "CVertex.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertex::ACVertex()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");

	float p = 0.5f;

	//Front
	Positions.Add(FVector(-p, -p, -p)); //0
	Positions.Add(FVector(-p, -p, +p)); //1
	Positions.Add(FVector(-p, +p, -p)); //2
	Positions.Add(FVector(-p, +p, +p)); //3

	Indices.Add(2);
	Indices.Add(1);
	Indices.Add(0);
	Indices.Add(3);
	Indices.Add(1);
	Indices.Add(2);

	for (int32 i = 0; i < 4; i++)
		Normals.Add(FVector(-1, 0, 0));
	
	UVs.Add(FVector2D(0.646f, 1.f));
	UVs.Add(FVector2D(0.646f, 0.765f));
	UVs.Add(FVector2D(0.736f, 1.f));
	UVs.Add(FVector2D(0.736f, 0.765f));

	Colors.Add(FColor::Red);
	Colors.Add(FColor::Green);
	Colors.Add(FColor::Blue);
	Colors.Add(FColor::Cyan);

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

	ProcMesh->SetRelativeScale3D(FVector(100));
}

void ACVertex::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

