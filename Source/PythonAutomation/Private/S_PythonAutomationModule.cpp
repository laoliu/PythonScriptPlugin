// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "S_PythonAutomationModule.h"
#include "S_UnrealEnginePython.h"
#include "S_UEPyFAutomationEditorCommonUtils.h"

IMPLEMENT_MODULE(FPythonAutomationModule, PythonAutomation);


void FPythonAutomationModule::StartupModule()
{
	FScopePythonGIL gil;
	PyObject *py_automation_module = PyImport_AddModule("unreal_engine.automation");
	ue_python_init_fautomation_editor_common_utils(py_automation_module);
}

void FPythonAutomationModule::ShutdownModule()
{

}
