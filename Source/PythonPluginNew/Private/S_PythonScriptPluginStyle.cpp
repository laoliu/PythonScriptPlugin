// Copyright Epic Games, Inc. All Rights Reserved.

#include "S_PythonScriptPluginStyle.h"

#include "Styling/SlateTypes.h"
#include "Styling/CoreStyle.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyleMacros.h"

FName FPythonScriptPluginEditorStyle_S::StyleName("PythonScriptPluginEditorStyle");

FPythonScriptPluginEditorStyle_S::FPythonScriptPluginEditorStyle_S()
	: FSlateStyleSet(StyleName)
{
	const FVector2D IconSize(16.0f, 16.0f);

	SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("PythonPluginNew/Content"));
	SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	Set("Icons.PythonExecute", new IMAGE_BRUSH_SVG("PythonExecute", IconSize));
	Set("Icons.PythonRecent",  new IMAGE_BRUSH_SVG("PythonRecent", IconSize));

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FPythonScriptPluginEditorStyle_S::~FPythonScriptPluginEditorStyle_S()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}

FPythonScriptPluginEditorStyle_S& FPythonScriptPluginEditorStyle_S::Get()
{
	static FPythonScriptPluginEditorStyle_S Inst;
	return Inst;
}


