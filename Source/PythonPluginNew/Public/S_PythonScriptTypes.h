// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreTypes.h"
#include "Misc/EnumClassFlags.h"
#include "S_PythonScriptTypes.generated.h"

// Note: The types in this header are used by IPythonScriptPlugin, so MUST be inline as they CANNOT require linkage to use

UENUM()
enum class ETypeHintingMode_S : uint8
{
	/** Turn off type hinting. */
	Off,

	/**
	 * When generating the Python stub and to some extend the Docstrings, enables type hinting (PEP 484) to get the best experience
	 * with a Python IDE auto-completion. The hinting will list the exact input types, omit type coercions and will assume all reflected
	 * unreal.Object cannot be None which is not true, but will let the function signature easy to read.
	 */
	AutoCompletion,

	/**
	 * Enables type hinting for static type checking. Hint as close as possible the real supported types including
	 * possible type coercions. Because the UE reflection API doesn't provide all the required information, some tradeoffs
	 * are required that do not always reflect the reality. For example, reflected UObject will always be marked as
	 * 'possibly None'. While this is true in some contexts, it is not true all the time.
	 */
	TypeChecker,
};

/** Types of log output that Python can give. */
UENUM()
enum class EPythonLogOutputType_S : uint8
{
	/** This log was informative. */
	Info,
	/** This log was a warning. */
	Warning,
	/** This log was an error. */
	Error,
};

/** Flags that can be specified when running Python commands. */
UENUM()
enum class EPythonCommandFlags_S : uint8
{
	/** No special behavior. */
	None = 0,
	/** Run the Python command in "unattended" mode (GIsRunningUnattendedScript set to true), which will suppress certain pieces of UI. */
	Unattended = 1<<0,
};
ENUM_CLASS_FLAGS(EPythonCommandFlags_S);

/** Controls the execution mode used for the Python command. */
UENUM()
enum class EPythonCommandExecutionMode_S : uint8
{
	/** Execute the Python command as a file. This allows you to execute either a literal Python script containing multiple statements, or a file with optional arguments. */
	ExecuteFile,
	/** Execute the Python command as a single statement. This will execute a single statement and print the result. This mode cannot run files. */
	ExecuteStatement,
	/** Evaluate the Python command as a single statement. This will evaluate a single statement and return the result. This mode cannot run files. */
	EvaluateStatement,
};

/** Controls the scope used when executing Python files. */
UENUM()
enum class EPythonFileExecutionScope_S : uint8
{
	/** Execute the Python file with its own unique locals and globals dict to isolate any changes it makes to the environment (like imports). */
	Private,
	/** Execute the Python file with the shared locals and globals dict as used by the console, so that executing it behaves as if you'd ran the file contents directly in the console. */
	Public,
};

/** Log output entry captured from Python. */
USTRUCT(BlueprintType)
struct FPythonLogOutputEntry_S
{
	GENERATED_BODY()

	/** The type of the log output. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python|Output")
	EPythonLogOutputType_S Type = EPythonLogOutputType_S::Info;

	/** The log output string. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Python|Output")
	FString Output;
};

/** Extended information when executing Python commands. */
struct FPythonCommandEx_S
{
	/** Flags controlling how the command should be run. */
	EPythonCommandFlags_S Flags = EPythonCommandFlags_S::None;

	/** Controls the mode used to execute the command. */
	EPythonCommandExecutionMode_S ExecutionMode = EPythonCommandExecutionMode_S::ExecuteFile;

	/** Controls the scope used when executing Python files. */
	EPythonFileExecutionScope_S FileExecutionScope = EPythonFileExecutionScope_S::Private;

	/** The command to run. This may be literal Python code, or a file (with optional arguments) to run. */
	FString Command;

	/** The result of running the command. On success, for EvaluateStatement mode this will be the actual result of running the command, and will be None in all other cases. On failure, this will be the error information (typically a Python exception trace). */
	FString CommandResult;

	/** The log output captured while running the command. */
	TArray<FPythonLogOutputEntry_S> LogOutput;
};

inline const TCHAR* LexToString(EPythonLogOutputType_S InType)
{
	switch (InType)
	{
	case EPythonLogOutputType_S::Info:
		return TEXT("Info");
	case EPythonLogOutputType_S::Warning:
		return TEXT("Warning");
	case EPythonLogOutputType_S::Error:
		return TEXT("Error");
	default:
		break;
	}
	return TEXT("<Unknown EPythonLogOutputType>");
}

inline const TCHAR* LexToString(EPythonCommandExecutionMode_S InMode)
{
	switch (InMode)
	{
	case EPythonCommandExecutionMode_S::ExecuteFile:
		return TEXT("ExecuteFile");
	case EPythonCommandExecutionMode_S::ExecuteStatement:
		return TEXT("ExecuteStatement");
	case EPythonCommandExecutionMode_S::EvaluateStatement:
		return TEXT("EvaluateStatement");
	default:
		break;
	}
	return TEXT("<Unknown EPythonCommandExecutionMode>");
}

inline bool LexTryParseString(EPythonCommandExecutionMode_S& OutMode, const TCHAR* InBuffer)
{
	if (FCString::Stricmp(InBuffer, TEXT("ExecuteFile")) == 0)
	{
		OutMode = EPythonCommandExecutionMode_S::ExecuteFile;
		return true;
	}
	if (FCString::Stricmp(InBuffer, TEXT("ExecuteStatement")) == 0)
	{
		OutMode = EPythonCommandExecutionMode_S::ExecuteStatement;
		return true;
	}
	if (FCString::Stricmp(InBuffer, TEXT("EvaluateStatement")) == 0)
	{
		OutMode = EPythonCommandExecutionMode_S::EvaluateStatement;
		return true;
	}
	return false;
}

inline void LexFromString(EPythonCommandExecutionMode_S& OutMode, const TCHAR* InBuffer)
{
	OutMode = EPythonCommandExecutionMode_S::ExecuteFile;
	LexTryParseString(OutMode, InBuffer);
}
