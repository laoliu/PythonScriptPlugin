// Copyright Epic Games, Inc. All Rights Reserved.

#include "S_PyTest.h"
#include "S_PyUtil.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(S_PyTest)

FPyTestStruct_S::FPyTestStruct_S()
{
	Bool = false;
	Int = 0;
	Float = 0.0f;
	Enum = S_EPyTestEnum::One;
	LegacyInt_DEPRECATED = 0;
	BoolInstanceOnly = false;
	BoolDefaultsOnly = false;
}

bool UPyTestStructLibrary_S::IsBoolSet(const FPyTestStruct_S& InStruct)
{
	return InStruct.Bool;
}

bool UPyTestStructLibrary_S::LegacyIsBoolSet(const FPyTestStruct_S& InStruct)
{
	return IsBoolSet(InStruct);
}

int32 UPyTestStructLibrary_S::GetConstantValue()
{
	return 10;
}

FPyTestStruct_S UPyTestStructLibrary_S::AddInt(const FPyTestStruct_S& InStruct, const int32 InValue)
{
	FPyTestStruct_S Result = InStruct;
	Result.Int += InValue;
	return Result;
}

FPyTestStruct_S UPyTestStructLibrary_S::AddFloat(const FPyTestStruct_S& InStruct, const float InValue)
{
	FPyTestStruct_S Result = InStruct;
	Result.Float += InValue;
	return Result;
}

FPyTestStruct_S UPyTestStructLibrary_S::AddStr(const FPyTestStruct_S& InStruct, const FString& InValue)
{
	FPyTestStruct_S Result = InStruct;
	Result.String += InValue;
	return Result;
}

void UPyTestStructLibrary_S::SetBoolMutable(const FPyTestStruct_S& InStruct)
{
	InStruct.BoolMutable = true;
}

void UPyTestStructLibrary_S::ClearBoolMutable(const FPyTestStruct_S& InStruct)
{
	InStruct.BoolMutable = false;
}

void UPyTestStructLibrary_S::SetBoolMutableViaRef(FPyTestStruct_S& InStruct)
{
	InStruct.BoolMutable = true;
}

void UPyTestStructLibrary_S::ClearBoolMutableViaRef(FPyTestStruct_S& InStruct)
{
	InStruct.BoolMutable = false;
}

