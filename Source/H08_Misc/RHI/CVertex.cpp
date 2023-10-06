#include "CVertex.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertex::ACVertex()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 5.f;

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");

	float p = 0.5f;

	//Front
	Positions.Add(FVector(-p, -p, -p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p, -p, +p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p, +p, -p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-p, +p, +p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));
		Colors.Add(FColor::Red);
	}
	AddIndices(0);

	//Back
	Positions.Add(FVector(+p, +p, -p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p, +p, +p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p, -p, -p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p, -p, +p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(+1, 0, 0));
		Colors.Add(FColor::Green);
	}
	AddIndices(4);


	//Top
	Positions.Add(FVector(-p, -p, +p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p, -p, +p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p, +p, +p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p, +p, +p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, +1));
		Colors.Add(FColor::Blue);
	}
	AddIndices(8);


	//Bottom
	Positions.Add(FVector(-p, -p, -p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p, +p, -p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p, -p, -p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p, +p, -p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, 0, -1));
		Colors.Add(FColor::Cyan);
	}
	AddIndices(12);


	//Left
	Positions.Add(FVector(+p, -p, -p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(+p, -p, +p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(-p, -p, -p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(-p, -p, +p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, -1, 0));
		Colors.Add(FColor::Magenta);
	}
	AddIndices(16);


	//Right
	Positions.Add(FVector(-p, +p, -p)); UVs.Add(FVector2D(0, 1));
	Positions.Add(FVector(-p, +p, +p)); UVs.Add(FVector2D(0, 0));
	Positions.Add(FVector(+p, +p, -p)); UVs.Add(FVector2D(1, 1));
	Positions.Add(FVector(+p, +p, +p)); UVs.Add(FVector2D(1, 0));

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(0, +1, 0));
		Colors.Add(FColor::Yellow);
	}
	AddIndices(20);
	
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

	for (int32 i = 0; i < Colors.Num() / 4; i++)
	{
		FColor randomColor = FColor::MakeRandomColor();
		randomColor.A = 1.f;

		Colors[i * 4 + 0] = randomColor;
		Colors[i * 4 + 1] = randomColor;
		Colors[i * 4 + 2] = randomColor;
		Colors[i * 4 + 3] = randomColor;
	}
	
	ProcMesh->UpdateMeshSection(0, Positions, Normals, UVs, Colors, TArray<FProcMeshTangent>());


	//-> 2. 아마도.. 정점 단위에서 색변화가 있을 것 -> 면 단위로 바꾸려면?
}

void ACVertex::AddIndices(int32 InStart)
{
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);
}

