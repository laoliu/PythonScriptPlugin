#pragma once

#include "S_UnrealEnginePython.h"


#include "S_UEPySLeafWidget.h"

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 21)
#include "Runtime/SlateCore/Public/Widgets/Images/SImage.h"
#else
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#endif
#include "Runtime/SlateCore/Public/Styling/SlateBrush.h"

extern PyTypeObject ue_PySImageType;

typedef struct {
	ue_PySLeafWidget s_leaf_widget;
	/* Type-specific fields go here. */
	FSlateBrush brush;
} ue_PySImage;

void ue_python_init_simage(PyObject *);
