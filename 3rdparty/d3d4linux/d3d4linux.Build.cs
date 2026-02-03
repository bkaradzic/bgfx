
using UnrealBuildTool;

public class d3d4linux : ModuleRules
{
	public d3d4linux(TargetInfo Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PublicIncludePaths.Add(UEBuildConfiguration.UEThirdPartySourceDirectory + "d3d4linux/include");
		}
	}
}

