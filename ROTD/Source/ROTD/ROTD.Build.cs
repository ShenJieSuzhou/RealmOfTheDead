// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ROTD : ModuleRules
{
	public ROTD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Niagara" });

        PrivateIncludePaths.AddRange(
           new string[] {
           // ... add other private include paths required here  ...
            "ROTD/Weapons",
           }
         );

    }
}
