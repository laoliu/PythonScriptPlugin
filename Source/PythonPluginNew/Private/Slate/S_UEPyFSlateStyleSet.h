#pragma once

#include "S_UEPySlate.h"
#include "Wrappers/S_UEPyFColor.h"
#include "Wrappers/S_UEPyFLinearColor.h"

typedef struct
{
	PyObject_HEAD
		/* Type-specific fields go here. */
		FSlateStyleSet *style_set;
} ue_PyFSlateStyleSet;

ue_PyFSlateStyleSet* py_ue_new_fslate_style_set(FSlateStyleSet* styleSet);

void ue_python_init_fslate_style_set(PyObject *);
