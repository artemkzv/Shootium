// Shootium Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootiumEditorTarget : TargetRules
{
	public ShootiumEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "Shootium" } );
	}
}
