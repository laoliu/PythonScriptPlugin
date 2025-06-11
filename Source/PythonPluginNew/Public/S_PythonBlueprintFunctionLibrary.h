#pragma once


#include "Kismet/BlueprintFunctionLibrary.h"
#include "S_UnrealEnginePython.h"
#include "S_PythonBlueprintFunctionLibrary.generated.h"


UCLASS()
class UPythonBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Exec, Category = "Python")
		static void ExecutePythonScript(FString script);

	UFUNCTION(BlueprintCallable, Exec, Category = "Python")
		static void ExecutePythonString(const FString& PythonCmd);
};

