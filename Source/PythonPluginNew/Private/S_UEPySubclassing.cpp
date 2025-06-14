
#include "S_UEPyModule.h"
#include "S_PythonClass.h"
#include "UObject/S_UEPyObject.h"

//#include "Runtime/CoreUObject/Public/UObject/Field.h"

// hack for avoiding loops in class constructors (thanks to the Unreal.js project for the idea)
UClass *ue_py_class_constructor_placeholder = nullptr;
static void UEPyClassConstructor(UClass *u_class, const FObjectInitializer &ObjectInitializer)
{
	if (UPythonClass *u_py_class_casted = Cast<UPythonClass>(u_class))
	{
		ue_py_class_constructor_placeholder = u_class;
	}
	u_class->ClassConstructor(ObjectInitializer);
	ue_py_class_constructor_placeholder = nullptr;
}

int unreal_engine_py_init(ue_PyUObject *self, PyObject *args, PyObject *kwds)
{
	EXTRA_UE_LOG(LogPython, Warning, TEXT("unreal_engine_py_init (uobject) - subclassing args %d"), PyTuple_Size(args));

	// is it subclassing ?
	if (PyTuple_Size(args) == 3)
	{
		// TODO make it smarter on error checking
		UE_LOG(LogPython, Warning, TEXT("%s"), UTF8_TO_TCHAR(UEPyUnicode_AsUTF8(PyObject_Str(PyTuple_GetItem(args, 0)))));
		UE_LOG(LogPython, Warning, TEXT("%s"), UTF8_TO_TCHAR(UEPyUnicode_AsUTF8(PyObject_Str(PyTuple_GetItem(args, 1)))));
		UE_LOG(LogPython, Warning, TEXT("%s"), UTF8_TO_TCHAR(UEPyUnicode_AsUTF8(PyObject_Str(PyTuple_GetItem(args, 2)))));

		PyObject *parents = PyTuple_GetItem(args, 1);
		ue_PyUObject *parent = (ue_PyUObject *)PyTuple_GetItem(parents, 0);

		PyObject *class_attributes = PyTuple_GetItem(args, 2);

		PyObject *class_name = PyDict_GetItemString(class_attributes, (char *)"__qualname__");
		const char *name = UEPyUnicode_AsUTF8(class_name);
		// check if parent is a uclass
		UClass *new_class = unreal_engine_new_uclass((char *)name, (UClass *)parent->ue_object);
		if (!new_class)
			return -1;

		// map the class to the python object
		self->ue_object = new_class;
		self->py_proxy = nullptr;
		self->auto_rooted = 0;
		self->py_dict = PyDict_New();

		FUnrealEnginePythonHouseKeeper::Get()->RegisterPyUObject(new_class, self);

		PyObject *py_additional_properties = PyDict_New();

		PyObject *class_attributes_keys = PyObject_GetIter(class_attributes);
		for (;;)
		{
			PyObject *key = PyIter_Next(class_attributes_keys);
			if (!key)
			{
				if (PyErr_Occurred())
					return -1;
				break;
			}
			if (!PyUnicodeOrString_Check(key))
				continue;
			const char *class_key = UEPyUnicode_AsUTF8(key);

			PyObject *value = PyDict_GetItem(class_attributes, key);

			if (strlen(class_key) > 2 && class_key[0] == '_' && class_key[1] == '_')
			{
				continue;
			}

			//EXTRA_UE_LOG(LogPython, Warning, TEXT("object init attr value %p"), value);

			bool prop_added = false;


			//EXTRA_UE_LOG(LogPython, Warning, TEXT("offset tp_alloc %d %x"), offsetof(PyTypeObject, tp_alloc), offsetof(PyTypeObject, tp_alloc));

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
			if (FProperty *f_property = new_class->FindPropertyByName(FName(UTF8_TO_TCHAR(class_key))))
			{
				UE_LOG(LogPython, Warning, TEXT("Found FProperty %s"), UTF8_TO_TCHAR(class_key));
				PyDict_SetItem(py_additional_properties, key, value);
				prop_added = true;
			}
#else
			if (UProperty *u_property = new_class->FindPropertyByName(FName(UTF8_TO_TCHAR(class_key))))
			{
				UE_LOG(LogPython, Warning, TEXT("Found UProperty %s"), UTF8_TO_TCHAR(class_key));
				PyDict_SetItem(py_additional_properties, key, value);
				prop_added = true;
			}
#endif
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
			// add simple property
			// this is confusing because it appears when properties were uobjects UEP allowed both general
			// uobject classes and UProperty classes as arguments - creating a UOBjectProperty/UScriptStructProperty for a non-UProperty class
			// this now has to be separate code
			else if (ue_is_pyfproperty(value))
			{
				// So I dont think an FProperty is valid as an argument here - we need a class object
				// which for FProperties is now an FFieldClass
				// we could of course take the class of the FProperty and add a new property
				//ue_PyFProperty *py_obj = (ue_PyFProperty *)value;
				UE_LOG(LogPython, Error, TEXT("fproperty not valid as property argument %s"), UTF8_TO_TCHAR(class_key));
				return -1;
			}
			else if (ue_is_pyffieldclass(value))
			{
				//ue_PyFFieldClass *py_obj = (ue_PyFFieldClass *)value;
				//UE_LOG(LogPython, Error, TEXT("simple property NEEDS FIXING %s"), UTF8_TO_TCHAR(class_key));
				//return -1;
				// so I think we just add the property here now - in old terms we essentially know 
				// this is a UClass of a UProperty subclass - ie an FFieldClass
				// think we should disallow a plain FFieldClass - we need a subclass
				ue_PyFFieldClass *py_obj = (ue_PyFFieldClass *)value;
				//if (FFieldClass::IsChildOf(py_obj->ue_ffieldclass))
				//{
					if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
					{
						unreal_engine_py_log_error();
						return -1;
					}
					prop_added = true;
				//}
			}
			// allow for adding UObject/UScriptStruct properties by simply specifying the UObject/UScriptStruct class here
			// this appears to be what the UProperty code did
			else if (ue_is_pyuobject(value))
			{
				ue_PyUObject *py_obj = (ue_PyUObject *)value;
				if (py_obj->ue_object->IsA<UClass>())
				{
					UClass *p_class = (UClass *)py_obj->ue_object;
					// So apparently this wont work - UProperty subclasses seems to be mapped to FFieldClass automagically
					//if (p_class->IsChildOf<UProperty>())
					//{
						// we may be able to leave this in as it appears we still have access to UProperty subclasses
						// for the moment error out here
						//if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
						//{
						//	unreal_engine_py_log_error();
						//	return -1;
						//}
						//prop_added = true;
						//UE_LOG(LogPython, Error, TEXT("uproperty as property implementation disabled "));
						//return -1;
					//}
					//else
					{
						if (!py_ue_add_property(self, Py_BuildValue("(OsO)", (PyObject *)ue_get_python_ffieldclass(FObjectProperty::StaticClass()), class_key, value)))
						{
							unreal_engine_py_log_error();
							return -1;
						}
						prop_added = true;
					}
				}
				else if (py_obj->ue_object->IsA<UScriptStruct>())
				{
					if (!py_ue_add_property(self, Py_BuildValue("(OsO)", (PyObject *)ue_get_python_ffieldclass(FStructProperty::StaticClass()), class_key, value)))
					{
						unreal_engine_py_log_error();
						return -1;
					}
					prop_added = true;
				}
			}
#else
			// add simple property
			else if (ue_is_pyuobject(value))
			{
				ue_PyUObject *py_obj = (ue_PyUObject *)value;
				if (py_obj->ue_object->IsA<UClass>())
				{
					UClass *p_class = (UClass *)py_obj->ue_object;
					if (p_class->IsChildOf<UProperty>())
					{
						if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
						{
							unreal_engine_py_log_error();
							return -1;
						}
						prop_added = true;
					}
					else
					{
						if (!py_ue_add_property(self, Py_BuildValue("(OsO)", (PyObject *)ue_get_python_uobject(UObjectProperty::StaticClass()), class_key, value)))
						{
							unreal_engine_py_log_error();
							return -1;
						}
						prop_added = true;
					}
				}
				else if (py_obj->ue_object->IsA<UScriptStruct>())
				{
					if (!py_ue_add_property(self, Py_BuildValue("(OsO)", (PyObject *)ue_get_python_uobject(UStructProperty::StaticClass()), class_key, value)))
					{
						unreal_engine_py_log_error();
						return -1;
					}
					prop_added = true;
				}
			}
#endif

			// add array property
			else if (PyList_Check(value))
			{
				if (PyList_Size(value) == 1)
				{
					PyObject *first_item = PyList_GetItem(value, 0);
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
					// pigs - we need same code as above - allow for direct FFieldClass plus UObject/UScriptStruct classes
					if (ue_is_pyfproperty(first_item))
					{
						// So I dont think an FProperty is valid as an argument here - we need a class object
						// which for FProperties is now an FFieldClass
						// we could of course take the class of the FProperty and add a new property
						//ue_PyFProperty *py_obj = (ue_PyFProperty *)first_item;
						UE_LOG(LogPython, Error, TEXT("fproperty not valid as property argument %s"), UTF8_TO_TCHAR(class_key));
						return -1;
					}
					else if (ue_is_pyffieldclass(first_item))
					{
						//ue_PyFFieldClass *py_obj = (ue_PyFFieldClass *)value;
						//UE_LOG(LogPython, Error, TEXT("simple property NEEDS FIXING %s"), UTF8_TO_TCHAR(class_key));
						//return -1;
						// so I think we just add the property here now - in old terms we essentially know 
						// this is a UClass of a UProperty subclass - ie an FFieldClass
						// think we should disallow a plain FFieldClass - we need a subclass
						ue_PyFFieldClass *py_obj = (ue_PyFFieldClass *)first_item;
						//if (py_obj->ue_ffieldclass->IsChildOf(FFieldClass::StaticClass()))
						//{
							if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
							{
								unreal_engine_py_log_error();
								return -1;
							}
							prop_added = true;
						//}
					}
					else if (ue_is_pyuobject(first_item))
					{
						ue_PyUObject *py_obj = (ue_PyUObject *)first_item;
						if (py_obj->ue_object->IsA<UClass>())
						{
							UClass *p_class = (UClass *)py_obj->ue_object;
							// So apparently this wont work - UProperty subclasses seems to be mapped to FFieldClass automagically
							//if (p_class->IsChildOf<UProperty>())
							//{
								// we may be able to leave this in as it appears we still have access to UProperty subclasses
								// for the moment error out here
								//if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
								//{
								//	unreal_engine_py_log_error();
								//	return -1;
								//}
								//prop_added = true;
								//UE_LOG(LogPython, Error, TEXT("uproperty as property array implementation disabled "));
								//return -1;
							//}
							//else
							{
								if (!py_ue_add_property(self, Py_BuildValue("([O]sO)", (PyObject *)ue_get_python_ffieldclass(FObjectProperty::StaticClass()), class_key, first_item)))
								{
									unreal_engine_py_log_error();
									return -1;
								}
								prop_added = true;
							}
						}
						else if (py_obj->ue_object->IsA<UScriptStruct>())
						{
							if (!py_ue_add_property(self, Py_BuildValue("([O]sO)", (PyObject *)ue_get_python_ffieldclass(FStructProperty::StaticClass()), class_key, first_item)))
							{
								unreal_engine_py_log_error();
								return -1;
							}
							prop_added = true;
						}
					}
#else
					if (ue_is_pyuobject(first_item))
					{
						ue_PyUObject *py_obj = (ue_PyUObject *)first_item;
						if (py_obj->ue_object->IsA<UClass>())
						{
							UClass *p_class = (UClass *)py_obj->ue_object;
							if (p_class->IsChildOf<UProperty>())
							{
								if (!py_ue_add_property(self, Py_BuildValue("(Os)", value, class_key)))
								{
									unreal_engine_py_log_error();
									return -1;
								}
								prop_added = true;
							}

							else
							{
								if (!py_ue_add_property(self, Py_BuildValue("([O]sO)", (PyObject *)ue_get_python_uobject(UObjectProperty::StaticClass()), class_key, first_item)))
								{
									unreal_engine_py_log_error();
									return -1;
								}
								prop_added = true;
							}
						}
						else if (py_obj->ue_object->IsA<UScriptStruct>())
						{
							if (!py_ue_add_property(self, Py_BuildValue("([O]sO)", (PyObject *)ue_get_python_uobject(UStructProperty::StaticClass()), class_key, first_item)))
							{
								unreal_engine_py_log_error();
								return -1;
							}
							prop_added = true;
						}
					}
#endif

				}
			}
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 15)
			else if (PyDict_Check(value))
			{
				if (PyDict_Size(value) == 1)
				{
					PyObject *py_key = nullptr;
					PyObject *py_value = nullptr;
					Py_ssize_t pos = 0;
					PyDict_Next(value, &pos, &py_key, &py_value);
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
					if (ue_is_pyfproperty(py_key) || ue_is_pyfproperty(py_value))
					{
						// So I dont think an FProperty is valid as an argument here - we need a class object
						// which for FProperties is now an FFieldClass
						// we could of course take the class of the FProperty and add a new property
						//ue_PyFProperty *py_obj = (ue_PyFProperty *)first_item;
						UE_LOG(LogPython, Error, TEXT("fproperty not valid as property argument %s"), UTF8_TO_TCHAR(class_key));
						return -1;
					}
					else
					{
						PyObject *first_item = nullptr;
						PyObject *second_item = nullptr;

						if (ue_is_pyffieldclass(py_key))
						{
							ue_PyFFieldClass *py_obj = (ue_PyFFieldClass *)py_key;
							//if (py_obj->ue_ffieldclass->IsChildOf(FFieldClass::StaticClass()))
							//{
								first_item = py_key;
							//}
						}
						else if (ue_is_pyuobject(py_key))
						{
							ue_PyUObject *py_obj = (ue_PyUObject *)py_key;
							if (py_obj->ue_object->IsA<UClass>())
							{
								UClass *p_class = (UClass *)py_obj->ue_object;
								// So apparently this wont work - UProperty subclasses seems to be mapped to FFieldClass automagically
								//if (p_class->IsChildOf<UProperty>())
								//{
									// we may be able to leave this in as it appears we still have access to UProperty subclasses
									// for the moment error out here
									//first_item = py_key;
									//UE_LOG(LogPython, Error, TEXT("uproperty as property map key implementation disabled "));
									//return -1;
								//}
								//else
								{
									first_item = (PyObject *)ue_get_python_ffieldclass(FObjectProperty::StaticClass());
								}
							}
							else if (py_obj->ue_object->IsA<UScriptStruct>())
							{
								first_item = (PyObject *)ue_get_python_ffieldclass(FStructProperty::StaticClass());
							}
						}

						if (ue_is_pyffieldclass(py_value))
						{
							ue_PyFFieldClass *py_obj2 = (ue_PyFFieldClass *)py_key;
							//if (py_obj2->ue_ffieldclass->IsChildOf(FFieldClass::StaticClass()))
							//{
								second_item = py_value;
							//}
						}
						else if (ue_is_pyuobject(py_value))
						{
							ue_PyUObject *py_obj2 = (ue_PyUObject *)py_value;

							if (py_obj2->ue_object->IsA<UClass>())
							{
								UClass *p_class = (UClass *)py_obj2->ue_object;
								// So apparently this wont work - UProperty subclasses seems to be mapped to FFieldClass automagically
								//if (p_class->IsChildOf<UProperty>())
								//{
									// we may be able to leave this in as it appears we still have access to UProperty subclasses
									// for the moment error out here
									//second_item = py_value;
									//UE_LOG(LogPython, Error, TEXT("uproperty as property map value implementation disabled "));
									//return -1;
								//}
								//else
								{
									second_item = (PyObject *)ue_get_python_ffieldclass(FObjectProperty::StaticClass());
								}
							}
							else if (py_obj2->ue_object->IsA<UScriptStruct>())
							{
								second_item = (PyObject *)ue_get_python_ffieldclass(FStructProperty::StaticClass());
							}
						}

						if (first_item && second_item)
						{
							if (!py_ue_add_property(self, Py_BuildValue("([OO]sOO)", first_item, second_item, class_key, py_key, py_value)))
							{
								unreal_engine_py_log_error();
								return -1;
							}
							prop_added = true;
						}
					}
#else
					if (ue_is_pyuobject(py_key) && ue_is_pyuobject(py_value))
					{
						PyObject *first_item = nullptr;
						PyObject *second_item = nullptr;

						ue_PyUObject *py_obj = (ue_PyUObject *)py_key;
						if (py_obj->ue_object->IsA<UClass>())
						{
							UClass *p_class = (UClass *)py_obj->ue_object;
							if (p_class->IsChildOf<UProperty>())
							{
								first_item = py_key;
							}
							else
							{
								first_item = (PyObject *)ue_get_python_uobject(UObjectProperty::StaticClass());
							}
						}
						else if (py_obj->ue_object->IsA<UScriptStruct>())
						{
							first_item = (PyObject *)ue_get_python_uobject(UStructProperty::StaticClass());
						}

						ue_PyUObject *py_obj2 = (ue_PyUObject *)py_value;
						if (py_obj2->ue_object->IsA<UClass>())
						{
							UClass *p_class = (UClass *)py_obj2->ue_object;
							if (p_class->IsChildOf<UProperty>())
							{
								second_item = py_value;
							}
							else
							{
								second_item = (PyObject *)ue_get_python_uobject(UObjectProperty::StaticClass());
							}
						}
						else if (py_obj2->ue_object->IsA<UScriptStruct>())
						{
							second_item = (PyObject *)ue_get_python_uobject(UStructProperty::StaticClass());
						}

						if (!py_ue_add_property(self, Py_BuildValue("([OO]sOO)", first_item, second_item, class_key, py_key, py_value)))
						{
							unreal_engine_py_log_error();
							return -1;
						}
						prop_added = true;
					}
#endif
				}
			}

#endif
			// function ?
			else if (PyCallable_Check(value) && class_key[0] >= 'A' && class_key[0] <= 'Z')
			{
				uint32 func_flags = FUNC_Native | FUNC_BlueprintCallable | FUNC_Public;
				PyObject *is_event = PyObject_GetAttrString(value, (char *)"event");
				if (is_event && PyObject_IsTrue(is_event))
				{
					func_flags |= FUNC_Event | FUNC_BlueprintEvent;
				}
				else if (!is_event)
					PyErr_Clear();

				PyObject *is_multicast = PyObject_GetAttrString(value, (char *)"multicast");
				if (is_multicast && PyObject_IsTrue(is_multicast))
				{
					func_flags |= FUNC_NetMulticast;
				}
				else if (!is_multicast)
					PyErr_Clear();
				PyObject *is_server = PyObject_GetAttrString(value, (char *)"server");
				if (is_server && PyObject_IsTrue(is_server))
				{
					func_flags |= FUNC_NetServer;
				}
				else if (!is_server)
					PyErr_Clear();
				PyObject *is_client = PyObject_GetAttrString(value, (char *)"client");
				if (is_client && PyObject_IsTrue(is_client))
				{
					func_flags |= FUNC_NetClient;
				}
				else if (!is_client)
					PyErr_Clear();
				PyObject *is_reliable = PyObject_GetAttrString(value, (char *)"reliable");
				if (is_reliable && PyObject_IsTrue(is_reliable))
				{
					func_flags |= FUNC_NetReliable;
				}
				else if (!is_reliable)
					PyErr_Clear();


				PyObject *is_pure = PyObject_GetAttrString(value, (char *)"pure");
				if (is_pure && PyObject_IsTrue(is_pure))
				{
					func_flags |= FUNC_BlueprintPure;
				}
				else if (!is_pure)
					PyErr_Clear();
				PyObject *is_static = PyObject_GetAttrString(value, (char *)"static");
				if (is_static && PyObject_IsTrue(is_static))
				{
					func_flags |= FUNC_Static;
				}
				else if (!is_static)
					PyErr_Clear();
				PyObject *override_name = PyObject_GetAttrString(value, (char *)"override");
				if (override_name && PyUnicodeOrString_Check(override_name))
				{
					class_key = UEPyUnicode_AsUTF8(override_name);
				}
				else if (override_name && PyUnicodeOrString_Check(override_name))
				{
					class_key = UEPyUnicode_AsUTF8(override_name);
				}
				else if (!override_name)
					PyErr_Clear();
				if (!unreal_engine_add_function(new_class, (char *)class_key, value, func_flags))
				{
					UE_LOG(LogPython, Error, TEXT("unable to add function %s"), UTF8_TO_TCHAR(class_key));
					return -1;
				}
				prop_added = true;
			}


			if (!prop_added)
			{
				UE_LOG(LogPython, Warning, TEXT("Adding %s as attr"), UTF8_TO_TCHAR(class_key));
				PyObject_SetAttr((PyObject *)self, key, value);
			}
		}

		if (PyDict_Size(py_additional_properties) > 0)
		{
			PyObject_SetAttrString((PyObject *)self, (char*)"__additional_uproperties__", py_additional_properties);
		}

		UPythonClass *new_u_py_class = (UPythonClass *)new_class;
		// TODO: check if we can use this to decref the ue_PyUbject mapped to the class
		new_u_py_class->py_uobject = self;
		new_u_py_class->ClassConstructor = [](const FObjectInitializer &ObjectInitializer)
		{
			FScopePythonGIL gil;
			UClass *u_class = ue_py_class_constructor_placeholder ? ue_py_class_constructor_placeholder : ObjectInitializer.GetClass();
			ue_py_class_constructor_placeholder = nullptr;

			UEPyClassConstructor(u_class->GetSuperClass(), ObjectInitializer);

			if (UPythonClass *u_py_class_casted = Cast<UPythonClass>(u_class))
			{
				ue_PyUObject *new_self = ue_get_python_uobject(ObjectInitializer.GetObj());
				if (!new_self)
				{
					unreal_engine_py_log_error();
					return;
				}

				// fill __dict__ from class
				if (u_py_class_casted->py_uobject && u_py_class_casted->py_uobject->py_dict)
				{
					PyObject *found_additional_props = PyDict_GetItemString(u_py_class_casted->py_uobject->py_dict, (char *)"__additional_uproperties__");
					// manage UProperties (and automatically maps multicast properties)
					if (found_additional_props)
					{
						PyObject *keys = PyDict_Keys(found_additional_props);
						Py_ssize_t items_len = PyList_Size(keys);
						for (Py_ssize_t i = 0; i < items_len; i++)
						{
							PyObject *mc_key = PyList_GetItem(keys, i);
							PyObject *mc_value = PyDict_GetItem(found_additional_props, mc_key);

							const char *mc_name = UEPyUnicode_AsUTF8(mc_key);
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
							FProperty *f_property = ObjectInitializer.GetObj()->GetClass()->FindPropertyByName(FName(UTF8_TO_TCHAR(mc_name)));
							if (f_property)
							{
								if (auto casted_prop = CastField<FMulticastDelegateProperty>(f_property))
								{
#else
							UProperty *u_property = ObjectInitializer.GetObj()->GetClass()->FindPropertyByName(FName(UTF8_TO_TCHAR(mc_name)));
							if (u_property)
							{
								if (auto casted_prop = Cast<UMulticastDelegateProperty>(u_property))
								{
#endif
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 23)
									FMulticastScriptDelegate multiscript_delegate = *casted_prop->GetMulticastDelegate(ObjectInitializer.GetObj());
#else
									
									FMulticastScriptDelegate multiscript_delegate = casted_prop->GetPropertyValue_InContainer(ObjectInitializer.GetObj());
#endif

									FScriptDelegate script_delegate;
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)
									// can we reuse UPythonDelegate here??
									UPythonDelegate *py_delegate = FUnrealEnginePythonHouseKeeper::Get()->NewDelegate(ObjectInitializer.GetObj(), mc_value, casted_prop->SignatureFunction);
#else
									UPythonDelegate *py_delegate = FUnrealEnginePythonHouseKeeper::Get()->NewDelegate(ObjectInitializer.GetObj(), mc_value, casted_prop->SignatureFunction);
#endif
									// fake UFUNCTION for bypassing checks
									script_delegate.BindUFunction(py_delegate, FName("PyFakeCallable"));

									// add the new delegate
									multiscript_delegate.Add(script_delegate);

									// re-assign multicast delegate
#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 23)
									casted_prop->SetMulticastDelegate(ObjectInitializer.GetObj(), multiscript_delegate);
#else
									casted_prop->SetPropertyValue_InContainer(ObjectInitializer.GetObj(), multiscript_delegate);
#endif
								}
								else
								{
									PyObject_SetAttr((PyObject *)new_self, mc_key, mc_value);
								}
							}

						}
						Py_DECREF(keys);
					}
					else
					{
						PyErr_Clear();
					}
					PyObject *keys = PyDict_Keys(u_py_class_casted->py_uobject->py_dict);
					Py_ssize_t keys_len = PyList_Size(keys);
					for (Py_ssize_t i = 0; i < keys_len; i++)
					{
						PyObject *key = PyList_GetItem(keys, i);
						PyObject *value = PyDict_GetItem(u_py_class_casted->py_uobject->py_dict, key);
						if (PyUnicodeOrString_Check(key))
						{
							const char *key_name = UEPyUnicode_AsUTF8(key);
							if (!strcmp(key_name, (char *)"__additional_uproperties__"))
								continue;
						}
						// special case to bound function to method
						if (PyFunction_Check(value))
						{
							PyObject *bound_function = PyObject_CallMethod(value, (char*)"__get__", (char*)"O", (PyObject *)new_self);
							if (bound_function)
							{
								PyObject_SetAttr((PyObject *)new_self, key, bound_function);
								Py_DECREF(bound_function);
							}
							else
							{
								unreal_engine_py_log_error();
							}
						}
						else
						{
							PyObject_SetAttr((PyObject *)new_self, key, value);
						}
					}
					Py_DECREF(keys);
				}
				// call __init__
				u_py_class_casted->CallPyConstructor(new_self);
			}
		};



		if (self->py_dict)
		{
			ue_PyUObject *new_default_self = ue_get_python_uobject(new_u_py_class->ClassDefaultObject);

			if (!new_default_self)
			{
				unreal_engine_py_log_error();
				UE_LOG(LogPython, Error, TEXT("unable to set dict on new ClassDefaultObject"));
				return -1;
			}
			PyObject *keys = PyDict_Keys(self->py_dict);

			Py_ssize_t keys_len = PyList_Size(keys);
			for (Py_ssize_t i = 0; i < keys_len; i++)
			{
				PyObject *key = PyList_GetItem(keys, i);
				PyObject *value = PyDict_GetItem(self->py_dict, key);
				// special case to bound function to method
				if (PyFunction_Check(value))
				{
					PyObject *bound_function = PyObject_CallMethod(value, (char*)"__get__", (char*)"O", (PyObject *)new_default_self);
					if (bound_function)
					{
						PyObject_SetAttr((PyObject *)new_default_self, key, bound_function);
						Py_DECREF(bound_function);
					}
					else
					{
						unreal_engine_py_log_error();
					}
				}
				else
				{
					PyObject_SetAttr((PyObject *)new_default_self, key, value);
				}
			}
			Py_DECREF(keys);
		}

		// add default uproperties values
		if (py_additional_properties)
		{
			ue_PyUObject *new_default_self = ue_get_python_uobject(new_u_py_class->ClassDefaultObject);
			if (!new_default_self)
			{
				unreal_engine_py_log_error();
				UE_LOG(LogPython, Error, TEXT("unable to set properties on new ClassDefaultObject"));
				return -1;
			}
			PyObject *keys = PyDict_Keys(py_additional_properties);
			Py_ssize_t keys_len = PyList_Size(keys);
			for (Py_ssize_t i = 0; i < keys_len; i++)
			{
				PyObject *key = PyList_GetItem(keys, i);
				PyObject *value = PyDict_GetItem(py_additional_properties, key);

				PyObject_SetAttr((PyObject *)new_default_self, key, value);
			}
			Py_DECREF(keys);
		}

		// add custom constructor (__init__)
		PyObject *py_init = PyDict_GetItemString(class_attributes, (char *)"__init__");
		if (py_init && PyCallable_Check(py_init))
		{
			// fake initializer
#if ENGINE_MAJOR_VERSION == 5
			FObjectInitializer initializer(new_u_py_class->ClassDefaultObject, nullptr,
			                               EObjectInitializerOptions::None |
			                               EObjectInitializerOptions::InitializeProperties, nullptr);
#else
			FObjectInitializer initializer(new_u_py_class->ClassDefaultObject, nullptr, false, true);
#endif
			new_u_py_class->SetPyConstructor(py_init);
			ue_PyUObject *new_default_self = ue_get_python_uobject(new_u_py_class->ClassDefaultObject);

			if (!new_default_self)
			{
				unreal_engine_py_log_error();
				UE_LOG(LogPython, Error, TEXT("unable to call __init__ on new ClassDefaultObject"));
				return -1;
			}

			new_u_py_class->CallPyConstructor(new_default_self);
		}

	}

	return 0;
}


#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 25)


int unreal_engine_py_fproperty_init(ue_PyUObject *self, PyObject *args, PyObject *kwds)
{
	UE_LOG(LogPython, Warning, TEXT("__init__ called (tp_init) for FProperty"));
	return -1;
}

int unreal_engine_py_ffieldclass_init(ue_PyUObject *self, PyObject *args, PyObject *kwds)
{
	UE_LOG(LogPython, Warning, TEXT("__init__ called (tp_init) for FFieldClass"));
	return -1;
}

#endif
