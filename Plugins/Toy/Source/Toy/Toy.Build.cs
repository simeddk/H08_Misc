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
	}
}
