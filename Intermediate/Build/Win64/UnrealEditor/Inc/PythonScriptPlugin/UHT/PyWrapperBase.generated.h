// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PyWrapperBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PYTHONSCRIPTPLUGIN_PyWrapperBase_generated_h
#error "PyWrapperBase.generated.h already included, missing '#pragma once' in PyWrapperBase.h"
#endif
#define PYTHONSCRIPTPLUGIN_PyWrapperBase_generated_h

#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	PYTHONSCRIPTPLUGIN_API UPythonResourceOwner(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPythonResourceOwner) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(PYTHONSCRIPTPLUGIN_API, UPythonResourceOwner); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPythonResourceOwner); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPythonResourceOwner(UPythonResourceOwner&&); \
	UPythonResourceOwner(const UPythonResourceOwner&); \
public: \
	PYTHONSCRIPTPLUGIN_API virtual ~UPythonResourceOwner();


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUPythonResourceOwner(); \
	friend struct Z_Construct_UClass_UPythonResourceOwner_Statics; \
public: \
	DECLARE_CLASS(UPythonResourceOwner, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/PythonScriptPlugin"), PYTHONSCRIPTPLUGIN_API) \
	DECLARE_SERIALIZER(UPythonResourceOwner)


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_GENERATED_UINTERFACE_BODY() \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_INCLASS_IINTERFACE \
protected: \
	virtual ~IPythonResourceOwner() {} \
public: \
	typedef UPythonResourceOwner UClassType; \
	typedef IPythonResourceOwner ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_96_PROLOG
#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_104_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_99_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PYTHONSCRIPTPLUGIN_API UClass* StaticClass<class UPythonResourceOwner>();

#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_133_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPythonObjectHandle(); \
	friend struct Z_Construct_UClass_UPythonObjectHandle_Statics; \
public: \
	DECLARE_CLASS(UPythonObjectHandle, UObject, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/PythonScriptPlugin"), NO_API) \
	DECLARE_SERIALIZER(UPythonObjectHandle) \
	virtual UObject* _getUObject() const override { return const_cast<UPythonObjectHandle*>(this); }


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_133_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPythonObjectHandle(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UPythonObjectHandle(UPythonObjectHandle&&); \
	UPythonObjectHandle(const UPythonObjectHandle&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPythonObjectHandle); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPythonObjectHandle); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPythonObjectHandle) \
	NO_API virtual ~UPythonObjectHandle();


#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_130_PROLOG
#define FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_133_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_133_INCLASS_NO_PURE_DECLS \
	FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h_133_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PYTHONSCRIPTPLUGIN_API UClass* StaticClass<class UPythonObjectHandle>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Engine_Plugins_Experimental_PythonScriptPlugin_Source_PythonScriptPlugin_Private_PyWrapperBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
