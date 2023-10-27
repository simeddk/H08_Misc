#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CObject.generated.h"

UCLASS()
class H08_MISC_API UCObject : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		FVector Location;
};
