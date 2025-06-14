// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "S_IncludePython.h"
#include "S_IPythonScriptPlugin.h"
#include "S_PyUtil.h"
#include "S_PyPtr.h"
#include "Containers/Ticker.h"
#include "Misc/CoreMisc.h"
#include "HAL/IConsoleManager.h"
#include "Framework/Commands/InputChord.h"
#include "Kismet2/EnumEditorUtils.h"
#include "UObject/StrongObjectPtr.h"
//#include "S_PythonScriptPluginSettings.h"

class FPythonPluginNew;
class FPythonScriptRemoteExecution;
class FPackageReloadedEvent;
class UContentBrowserFileDataSource;
class UToolMenu;

struct FAssetData;

enum class EPackageReloadPhase : uint8;

#if WITH_PYTHON

/**
 * Executor for "Python" commands
 */
class FPythonCommandExecutor : public IConsoleCommandExecutor
{
public:
	FPythonCommandExecutor(IPythonScriptPlugin_S* InPythonScriptPlugin);

	static FName StaticName();
	virtual FName GetName() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetDescription() const override;
	virtual FText GetHintText() const override;
	virtual void GetSuggestedCompletions(const TCHAR* Input, TArray<FConsoleSuggestion>& Out) override;
	virtual void GetExecHistory(TArray<FString>& Out) override;
	virtual bool Exec(const TCHAR* Input) override;
	virtual bool AllowHotKeyClose() const override;
	virtual bool AllowMultiLine() const override;
	virtual FInputChord GetHotKey() const override;
	virtual FInputChord GetIterateExecutorHotKey() const override;

private:
	IPythonScriptPlugin_S* PythonScriptPlugin;
};

/**
 * Executor for "Python (REPL)" commands
 */
class FPythonREPLCommandExecutor : public IConsoleCommandExecutor
{
public:
	FPythonREPLCommandExecutor(IPythonScriptPlugin_S* InPythonScriptPlugin);

	static FName StaticName();
	virtual FName GetName() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetDescription() const override;
	virtual FText GetHintText() const override;
	virtual void GetSuggestedCompletions(const TCHAR* Input, TArray<FConsoleSuggestion>& Out) override;
	virtual void GetExecHistory(TArray<FString>& Out) override;
	virtual bool Exec(const TCHAR* Input) override;
	virtual bool AllowHotKeyClose() const override;
	virtual bool AllowMultiLine() const override;
	virtual FInputChord GetHotKey() const override;
	virtual FInputChord GetIterateExecutorHotKey() const override;

private:
	IPythonScriptPlugin_S* PythonScriptPlugin;
};

/**
 *
 */
struct IPythonCommandMenu
{
	virtual ~IPythonCommandMenu() {}

	virtual void OnStartupMenu() = 0;
	virtual void OnShutdownMenu() = 0;

	virtual void OnRunFile(const FString& InFile, bool bAdd) = 0;
};
#endif	// WITH_PYTHON

