#include "DebuggerCategory.h"
#include "CanvasItem.h"

TSharedRef<class FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FDebuggerCategory());
}

FDebuggerCategory::FDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;
}

FDebuggerCategory::~FDebuggerCategory()
{
}

void FDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	APawn* playerPawn = OwnerPC->GetPawn();

	//PlayerData
	{
		PlayerData.Name = playerPawn->GetName();
		PlayerData.Location = playerPawn->GetActorLocation();
		PlayerData.Forward = playerPawn->GetActorForwardVector();
	}
	
	//ForwardActorData
	{
		FHitResult hitResult;
		FVector start = PlayerData.Location;
		FVector end = start + PlayerData.Forward * 1e+4f;

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(playerPawn);

		playerPawn->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParams);

		if (hitResult.bBlockingHit)
		{
			ForwardActorData.Name = hitResult.GetActor()->GetName();
			ForwardActorData.Location = hitResult.GetActor()->GetActorLocation();
			ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector();
		}
		else
		{
			ForwardActorData.Name = "No Traced Any Actor";
			ForwardActorData.Location = FVector::ZeroVector;
			ForwardActorData.Forward = FVector::ZeroVector;
		}
	}

	//DebuggerActorData;
	if (!!DebugActor)
	{
		DebuggerActorData.Name = DebugActor->GetName();
		DebuggerActorData.Location = DebugActor->GetActorLocation();
		DebuggerActorData.Forward = DebugActor->GetActorForwardVector();
	}
	else
	{
		DebuggerActorData.Name = "No Debug Actor";
		DebuggerActorData.Location = FVector::ZeroVector;
		DebuggerActorData.Forward = FVector::ZeroVector;
	}
}	

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

	if (TextureAsset == nullptr)
		TextureAsset = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Toy/T_Background.T_Background'")));

	FCanvasTileItem item(FVector2D::ZeroVector, TextureAsset->Resource, FVector2D(320, 220), FLinearColor(1.f, 1.f, 1.f, 0.75f));
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend;
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);

	CanvasContext.Printf(FColor::Green, L"  -----<Player>-----");
	CanvasContext.Printf(FColor::White, L"  Name : %s", *PlayerData.Name);
	CanvasContext.Printf(FColor::White, L"  Location : %s", *PlayerData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"  Forward : %s", *PlayerData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -----<Forward Actor>-----");
	CanvasContext.Printf(FColor::White, L"  Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"  Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"  Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L"  -----<Debugger Actor>-----");
	CanvasContext.Printf(FColor::White, L"  Name : %s", *DebuggerActorData.Name);
	CanvasContext.Printf(FColor::White, L"  Location : %s", *DebuggerActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"  Forward : %s", *DebuggerActorData.Forward.ToString());
}
