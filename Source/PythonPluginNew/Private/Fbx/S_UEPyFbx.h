#pragma once

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 12)
#include "S_UEPyModule.h"

#if WITH_EDITOR

#include "S_UEPyFbxManager.h"
#include "S_UEPyFbxIOSettings.h"
#include "S_UEPyFbxImporter.h"
#include "S_UEPyFbxScene.h"
#include "S_UEPyFbxNode.h"
#include "S_UEPyFbxObject.h"
#include "S_UEPyFbxProperty.h"
#include "S_UEPyFbxPose.h"
#include "S_UEPyFbxMesh.h"

void ue_python_init_fbx(PyObject *);

#endif
#endif