class FPythonPluginNew 
	: public IPythonScriptPlugin_S
	, public FSelfRegisteringExec
	, public FEnumEditorUtils::INotifyOnEnumChanged
{
public:
	FPythonPluginNew();

	/** Get this module */
	static FPythonPluginNew* Get()
	{
		return static_cast<FPythonPluginNew*>(IPythonScriptPlugin_S::Get());
	}

	//~ IPythonScriptPlugin interface
	virtual bool IsPythonAvailable() const override;
	virtual bool ExecPythonCommand(const TCHAR* InPythonCommand) override;
	virtual bool ExecPythonCommandEx(FPythonCommandEx_S& InOutPythonCommand) override;
	virtual FString GetInterpreterExecutablePath() const override;
	virtual FSimpleMulticastDelegate& OnPythonInitialized() override;
	virtual FSimpleMulticastDelegate& OnPythonShutdown() override;

	//~ IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//~ FEnumEditorUtils::INotifyOnEnumChanged interface
	virtual void PreChange(const UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;
	virtual void PostChange(const UUserDefinedEnum* Enum, FEnumEditorUtils::EEnumEditorChangeInfo Info) override;

#if WITH_PYTHON
	void RunStartupScripts();

	void OnPostEngineInit();

	/** Sync the remote execution environment to the current settings, starting or stopping it as required */
	void SyncRemoteExecutionToSettings();

	/** 
	 * Import the given module into the "unreal" package.
	 * This function will take the given name and attempt to import either "unreal_{name}" or "_unreal_{name}" into the "unreal" package as "unreal.{name}".
	 */
	void ImportUnrealModule(const TCHAR* InModuleName);

	/** Evaluate/Execute a Python string, and return the result */
	PyObject* EvalString(const TCHAR* InStr, const TCHAR* InContext, const int InMode);
	PyObject* EvalString(const TCHAR* InStr, const TCHAR* InContext, const int InMode, PyObject* InGlobalDict, PyObject* InLocalDict);

	/** Run literal Python script */
	bool RunString(FPythonCommandEx_S& InOutPythonCommand);

	/** Run a Python file */
	bool RunFile(const TCHAR* InFile, const TCHAR* InArgs, FPythonCommandEx_S& InOutPythonCommand);

	PyObject* GetDefaultGlobalDict() { return PyDefaultGlobalDict.Get(); }
	PyObject* GetDefaultLocalDict()  { return PyDefaultLocalDict.Get();  }
	PyObject* GetConsoleGlobalDict() { return PyConsoleGlobalDict.Get(); }
	PyObject* GetConsoleLocalDict()  { return PyConsoleLocalDict.Get();  }
#endif	// WITH_PYTHON

	TArray<FString> ScriptsPaths;
protected:
	//~ FSelfRegisteringExec interface
	virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

private:
#if WITH_PYTHON
	void InitializePython();

	void ShutdownPython();

	void InitPipInstaller();

	void RunPipInstaller();

	void RequestStubCodeGeneration();

	void GenerateStubCode();

	void Tick(const float InDeltaTime);

	void OnModuleDirtied(FName InModuleName);

	void OnModulesChanged(FName InModuleName, EModuleChangeReason InModuleChangeReason);

	void OnContentPathMounted(const FString& InAssetPath, const FString& InFilesystemPath);

	void OnContentPathDismounted(const FString& InAssetPath, const FString& InFilesystemPath);

	static void RegisterModulePaths(const FString& InFilesystemPath);

	static void UnregisterModulePaths(const FString& InFilesystemPath);

	static bool IsDeveloperModeEnabled();

	static ETypeHintingMode_S GetTypeHintingMode();

	void OnAssetRenamed(const FAssetData& Data, const FString& OldName);

	void OnAssetRemoved(const FAssetData& Data);

	void OnAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);

	void OnAssetUpdated(const UObject* InObj);

#if WITH_EDITOR
	void OnPrepareToCleanseEditorObject(UObject* InObject);

	void PopulatePythonFileContextMenu(UToolMenu* InMenu);

	TStrongObjectPtr<UContentBrowserFileDataSource> PythonFileDataSource;

	void LoadSharedDSO(const FString& PythonDSOWildcard, const FString& PythonDir);
	void LoadPythonLibraries();
	void UnloadPythonLibraries();
#endif	// WITH_EDITOR

	TUniquePtr<FPythonScriptRemoteExecution> RemoteExecution;
	FPythonCommandExecutor CmdExec;
	FPythonREPLCommandExecutor CmdREPLExec;
	IPythonCommandMenu* CmdMenu;
	FTSTicker::FDelegateHandle TickHandle;
	FTSTicker::FDelegateHandle ModuleDelayedHandle;

	PyUtil::FPyApiBuffer PyProgramName;
	PyUtil::FPyApiBuffer PyHomePath;
	FPyObjectPtr PyDefaultGlobalDict;
	FPyObjectPtr PyDefaultLocalDict;
	FPyObjectPtr PyConsoleGlobalDict;
	FPyObjectPtr PyConsoleLocalDict;
	FPyObjectPtr PyUnrealModule;
	PyThreadState* PyMainThreadState = nullptr;
	bool bInitialized;
	bool bRanStartupScripts;

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 11
	PyConfig ModulePyConfig;
	static PyUtil::FPyApiBuffer Utf8String;
#endif // 3.11 upgrade
#endif	// WITH_PYTHON

	FSimpleMulticastDelegate OnPythonInitializedDelegate;
	FSimpleMulticastDelegate OnPythonShutdownDelegate;
	TArray<void*> DLLHandles;
};
