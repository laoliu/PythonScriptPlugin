// Copyright Epic Games, Inc. All Rights Reserved.

#include "S_EditorPythonScriptingLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(S_EditorPythonScriptingLibrary)

#define LOCTEXT_NAMESPACE "EditorPythonScriptingLibrary"

bool UEditorPythonScriptingLibrary_S::bKeepPythonScriptAlive = false;


void UEditorPythonScriptingLibrary_S::SetKeepPythonScriptAlive(const bool bNewKeepAlive)
{
	bKeepPythonScriptAlive = bNewKeepAlive;
}

bool UEditorPythonScriptingLibrary_S::GetKeepPythonScriptAlive()
{
	return bKeepPythonScriptAlive;
}


#undef LOCTEXT_NAMESPACE // "EditorPythonScriptingLibrary"
