// Copyright Kite & Lightning

#pragma once

#include "UObject/Class.h"
#include "S_UnrealEnginePython.h"
#include "Components/NativeWidgetHost.h"
#include "S_PyNativeWidgetHost.generated.h"



USTRUCT(BlueprintType)
struct FPythonSWidgetWrapper
{
	GENERATED_USTRUCT_BODY()

		TSharedPtr<SWidget> Widget;
};

template<>
struct TStructOpsTypeTraits<FPythonSWidgetWrapper> : public TStructOpsTypeTraitsBase2<FPythonSWidgetWrapper>
{
	enum
	{
		WithCopy = true,
	};
};

/**
 *
 */
UCLASS()
class UPyNativeWidgetHost : public UNativeWidgetHost
{
	GENERATED_BODY()


		UPyNativeWidgetHost(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

};

