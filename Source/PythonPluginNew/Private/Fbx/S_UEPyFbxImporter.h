#pragma once
#include "S_UEPyModule.h"

#if WITH_EDITOR

#if PLATFORM_LINUX
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wnull-dereference"
#pragma clang diagnostic warning "-Wshadow"
#endif
#endif

#include <fbxsdk.h>

struct ue_PyFbxImporter
{
	PyObject_HEAD
		/* Type-specific fields go here. */
		FbxImporter *fbx_importer;
};


void ue_python_init_fbx_importer(PyObject *);

#endif
