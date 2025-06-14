#pragma once

#include "S_UnrealEnginePython.h"


#include "S_UEPySPanel.h"

#include "Runtime/SlateCore/Public/Widgets/SOverlay.h"

extern PyTypeObject ue_PySOverlayType;

typedef struct {
	ue_PySPanel s_panel;
	/* Type-specific fields go here. */
} ue_PySOverlay;

void ue_python_init_soverlay(PyObject *);
