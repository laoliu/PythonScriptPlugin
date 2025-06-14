#pragma once

#include "S_UEPySCompoundWidget.h"

#include "Runtime/Slate/Public/Widgets/Input/SVectorInputBox.h"

extern PyTypeObject ue_PySVectorInputBoxType;

typedef struct
{
	ue_PySCompoundWidget s_compound_widget;
	/* Type-specific fields go here. */
} ue_PySVectorInputBox;

void ue_python_init_svector_input_box(PyObject *);
