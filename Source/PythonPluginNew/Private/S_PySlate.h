// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "S_IncludePython.h"
#include "S_PyPtr.h"
#include "CoreMinimal.h"

#if WITH_PYTHON

namespace PySlate
{
	void InitializeModule();
	void ShutdownModule();
}

#endif	// WITH_PYTHON
