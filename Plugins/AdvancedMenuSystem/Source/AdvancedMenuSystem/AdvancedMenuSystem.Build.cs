//========= Copyright 2024 Head Mounted Software, All rights reserved. ============//

using UnrealBuildTool;

public class AdvancedMenuSystem : ModuleRules
{
	public AdvancedMenuSystem(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrecompileForTargets = PrecompileTargetsType.Any;

  //      PublicIncludePaths.AddRange(
		//	new string[] {
  //              "AdvancedMenuSystem/Public/"
  //          }
		//	);
				
		
		//PrivateIncludePaths.AddRange(
		//	new string[] {
  //              "AdvancedMenuSystem/Private/"
  //          }
		//	);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "InputCore"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EnhancedInput",
                "UMG",
                "CommonUI"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
