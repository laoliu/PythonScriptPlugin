// Copyright Epic Games, Inc. All Rights Reserved.

#include "S_PythonScriptPluginSettings.h"
#include "S_PythonScriptPlugin.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(S_PythonScriptPluginSettings)

#define LOCTEXT_NAMESPACE "PythonPluginNew"

UPythonScriptPluginSettings_S::UPythonScriptPluginSettings_S()
{
	CategoryName = TEXT("Plugins");
	SectionName  = TEXT("Python");

	RemoteExecutionMulticastGroupEndpoint = TEXT("239.0.0.1:6766");
	RemoteExecutionMulticastBindAddress = TEXT("127.0.0.1");
	RemoteExecutionSendBufferSizeBytes = 2 * 1024 * 1024;
	RemoteExecutionReceiveBufferSizeBytes = 2 * 1024 * 1024;
	RemoteExecutionMulticastTtl = 0;
}

#if WITH_EDITOR

bool UPythonScriptPluginSettings_S::CanEditChange(const FProperty* InProperty) const
{
	bool bCanEditChange = Super::CanEditChange(InProperty);

	if (bCanEditChange && InProperty)
	{
		if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastGroupEndpoint) ||
			InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastBindAddress) ||
			InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionSendBufferSizeBytes) || 
			InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionReceiveBufferSizeBytes) ||
			InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastTtl)
			)
		{
			bCanEditChange &= bRemoteExecution;
		}
	}

	return bCanEditChange;
}

void UPythonScriptPluginSettings_S::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

#if WITH_PYTHON
	if (PropertyChangedEvent.MemberProperty)
	{
		if (PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, bRemoteExecution) ||
			PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastGroupEndpoint) ||
			PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastBindAddress) ||
			PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionSendBufferSizeBytes) ||
			PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionReceiveBufferSizeBytes) ||
			PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UPythonScriptPluginSettings_S, RemoteExecutionMulticastTtl)
			)
		{
			FPythonPluginNew::Get()->SyncRemoteExecutionToSettings();
		}
	}
#endif	// WITH_PYTHON
}

FText UPythonScriptPluginSettings_S::GetSectionText() const
{
	return LOCTEXT("SettingsDisplayName", "Python");
}

#endif	// WITH_EDITOR

UPythonScriptPluginUserSettings_S::UPythonScriptPluginUserSettings_S()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("Python");
}

#if WITH_EDITOR
FText UPythonScriptPluginUserSettings_S::GetSectionText() const
{
	return LOCTEXT("UserSettingsDisplayName", "Python");
}

#endif	// WITH_EDITOR

#undef LOCTEXT_NAMESPACE


