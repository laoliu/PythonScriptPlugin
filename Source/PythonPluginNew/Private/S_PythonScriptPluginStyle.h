// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

/**
 * Slate style set that defines the styles for Python UI in the Editor 
 */
class FPythonScriptPluginEditorStyle_S
	: public FSlateStyleSet
{
public:
	static FName StyleName;

	/** Access the singleton instance for this style set */
	static FPythonScriptPluginEditorStyle_S& Get();

private:

	FPythonScriptPluginEditorStyle_S();
	~FPythonScriptPluginEditorStyle_S();
};
