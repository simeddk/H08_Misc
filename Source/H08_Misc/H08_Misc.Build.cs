// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class H08_Misc : ModuleRules
{
	public H08_Misc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
        PublicDependencyModuleNames.AddRange(new string[]
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule",
			"ProceduralMeshComponent" 
		});
	}
}
