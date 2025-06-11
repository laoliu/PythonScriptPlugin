#pragma once

#include "Commandlets/Commandlet.h"
#include "S_PyCommandlet.generated.h"

UCLASS()
class UPyCommandlet : public UCommandlet
{
	GENERATED_UCLASS_BODY()
	virtual int32 Main(const FString& Params) override;
};
