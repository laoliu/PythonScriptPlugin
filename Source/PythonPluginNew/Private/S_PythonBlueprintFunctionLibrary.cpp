

#include "S_PythonBlueprintFunctionLibrary.h"
#include "S_PythonScriptPlugin.h"

void UPythonBlueprintFunctionLibrary::ExecutePythonScript(FString script)
{
	FPythonPluginNew& PythonModule = FModuleManager::GetModuleChecked<FPythonPluginNew>("PythonScriptPlugin");
	FPythonCommandEx PythonCommand;
	PythonCommand.Command = *script;
	TCHAR* args = UTF8_TO_TCHAR("UPythonBlueprintFunctionLibrary");
	PythonModule.RunFile(*script, args, PythonCommand);
}

void UPythonBlueprintFunctionLibrary::ExecutePythonString(const FString& PythonCmd)
{
	FPythonPluginNew& PythonModule = FModuleManager::GetModuleChecked<FPythonPluginNew>("PythonScriptPlugin");	
	FPythonCommandEx PythonCommand;
	PythonCommand.Command = *PythonCmd;
	TCHAR* args = UTF8_TO_TCHAR("UPythonBlueprintFunctionLibrary");
	PythonModule.RunFile(*PythonCmd, args, PythonCommand);
}