UPyTestInterface_S::UPyTestInterface_S(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPyTestChildInterface_S::UPyTestChildInterface_S(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPyTestOtherInterface_S::UPyTestOtherInterface_S(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UPyTestObject_S::UPyTestObject_S()
{
	StructArray.AddDefaulted();
	StructArray.AddDefaulted();
}

int32 UPyTestObject_S::FuncBlueprintNative_Implementation(const int32 InValue) const
{
	return InValue;
}

void UPyTestObject_S::FuncBlueprintNativeRef_Implementation(FPyTestStruct_S& InOutStruct) const
{
}

int32 UPyTestObject_S::CallFuncBlueprintImplementable(const int32 InValue) const
{
	return FuncBlueprintImplementable(InValue);
}

bool UPyTestObject_S::CallFuncBlueprintImplementablePackedGetter(int32& OutValue) const
{
	return FuncBlueprintImplementablePackedGetter(OutValue);
}

int32 UPyTestObject_S::CallFuncBlueprintNative(const int32 InValue) const
{
	return FuncBlueprintNative(InValue);
}

void UPyTestObject_S::CallFuncBlueprintNativeRef(FPyTestStruct_S& InOutStruct) const
{
	return FuncBlueprintNativeRef(InOutStruct);
}

void UPyTestObject_S::FuncTakingPyTestStruct(const FPyTestStruct_S& InStruct) const
{
}

void UPyTestObject_S::FuncTakingPyTestChildStruct(const FPyTestChildStruct_S& InStruct) const
{
}

void UPyTestObject_S::LegacyFuncTakingPyTestStruct(const FPyTestStruct_S& InStruct) const
{
	FuncTakingPyTestStruct(InStruct);
}

void UPyTestObject_S::FuncTakingPyTestStructDefault(const FPyTestStruct_S& InStruct)
{
}

int32 UPyTestObject_S::FuncTakingPyTestDelegate(const FPyTestDelegate& InDelegate, const int32 InValue) const
{
	return InDelegate.IsBound() ? InDelegate.Execute(InValue) : INDEX_NONE;
}

void UPyTestObject_S::FuncTakingFieldPath(const TFieldPath<FProperty>& InFieldPath)
{
	FieldPath = InFieldPath;
}

int32 UPyTestObject_S::DelegatePropertyCallback(const int32 InValue) const
{
	if (InValue != Int)
	{
		UE_LOG(LogPython, Error, TEXT("Given value (%d) did not match the Int property value (%d)"), InValue, Int);
	}

	return InValue;
}

void UPyTestObject_S::MulticastDelegatePropertyCallback(FString InStr) const
{
	if (InStr != String)
	{
		UE_LOG(LogPython, Error, TEXT("Given value (%s) did not match the String property value (%s)"), *InStr, *String);
	}
}

TArray<int32> UPyTestObject_S::ReturnArray()
{
	TArray<int32> TmpArray;
	TmpArray.Add(10);
	return TmpArray;
}

TSet<int32> UPyTestObject_S::ReturnSet()
{
	TSet<int32> TmpSet;
	TmpSet.Add(10);
	return TmpSet;
}

TMap<int32, bool> UPyTestObject_S::ReturnMap()
{
	TMap<int32, bool> TmpMap;
	TmpMap.Add(10, true);
	return TmpMap;
}

TFieldPath<FProperty> UPyTestObject_S::ReturnFieldPath()
{
	return TFieldPath<FProperty>(UPyTestObject_S::StaticClass()->FindPropertyByName(TEXT("FieldPath")));
}

void UPyTestObject_S::EmitScriptError()
{
	FFrame::KismetExecutionMessage(TEXT("EmitScriptError was called"), ELogVerbosity::Error);
}

void UPyTestObject_S::EmitScriptWarning()
{
	FFrame::KismetExecutionMessage(TEXT("EmitScriptWarning was called"), ELogVerbosity::Warning);
}

int32 UPyTestObject_S::GetConstantValue()
{
	return 10;
}

int32 UPyTestObject_S::FuncInterface(const int32 InValue) const
{
	return InValue;
}

int32 UPyTestObject_S::FuncInterfaceChild(const int32 InValue) const
{
	return InValue;
}

int32 UPyTestObject_S::FuncInterfaceOther(const int32 InValue) const
{
	return InValue;
}

bool UPyTestObjectLibrary_S::IsBoolSet(const UPyTestObject_S* InObj)
{
	return InObj->Bool;
}

int32 UPyTestObjectLibrary_S::GetOtherConstantValue()
{
	return 20;
}


FString UPyTestTypeHint_S::GetStringConst()
{
	return FString("Foo");
}

int32 UPyTestTypeHint_S::GetIntConst()
{
	return 777;
}


UPyTestTypeHint_S::UPyTestTypeHint_S()
{
	ObjectProp = NewObject<UPyTestObject_S>();
}

UPyTestTypeHint_S::UPyTestTypeHint_S(bool bParam1, int32 Param2, float Param3, const FString& Param4, const FText& Param5)
	: BoolProp(bParam1)
	, IntProp(Param2)
	, FloatProp(Param3)
	, StringProp(Param4)
	, TextProp(Param5)
{
}

bool UPyTestTypeHint_S::CheckBoolTypeHints(bool bParam1, bool bParam2, bool bParam3)
{
	return true;
}

int32 UPyTestTypeHint_S::CheckIntegerTypeHints(uint8 Param1, int32 Param2, int64 Param3)
{
	return 0;
}

double UPyTestTypeHint_S::CheckFloatTypeHints(float Param1, double Param2, float Param3, double Param4)
{
	return 0.0;
}

S_EPyTestEnum UPyTestTypeHint_S::CheckEnumTypeHints(S_EPyTestEnum Param1, S_EPyTestEnum Param2)
{
	return S_EPyTestEnum::One;
}

FString UPyTestTypeHint_S::CheckStringTypeHints(const FString& Param1, const FString& Param2)
{
	return FString();
}

FName UPyTestTypeHint_S::CheckNameTypeHints(const FName& Param1, const FName& Param2)
{
	return FName();
}

FText UPyTestTypeHint_S::CheckTextTypeHints(const FText& Param1, const FText& Param2)
{
	return FText::GetEmpty();
}

TFieldPath<FProperty> UPyTestTypeHint_S::CheckFieldPathTypeHints(const TFieldPath<FProperty> Param1)
{
	return TFieldPath<FProperty>();
}

FPyTestStruct_S UPyTestTypeHint_S::CheckStructTypeHints(const FPyTestStruct_S& Param1, const FPyTestStruct_S& Param2)
{
	return FPyTestStruct_S();
}

UPyTestObject_S* UPyTestTypeHint_S::CheckObjectTypeHints(const UPyTestObject_S* Param1, const UPyTestObject_S* Param3)
{
	return nullptr;
}

TArray<FText> UPyTestTypeHint_S::CheckArrayTypeHints(const TArray<FString>& Param1, const TArray<FName>& Param2, const TArray<FText>& Param3, const TArray<UObject*>& Param4)
{
	return TArray<FText>();
}

TSet<FName> UPyTestTypeHint_S::CheckSetTypeHints(const TSet<FString>& Param1, const TSet<FName>& Param2, const TSet<UObject*>& Param4)
{
	return TSet<FName>();
}

TMap<FString, UObject*> UPyTestTypeHint_S::CheckMapTypeHints(const TMap<int, FString>& Param1, const TMap<int, FName>& Param2, const TMap<int, FText>& Param3, const TMap<int, UObject*>& Param4)
{
	return TMap<FString, UObject*>();
}

FPyTestDelegate& UPyTestTypeHint_S::CheckDelegateTypeHints(const FPyTestDelegate& Param1)
{
	return DelegateProp;
}

bool UPyTestTypeHint_S::CheckStaticFunction(bool Param1, int32 Param2, double Param3, const FString& Param4)
{
	return true;
}

int UPyTestTypeHint_S::CheckTupleReturnType(UPARAM(ref) FString& InOutString)
{
	InOutString = TEXT("Foo");
	return 0;
}


