#pragma once

#include "S_UEPySCompoundWidget.h"

#if WITH_EDITOR
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 13)
#include "Developer/DesktopWidgets/Public/Widgets/Input/SFilePathPicker.h"

extern PyTypeObject ue_PySFilePathPickerType;

typedef struct
{
	ue_PySCompoundWidget s_compound_widget;
	/* Type-specific fields go here. */
} ue_PySFilePathPicker;

void ue_python_init_sfile_path_picker(PyObject *);
#endif
#endif