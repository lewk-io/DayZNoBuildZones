class CfgPatches {
	class NoBuildZones {
		requiredAddons[]={"JM_CF_Scripts"};
	};
};

class CfgMods {
	class NoBuildZones {
		dir="DayZNoBuildZones";
		name="No Build Zones";
		author="@Lewk_io";
		type="mod";
		dependencies[]={
			"Game",
			"World",
			"Mission"
		};
		class defs{
			class gameScriptModule{
				value="";
				files[]={
					"DayZNoBuildZones/Scripts/3_Game"
				};
			};
			class worldScriptModule{
				value="";
				files[]={
					"DayZNoBuildZones/Scripts/4_World"
				};
			};
			class missionScriptModule{
				value="";
				files[]={
					"DayZNoBuildZones/Scripts/5_Mission"
				};
			};
		};
	};
};