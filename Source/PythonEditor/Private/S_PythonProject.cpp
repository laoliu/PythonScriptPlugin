// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "S_PythonProject.h"
#include "S_PythonScriptPlugin.h"


UPythonProject::UPythonProject(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	FString ProjectScriptsPath = FPaths::Combine(*FPaths::ProjectContentDir(), UTF8_TO_TCHAR("Scripts"));
	Path = ProjectScriptsPath;
	//FPythonPluginNew& PythonModule = FModuleManager::GetModuleChecked<FPythonPluginNew>("PythonPluginNew");
	//if(!PythonModule.ScriptsPaths.IsEmpty())
	//	Path = PythonModule.ScriptsPaths[0];
}
