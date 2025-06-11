// Copyright Epic Games, Inc. All Rights Reserved.

#include "S_PythonOnlineDocsCommandlet.h"
#include "S_PyWrapperTypeRegistry.h"
#include "S_PyGenUtil.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(S_PythonOnlineDocsCommandlet)

DEFINE_LOG_CATEGORY_STATIC(LogPythonOnlineDocsCommandlet, Log, All);

UPythonOnlineDocsCommandlet_S::UPythonOnlineDocsCommandlet_S()
{
	IsServer = true;
	IsClient = true;
	IsEditor = true;
	LogToConsole = false;
	ShowErrorCount = false;
}

int32 UPythonOnlineDocsCommandlet_S::Main(const FString& Params)
{
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> ParamVals;
	UCommandlet::ParseCommandLine(*Params, Tokens, Switches, ParamVals);

#if WITH_PYTHON
	EPyOnlineDocsFilterFlags DocGenFlags = EPyOnlineDocsFilterFlags::IncludeNone;

	// Apply the filter flags from the command line
#define APPLY_FILTER_FLAG(NAME)							\
	if (Switches.Contains(TEXT(#NAME)))					\
	{													\
		DocGenFlags |= EPyOnlineDocsFilterFlags::NAME;	\
	}
	APPLY_FILTER_FLAG(IncludeEngine)
	APPLY_FILTER_FLAG(IncludeEnterprise)
	APPLY_FILTER_FLAG(IncludeInternal)
	APPLY_FILTER_FLAG(IncludeProject)
#undef APPLY_FILTER_FLAG

	// If we weren't given any filter flags, include everything
	if (DocGenFlags == EPyOnlineDocsFilterFlags::IncludeNone)
	{
		DocGenFlags = EPyOnlineDocsFilterFlags::IncludeAll;
	}

	// For the documentation, use the the light typing version, avoid listing all type coercions which make the API harder to read.
	PyGenUtil::SetTypeHintingMode(ETypeHintingMode_S::AutoCompletion);

	UE_LOG(LogPythonOnlineDocsCommandlet, Display, TEXT("\n\nGenerating Python documentation..."));
	FPyWrapperTypeRegistry::Get().GenerateStubCodeForWrappedTypes(DocGenFlags);

#else	// WITH_PYTHON
	
	UE_LOG(LogPythonOnlineDocsCommandlet, Error, TEXT("Python docs cannot be generated as the plugin was built as a stub!"));
	return -1;

#endif	// WITH_PYTHON

	return 0;
}

