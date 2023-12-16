// Shootium Game. All Rights Reserved.

using UnrealBuildTool;

public class Shootium : ModuleRules
{
	public Shootium(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"PhysicsCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"Shootium/Public/Player", 
			"Shootium/Public/Components", 
			"Shootium/Public/Dev",
			"Shootium/Public/Weapon",
            "Shootium/Public/Weapon/Components",
            "Shootium/Public/UI",
            "Shootium/Public/Animations",
            "Shootium/Public/Pickups"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
