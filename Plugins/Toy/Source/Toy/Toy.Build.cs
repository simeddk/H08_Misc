// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Toy : ModuleRules
{
	public Toy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		//Header Dependency
		PrivateIncludePaths.Add(ModuleDirectory);

		//Binary Dependency
		PublicDependencyModuleNames.Add("Core");

		PrivateDependencyModuleNames.Add("CoreUObject");
		PrivateDependencyModuleNames.Add("Engine");
		PrivateDependencyModuleNames.Add("Slate");
		PrivateDependencyModuleNames.Add("SlateCore");
		PrivateDependencyModuleNames.Add("EditorStyle");
		PrivateDependencyModuleNames.Add("Projects");
		PrivateDependencyModuleNames.Add("GameplayDebugger");
		PrivateDependencyModuleNames.Add("PropertyEditor");
		PrivateDependencyModuleNames.Add("MainFrame");
		PrivateDependencyModuleNames.Add("DesktopPlatform");
		PrivateDependencyModuleNames.Add("UnrealEd");
		PrivateDependencyModuleNames.Add("AdvancedPreviewScene");
		PrivateDependencyModuleNames.Add("InputCore");

		PrivateDependencyModuleNames.Add("H08_Misc");
	}
}
