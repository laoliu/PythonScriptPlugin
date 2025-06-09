// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PyWrapperStruct.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PYTHONSCRIPTPLUGIN_PyWrapperStruct_generated_h
#error "PyWrapperStruct.generated.h already included, missing '#pragma once' in PyWrapperStruct.h"
#endif
#define PYTHONSCRIPTPLUGIN_PyWrapperStruct_generated_h

#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_377_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPythonGeneratedStruct(); \
	friend struct Z_Construct_UClass_UPythonGeneratedStruct_Statics; \
public: \
	DECLARE_CLASS(UPythonGeneratedStruct, UScriptStruct, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/PythonScriptPlugin"), NO_API) \
	DECLARE_SERIALIZER(UPythonGeneratedStruct) \
	virtual UObject* _getUObject() const override { return const_cast<UPythonGeneratedStruct*>(this); }


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_377_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPythonGeneratedStruct(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPythonGeneratedStruct(UPythonGeneratedStruct&&); \
	UPythonGeneratedStruct(const UPythonGeneratedStruct&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPythonGeneratedStruct); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPythonGeneratedStruct); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPythonGeneratedStruct) \
	NO_API virtual ~UPythonGeneratedStruct();


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_374_PROLOG
#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_377_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_377_INCLASS_NO_PURE_DECLS \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h_377_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PYTHONSCRIPTPLUGIN_API UClass* StaticClass<class UPythonGeneratedStruct>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperStruct_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
