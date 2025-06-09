// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PythonScriptPluginSettings.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PYTHONSCRIPTPLUGIN_PythonScriptPluginSettings_generated_h
#error "PythonScriptPluginSettings.generated.h already included, missing '#pragma once' in PythonScriptPluginSettings.h"
#endif
#define PYTHONSCRIPTPLUGIN_PythonScriptPluginSettings_generated_h

#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_38_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPythonScriptPluginSettings(); \
	friend struct Z_Construct_UClass_UPythonScriptPluginSettings_Statics; \
public: \
	DECLARE_CLASS(UPythonScriptPluginSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/PythonScriptPlugin"), NO_API) \
	DECLARE_SERIALIZER(UPythonScriptPluginSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Engine");} \



#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_38_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPythonScriptPluginSettings(UPythonScriptPluginSettings&&); \
	UPythonScriptPluginSettings(const UPythonScriptPluginSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPythonScriptPluginSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPythonScriptPluginSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPythonScriptPluginSettings) \
	NO_API virtual ~UPythonScriptPluginSettings();


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_35_PROLOG
#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_38_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_38_INCLASS_NO_PURE_DECLS \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_38_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PYTHONSCRIPTPLUGIN_API UClass* StaticClass<class UPythonScriptPluginSettings>();

#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_143_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPythonScriptPluginUserSettings(); \
	friend struct Z_Construct_UClass_UPythonScriptPluginUserSettings_Statics; \
public: \
	DECLARE_CLASS(UPythonScriptPluginUserSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/PythonScriptPlugin"), NO_API) \
	DECLARE_SERIALIZER(UPythonScriptPluginUserSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("EditorPerProjectUserSettings");} \



#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_143_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPythonScriptPluginUserSettings(UPythonScriptPluginUserSettings&&); \
	UPythonScriptPluginUserSettings(const UPythonScriptPluginUserSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPythonScriptPluginUserSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPythonScriptPluginUserSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPythonScriptPluginUserSettings) \
	NO_API virtual ~UPythonScriptPluginUserSettings();


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_140_PROLOG
#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_143_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_143_INCLASS_NO_PURE_DECLS \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h_143_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PYTHONSCRIPTPLUGIN_API UClass* StaticClass<class UPythonScriptPluginUserSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PythonScriptPluginSettings_h


#define FOREACH_ENUM_ETYPEHINTINGMODE(op) \
	op(ETypeHintingMode::Off) \
	op(ETypeHintingMode::AutoCompletion) \
	op(ETypeHintingMode::TypeChecker) 

enum class ETypeHintingMode : uint8;
template<> struct TIsUEnumClass<ETypeHintingMode> { enum { Value = true }; };
template<> PYTHONSCRIPTPLUGIN_API UEnum* StaticEnum<ETypeHintingMode>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
