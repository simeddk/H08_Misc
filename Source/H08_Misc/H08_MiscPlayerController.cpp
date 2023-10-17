// Copyright Epic Games, Inc. All Rights Reserved.

#include "H08_MiscPlayerController.h"
#include "Global.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "H08_MiscCharacter.h"
#include "Engine/World.h"
#include "KismetProceduralMeshLibrary.h"
#include "Materials/MaterialInstanceConstant.h"

AH08_MiscPlayerController::AH08_MiscPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AH08_MiscPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AH08_MiscPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AH08_MiscPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AH08_MiscPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AH08_MiscPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AH08_MiscPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AH08_MiscPlayerController::OnResetVR);

	InputComponent->BindAction("Slice", IE_Pressed, this, &AH08_MiscPlayerController::OnSlice);
}

void AH08_MiscPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AH08_MiscPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AH08_MiscCharacter* MyPawn = Cast<AH08_MiscCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AH08_MiscPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AH08_MiscPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AH08_MiscPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AH08_MiscPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AH08_MiscPlayerController::OnSlice()
{
	//LineTrace for Visibility
	FVector start = GetPawn()->GetActorLocation();
	FVector end = FVector(CursorLocation.X, CursorLocation.Y, start.Z);

	TArray<AActor*> ignores;
	ignores.Add(GetPawn());

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ignores,
		EDrawDebugTrace::ForDuration,
		hitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Red,
		1.f
	);
	CheckFalse(hitResult.IsValidBlockingHit());

	//Slice ProceduralMesh
	UProceduralMeshComponent* otherProcMeshComp = Cast<UProceduralMeshComponent>(hitResult.Component);
	CheckNull(otherProcMeshComp);

	FVector lineDirection = (end - start).GetSafeNormal();
	FVector planeNormal = lineDirection ^ GetPawn()->GetActorUpVector();

	UProceduralMeshComponent* newProcMeshComp = nullptr;
	UMaterialInstanceConstant* materialAsset;
	CHelpers::GetAssetDynamic(&materialAsset, "MaterialInstanceConstant'/Game/Materials/Vertex/MAT_ViewSpace_Inst.MAT_ViewSpace_Inst'");

	UKismetProceduralMeshLibrary::SliceProceduralMesh
	(
		otherProcMeshComp,
		hitResult.Location,
		planeNormal,
		true,
		newProcMeshComp,
		EProcMeshSliceCapOption::CreateNewSectionForCap,
		materialAsset
	);

	newProcMeshComp->SetSimulatePhysics(true);
	newProcMeshComp->AddImpulse(lineDirection * 600.f, NAME_None, true);
}
