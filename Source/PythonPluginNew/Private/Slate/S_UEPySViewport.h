#pragma once

#include "S_UEPySCompoundWidget.h"

#include "Runtime/Slate/Public/Widgets/SViewport.h"

extern PyTypeObject ue_PySViewportType;

typedef struct
{
	ue_PySCompoundWidget s_compound_widget;
	/* Type-specific fields go here. */
} ue_PySViewport;

void ue_python_init_sviewport(PyObject *);
