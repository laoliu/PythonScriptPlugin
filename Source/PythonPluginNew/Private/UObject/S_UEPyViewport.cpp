#include "S_UEPyViewport.h"

#if WITH_EDITOR
#include "LevelEditor.h"
#if ENGINE_MAJOR_VERSION == 4
#include "Editor/LevelEditor/Public/ILevelViewport.h"
#endif
#include "Editor/UnrealEd/Public/LevelEditorViewport.h"
#include "SLevelViewport.h"

#endif

#include "Slate/S_UEPySWidget.h"
#include "Slate/S_UEPySWindow.h"
// required for GEngine access
#include "Engine/Engine.h"

PyObject *py_ue_game_viewport_client_get_window(ue_PyUObject *self, PyObject *args)
{
	ue_py_check(self);

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "uobject is not a GameViewportClient");

	TSharedPtr<SWindow> Window = viewport->GetWindow();
	if (!Window.IsValid())
		return PyErr_Format(PyExc_Exception, "GameViewportClient has no window");

	return (PyObject *)py_ue_new_swindow(Window.ToSharedRef());
}

PyObject *py_unreal_engine_get_game_viewport_client(PyObject * self, PyObject * args)
{

	UGameViewportClient *viewport_client = GEngine->GameViewport;
	if (!viewport_client)
	{
		return PyErr_Format(PyExc_Exception, "no engine GameViewport found");
	}
	Py_RETURN_UOBJECT(GEngine->GameViewport);
}

#if WITH_EDITOR
PyObject *py_unreal_engine_get_editor_pie_game_viewport_client(PyObject * self, PyObject * args)
{

	UGameViewportClient *viewport_client = GEditor->GameViewport;
	if (!viewport_client)
	{
		return PyErr_Format(PyExc_Exception, "no editor GameViewport found");
	}
	Py_RETURN_UOBJECT(viewport_client);
}

PyObject *py_unreal_engine_editor_set_view_mode(PyObject * self, PyObject * args)
{

	int mode;

	if (!PyArg_ParseTuple(args, "i:editor_set_view_mode", &mode))
	{
		return NULL;
	}

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();
#else
	FLevelEditorModule &EditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	if (!ActiveLevelViewport.IsValid())
#else
	if (!EditorModule.GetFirstActiveViewport().IsValid())
#endif
		return PyErr_Format(PyExc_Exception, "no active LevelEditor Viewport");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorViewportClient& LevelViewportClient = ActiveLevelViewport->GetLevelViewportClient();
#else
	FLevelEditorViewportClient &viewport_client = EditorModule.GetFirstActiveViewport()->GetLevelViewportClient();
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	LevelViewportClient.SetViewMode((EViewModeIndex)mode);
#else
	viewport_client.SetViewMode((EViewModeIndex)mode);
#endif

	Py_RETURN_NONE;
}

PyObject *py_unreal_engine_editor_set_camera_speed(PyObject * self, PyObject * args)
{

	int speed;

	if (!PyArg_ParseTuple(args, "f:editor_set_camera_speed", &speed))
	{
		return NULL;
	}


#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();

	if (!ActiveLevelViewport.IsValid())
#else
	FLevelEditorModule &EditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	if (!EditorModule.GetFirstActiveViewport().IsValid())
#endif
		return PyErr_Format(PyExc_Exception, "no active LevelEditor Viewport");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorViewportClient& LevelViewportClient = ActiveLevelViewport->GetLevelViewportClient();
#else
	FLevelEditorViewportClient &viewport_client = EditorModule.GetFirstActiveViewport()->GetLevelViewportClient();
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	LevelViewportClient.SetCameraSpeedSetting(speed);
#else
	viewport_client.SetCameraSpeedSetting(speed);
#endif

	Py_RETURN_NONE;
}

PyObject *py_unreal_engine_editor_set_view_location(PyObject * self, PyObject * args)
{

	PyObject *py_vector;

	if (!PyArg_ParseTuple(args, "O:editor_set_view_location", &py_vector))
	{
		return NULL;
	}

	ue_PyFVector *vector = py_ue_is_fvector(py_vector);
	if (!vector)
		return PyErr_Format(PyExc_Exception, "argument is not a FVector");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();
#else
	FLevelEditorModule &EditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	if (!ActiveLevelViewport.IsValid())
#else
	if (!EditorModule.GetFirstActiveViewport().IsValid())
#endif
		return PyErr_Format(PyExc_Exception, "no active LevelEditor Viewport");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorViewportClient& LevelViewportClient = ActiveLevelViewport->GetLevelViewportClient();
#else
	FLevelEditorViewportClient &viewport_client = EditorModule.GetFirstActiveViewport()->GetLevelViewportClient();
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	LevelViewportClient.SetViewLocation(vector->vec);
#else
	viewport_client.SetViewLocation(vector->vec);
#endif

	Py_RETURN_NONE;
}

