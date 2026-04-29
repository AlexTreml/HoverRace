using UnrealBuildTool;
using System.Collections.Generic;

public class HoverVehicleSystemTarget : TargetRules
{
    public HoverVehicleSystemTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;

        ExtraModuleNames.Add("HoverVehicleSystem");
    }
}
