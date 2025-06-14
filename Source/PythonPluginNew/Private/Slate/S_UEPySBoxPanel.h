#pragma once

#include "S_UnrealEnginePython.h"


#include "S_UEPySPanel.h"

#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"

extern PyTypeObject ue_PySBoxPanelType;

typedef struct {
	ue_PySPanel s_panel;
	/* Type-specific fields go here. */
} ue_PySBoxPanel;

void ue_python_init_sbox_panel(PyObject *);