PyObject *py_unreal_engine_editor_set_view_rotation(PyObject * self, PyObject * args)
{

	PyObject *py_rotator;

	if (!PyArg_ParseTuple(args, "O:editor_set_view_rotation", &py_rotator))
	{
		return NULL;
	}

	ue_PyFRotator *rotator = py_ue_is_frotator(py_rotator);
	if (!rotator)
		return PyErr_Format(PyExc_Exception, "argument is not a FRotator");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<SLevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveLevelViewport();
#else
	FLevelEditorModule &EditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	if (!ActiveLevelViewport.IsValid())
#else
	if (!EditorModule.GetFirstActiveViewport().IsValid())
#endif
		return PyErr_Format(PyExc_Exception, "no active LevelEditor Viewport");

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	FLevelEditorViewportClient& LevelViewportClient = ActiveLevelViewport->GetLevelViewportClient();
#else
	FLevelEditorViewportClient &viewport_client = EditorModule.GetFirstActiveViewport()->GetLevelViewportClient();
#endif

#if ENGINE_MAJOR_VERSION == 5 || (ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 24)
	LevelViewportClient.SetViewRotation(rotator->rot);
#else
	viewport_client.SetViewRotation(rotator->rot);
#endif

	Py_RETURN_NONE;
}

#endif

PyObject *py_ue_add_viewport_widget_content(ue_PyUObject *self, PyObject * args)
{

	ue_py_check(self);

	PyObject *py_widget;
	int z_order = 0;

	if (!PyArg_ParseTuple(args, "O|i:add_viewport_widget_content", &py_widget, &z_order))
	{
		return NULL;
	}

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
	{
		UWorld *world = ue_py_check_type<UWorld>(self);
		if (!world)
			return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient or a UWorld");
		viewport = world->GetGameViewport();
		if (!viewport)
			return PyErr_Format(PyExc_Exception, "cannot retrieve GameViewportClient from UWorld");
	}

	TSharedPtr<SWidget> content = py_ue_is_swidget<SWidget>(py_widget);
	if (!content.IsValid())
	{
		return nullptr;
	}

	viewport->AddViewportWidgetContent(content.ToSharedRef());

	Py_RETURN_NONE;
}

PyObject *py_ue_remove_viewport_widget_content(ue_PyUObject *self, PyObject * args)
{

	ue_py_check(self);

	PyObject *py_widget;

	if (!PyArg_ParseTuple(args, "O:remove_viewport_widget_content", &py_widget))
	{
		return NULL;
	}

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient");

	TSharedPtr<SWidget> content = py_ue_is_swidget<SWidget>(py_widget);
	if (!content.IsValid())
	{
		return nullptr;
	}

	viewport->RemoveViewportWidgetContent(content.ToSharedRef());

	Py_RETURN_NONE;
}

PyObject *py_ue_remove_all_viewport_widgets(ue_PyUObject *self, PyObject * args)
{

	ue_py_check(self);

	UGameViewportClient *viewport = ue_py_check_type<UGameViewportClient>(self);
	if (!viewport)
		return PyErr_Format(PyExc_Exception, "object is not a GameViewportClient");


	viewport->RemoveAllViewportWidgets();

	Py_RETURN_NONE;
}

PyObject *py_ue_game_viewport_client_set_rendering_flag(ue_PyUObject *self, PyObject * args)
{

	ue_py_check(self);

	PyObject *py_bool;

	if (!PyArg_ParseTuple(args, "O:game_viewport_client_set_rendering_flag", &py_bool))
	{
		return nullptr;
	}

	bool bEnabled = PyObject_IsTrue(py_bool) ? true : false;

	UGameViewportClient *ViewportClient = ue_py_check_type<UGameViewportClient>(self);
	if (!ViewportClient)
	{
		return PyErr_Format(PyExc_Exception, "object is not a UGameViewportClient");
	}

	ViewportClient->EngineShowFlags.Rendering = bEnabled;

	Py_RETURN_NONE;
}

