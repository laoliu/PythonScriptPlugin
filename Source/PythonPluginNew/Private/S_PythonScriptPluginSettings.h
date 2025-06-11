// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/DeveloperSettings.h"
#include "S_PythonScriptTypes.h"
#include "S_PythonScriptPluginSettings.generated.h"
/**
 * Configure the Python plug-in.
 */
UCLASS(config=Engine, defaultconfig)
class UPythonScriptPluginSettings_S : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPythonScriptPluginSettings_S();

#if WITH_EDITOR
	//~ UObject interface
	virtual bool CanEditChange(const FProperty* InProperty) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;
#endif

	/** Array of Python scripts to run at start-up (run before the first Tick after the Engine has initialized). */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, MultiLine=true))
	TArray<FString> StartupScripts;

	/** Array of additional paths to add to the Python system paths. */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, RelativePath))
	TArray<FDirectoryPath> AdditionalPaths;

	/**
	 * Should the embedded interpreter be run in isolation mode. In isolation, the standard PYTHON* environment variables (PYTHONPATH,
	 * PYTHONHOME, etc), the script's directory and the user's site-packages directory are ignored by the interpreter. This
	 * prevents incompabible software to crash the engine. Consider turning this option off if you tightly control your Python
	 * environment and you are sure everything is compatible. Note that the UE_PYTHONPATH environment variable is added to 'sys.path'
	 * whether the interpreter runs in insolation mode or not.
	 */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))
	bool bIsolateInterpreterEnvironment = true;

	/**
	 * Should Developer Mode be enabled on the Python interpreter *for all users of the project*
	 * Note: Most of the time you want to enable bDeveloperMode in the Editor Preferences instead!
	 *
	 * (will also enable extra warnings (e.g., for deprecated code), and enable stub code generation for
	 * use with external IDEs).
	 */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true, DisplayName="Developer Mode (all users)"), AdvancedDisplay)
	bool bDeveloperMode;

	/**
	 * Should the pip install task be run on editor startup.
	 *
	 * NOTE: The project pip install directory: <ProjectDir>/Intermediate/PipInstall/Lib/site-packages
	 *       will still be added to site package path, if it exists, to allow for pre-populated installs
	 *       even auto-running UBT PipInstall is disabled.
	 *
	 *       See <ProjectDir>/Intermediate/PipInstall/merged_requirements.in for listing of required packages.
	 */
	UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, meta=(ConfigRestartRequired=true))
	bool bRunPipInstallOnStartup = true;

	/** Require pip to use strict hash checking for all packages
	 *  WARNING: Disabling this setting is a security risk, particularly when combined with IndexUrl override
	*/
	UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))
	bool bPipStrictHashCheck = true;

	/** Only run pip to generate merged requiremnts and/or validate requested packages are installed */
	UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))
	bool bOfflineOnly = false;

	/** Override all index/extra-index URLs, this is useful for internal NAT installs (using e.g. devpi or similar index cache)
	 *  WARNING: Strict hash checks should be enabled if an override index url is used
	*/
	UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))
	FString OverrideIndexURL;
	
	/** Additional arguments passed to main pip install call, useful to add e.g. --cert or other proxy options for restrictive firewalls
	* 	NOTE: Do not use this to add --index-url or --extra-index-url, instead use OverrideIndexURL setting or ExtraIndexUrls uplugin property, respectively
	*/
	UPROPERTY(config, EditAnywhere, Category=PythonPipInstall, AdvancedDisplay, meta=(ConfigRestartRequired=true))
	FString ExtraInstallArgs;

	/** Should remote Python execution be enabled? */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, meta=(DisplayName="Enable Remote Execution?"))
	bool bRemoteExecution;

	/** The multicast group endpoint (in the form of IP_ADDRESS:PORT_NUMBER) that the UDP multicast socket should join */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Group Endpoint"))
	FString RemoteExecutionMulticastGroupEndpoint;

	/** The adapter address that the UDP multicast socket should bind to, or 0.0.0.0 to bind to all adapters */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Bind Address"))
	FString RemoteExecutionMulticastBindAddress;

	/** Size of the send buffer for the remote endpoint connection */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Send Buffer Size", Units="Bytes"))
	int32 RemoteExecutionSendBufferSizeBytes;

	/** Size of the receive buffer for the remote endpoint connection */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Receive Buffer Size", Units="Bytes"))
	int32 RemoteExecutionReceiveBufferSizeBytes;

	/** The TTL that the UDP multicast socket should use (0 is limited to the local host, 1 is limited to the local subnet) */
	UPROPERTY(config, EditAnywhere, Category=PythonRemoteExecution, AdvancedDisplay, meta=(DisplayName="Multicast Time-To-Live"))
	uint8 RemoteExecutionMulticastTtl;
};


UCLASS(config=EditorPerProjectUserSettings)
class UPythonScriptPluginUserSettings_S : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPythonScriptPluginUserSettings_S();

#if WITH_EDITOR
	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;
#endif

	/**
	 * Should Developer Mode be enabled on the Python interpreter?
	 *
	 * (will also enable extra warnings (e.g., for deprecated code), and enable stub code generation for
	 * use with external IDEs).
	 */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))
	bool bDeveloperMode;

	/**
	 * Should the generated Python stub and API documentation have type hints. This enables standard Python type hinting (PEP 484) for the classes,
	 * structs, methods, properties, constants, etc. exposed by the engine. If the developer mode is enabled and the Python IDE configured to use
	 * the generated Python stub, types will be displayed in auto-completion popup and used by the IDE static type checkers. This has no effects on
	 * the execution of the code. (Requires Python >= 3.7)
	 */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))
	ETypeHintingMode_S TypeHintingMode = ETypeHintingMode_S::AutoCompletion;

	/** Should Python scripts be available in the Content Browser? */
	UPROPERTY(config, EditAnywhere, Category=Python, meta=(ConfigRestartRequired=true))
	bool bEnableContentBrowserIntegration;
};
