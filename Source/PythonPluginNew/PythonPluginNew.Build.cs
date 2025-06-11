// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class PythonPluginNew : ModuleRules
	{
		public PythonPluginNew(ReadOnlyTargetRules Target) : base(Target)
		{
        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
                Target.UEThirdPartySourceDirectory,
                Target.RelativeEnginePath
            }
            );
			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
					"Sockets",
					"Networking",
					"AssetRegistry", "SlateCore", "AnimationCore" 
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Analytics",
					"AssetRegistry",
					"Projects",
					"Python3",
					"Slate",
					"SlateCore",
					"InputCore",
					"Sockets",
					"Networking",
					"Json",
					"DeveloperSettings",
					"CoreUObject",
					"Engine",
					"MovieScene",
					"LevelSequence",
					"HTTP",
					"UMG",
					"AppFramework",
					"RHI",
					"Voice",
					"RenderCore",
					"MovieSceneCapture",
					"Landscape",
					"Foliage",
					"AIModule",
					"ApplicationCore"				
				}
			);

			if (Target.bBuildEditor == true)
			{
				PublicDependencyModuleNames.AddRange(
					new string[] {
						"ToolMenus"
					}
				);

				PrivateDependencyModuleNames.AddRange(
					new string[] {
						"DesktopPlatform",
						"LevelEditor",
						"EditorFramework",
						"UnrealEd",
						"EditorSubsystem",
						"BlueprintGraph",
						"KismetCompiler",
						"AssetTools",
						"ContentBrowserData",
						"ContentBrowserFileDataSource",
						"Projects",
						"Sequencer",
						"SequencerWidgets",
						"LevelSequenceEditor",
						"MovieSceneTools",
						"MovieSceneTracks",
						"CinematicCamera",
						"EditorStyle",
						"GraphEditor",
						"UMGEditor",
						"AIGraph",
						"RawMesh",
						"DesktopWidgets",
						"EditorWidgets",
						"FBX",
						"Persona",
						"PropertyEditor",
						"LandscapeEditor",
						"MaterialEditor",
                        "PythonScriptPlugin"
                    }
				);
			}
		}
	}
}
