#pragma once

#include "S_UEPySCompoundWidget.h"

#if WITH_EDITOR
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 13)

#include "Developer/DesktopWidgets/Public/Widgets/Input/SDirectoryPicker.h"

extern PyTypeObject ue_PySDirectoryPickerType;

typedef struct
{
	ue_PySCompoundWidget s_compound_widget;
	/* Type-specific fields go here. */
} ue_PySDirectoryPicker;

void ue_python_init_sdirectory_picker(PyObject *);
#endif
#endif