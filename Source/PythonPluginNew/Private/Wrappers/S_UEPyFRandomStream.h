#pragma once



#include "S_UEPyModule.h"

typedef struct
{
	PyObject_HEAD
		/* Type-specific fields go here. */
		FRandomStream rstream;
} ue_PyFRandomStream;

void ue_python_init_frandomstream(PyObject *);