// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class xfactor : ModuleRules
{
	public xfactor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"xfactor",
			"xfactor/Variant_Platforming",
			"xfactor/Variant_Platforming/Animation",
			"xfactor/Variant_Combat",
			"xfactor/Variant_Combat/AI",
			"xfactor/Variant_Combat/Animation",
			"xfactor/Variant_Combat/Gameplay",
			"xfactor/Variant_Combat/Interfaces",
			"xfactor/Variant_Combat/UI",
			"xfactor/Variant_SideScrolling",
			"xfactor/Variant_SideScrolling/AI",
			"xfactor/Variant_SideScrolling/Gameplay",
			"xfactor/Variant_SideScrolling/Interfaces",
			"xfactor/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
