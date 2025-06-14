// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreTypes.h"
#include "S_PythonScriptTypes.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

class IPythonScriptPlugin_S : public IModuleInterface
{
public:
	/** Get this module */
	static IPythonScriptPlugin_S* Get()
	{
		static const FName ModuleName = "PythonPluginNew";
		return FModuleManager::GetModulePtr<IPythonScriptPlugin_S>(ModuleName);
	}

	/**
	 * Check to see whether the plugin was built with Python support enabled.
	 */
	virtual bool IsPythonAvailable() const = 0;

	/**
	 * Execute the given Python command.
	 * This may be literal Python code, or a file (with optional arguments) that you want to run.
	 * @return true if the command ran successfully, false if there were errors (the output log will show the errors).
	 */
	virtual bool ExecPythonCommand(const TCHAR* InPythonCommand) = 0;

	/**
	 * Execute the given Python command.
	 * @return true if the command ran successfully, false if there were errors.
	 */
	virtual bool ExecPythonCommandEx(FPythonCommandEx_S& InOutPythonCommand) = 0;
	
	/**
	 * Get the path to the Python interpreter executable of the Python SDK this plugin was compiled against.
	 */
	virtual FString GetInterpreterExecutablePath() const = 0;

	/**
	 * Delegate called after Python has been initialized.
	 */
	virtual FSimpleMulticastDelegate& OnPythonInitialized() = 0;

	/**
	 * Delegate called before Python is shutdown.
	 */
	virtual FSimpleMulticastDelegate& OnPythonShutdown() = 0;
};
