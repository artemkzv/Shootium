// Shootium Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootiumTarget : TargetRules
{
	public ShootiumTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Shootium" } );
	}
}
