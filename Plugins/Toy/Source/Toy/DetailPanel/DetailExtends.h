#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FDetailExtends : public IDetailCustomization
{
public:
	static TSharedRef<class IDetailCustomization> MakeInstance();

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};
