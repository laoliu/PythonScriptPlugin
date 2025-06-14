#pragma once

#include "S_UnrealEnginePython.h"

#if WITH_EDITOR
#include "S_UEPySPanel.h"

#include "Editor/GraphEditor/Public/SNodePanel.h"

extern PyTypeObject ue_PySNodePanelType;

typedef struct {
    ue_PySPanel s_panel;
    /* Type-specific fields go here. */
} ue_PySNodePanel;


void ue_python_init_snode_panel(PyObject *);
#endif