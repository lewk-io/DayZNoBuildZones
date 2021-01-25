class CfgPatches
{
	class NoBuildZones
	{
		requiredAddons[]={
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class NoBuildZones
	{
		dir="DayZNoBuildZones";
		name="No Build Zones";
		author="@Lewk_io";
		type="mod";
		dependencies[]={
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"DayZNoBuildZones/Scripts/4_World",
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"DayZNoBuildZones/Scripts/5_Mission",
				};
			};
		};
	};
};