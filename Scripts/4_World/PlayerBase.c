modded class PlayerBase {
    protected DZNoBuildZonesSettings player_NoBuildZones;
    protected ref array<string> zf_IgnoredItems;
    protected DZNoBuildZonesZone zf_ActiveZone;
    protected bool zf_UseNotifications;
    protected string zf_WarningMessage;
    bool zf_HasRefreshRate = false;
    float zf_RefreshRate = 0
    float zf_Tick = 0;
    bool zf_IsInNoBuildZone = false;

    void PlayerBase() {
        GetRPCManager().AddRPC("DZNoBuildZones", "SendZoneSettings", this, SingleplayerExecutionType.Client);
    }

    void SendZoneSettings(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
        if (type == CallType.Client) {
            Param1<ref DZNoBuildZonesSettings> data;
            if (!ctx.Read(data)) return;
            if (data && data.param1) SaveZoneSettings(data.param1);
        }
    }

    void SaveZoneSettings(DZNoBuildZonesSettings settings) {
        player_NoBuildZones = settings;
        if (settings.IgnoredItems) zf_IgnoredItems = settings.IgnoredItems;
        if (settings.UseNotifications) zf_UseNotifications = settings.UseNotifications;
        if (settings.WarningMessage) zf_WarningMessage = settings.WarningMessage;
    }

    DZNoBuildZonesSettings GetNoBuildZones() {
        return player_NoBuildZones;
    }

    array<string> GetNoBuildZoneIgnoredItems() {
        return zf_IgnoredItems;
    }

    DZNoBuildZonesZone GetActiveNoBuildZone() {
        return zf_ActiveZone;
    }

    bool GetIsInNoBuildZone() {
        return zf_IsInNoBuildZone;
    }

    bool GetNoBuildZonesUseNotification() {
        return zf_UseNotifications;
    }

    string GetNoBuildZonesWarningMessage() {
        return zf_WarningMessage;
    }

    void OnScheduledTick(float deltaTime) {
		super.OnScheduledTick(deltaTime)

        if (player_NoBuildZones) {
            if (!zf_HasRefreshRate && player_NoBuildZones.RefreshTimer) zf_RefreshRate = player_NoBuildZones.RefreshTimer;

            zf_Tick += deltaTime;
            
            if (player_NoBuildZones.NoBuildZones && player_NoBuildZones.NoBuildZones.Count() > 0) {
                int TotalZones = player_NoBuildZones.NoBuildZones.Count();

                if (zf_Tick >= zf_RefreshRate) {
                    bool IsInBuildZone = false;
                    foreach(DZNoBuildZonesZone Zone: player_NoBuildZones.NoBuildZones) {
                        if (vector.Distance(GetPosition(), Vector(Zone.X, GetGame().SurfaceY(Zone.X, Zone.Y), Zone.Y)) <= Zone.Radius) {
                            IsInBuildZone = true;
                            zf_ActiveZone = Zone;
                        }
                    }
                    zf_IsInNoBuildZone = IsInBuildZone;

                    zf_Tick = 0;
                }
            }
        }
    }

	// override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
	// 	super.OnRPC(sender, rpc_type, ctx);	

    //     if (GetGame().IsClient() && rpc_type == NOBUILDZONE.NOBZ_MESSAGE) {
    //         Print("NOBUILDZONE.NOBZ_MESSAGE");
    //         Param2<string, string> data;
    //         if( !ctx.Read( data ) ) return;
    //         Print(player_NoBuildZones.Prefix)
    //         Print(player_NoBuildZones.GetWarningMessage(data.param2))
    //         string message = "[" + player_NoBuildZones.Prefix + "] " + player_NoBuildZones.GetWarningMessage(data.param2);
    //         this.Message( message, "colorImportant" );
    //     }
    // }
}