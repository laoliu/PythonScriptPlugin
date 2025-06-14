#pragma once
#include "S_UEPyModule.h"

#if WITH_EDITOR
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 12)

#if PLATFORM_LINUX
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wnull-dereference"
#endif
#endif

#include <fbxsdk.h>

struct ue_PyFbxMesh
{
	PyObject_HEAD
		/* Type-specific fields go here. */
		FbxMesh *fbx_mesh;
};


void ue_python_init_fbx_mesh(PyObject *);

PyObject *py_ue_new_fbx_mesh(FbxMesh *);

#endif
#endif
