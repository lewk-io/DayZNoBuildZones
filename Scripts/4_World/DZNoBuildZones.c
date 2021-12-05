ref DZNoBuildZonesSettings zf_NoBuildZones;

const string NO_BUILD_ZONES_PATH = "$profile:NoBuildZones.json";

class DZNoBuildZonesSettings {
    bool Enabled = true;
    bool UseNotifications = true;
    float RefreshTimer = 1;
    string Prefix = "NO BUILD ZONE";
    string WarningMessage = "You are too close to $$0$$ to build.";
    ref array<string> IgnoredItems;
    ref array<ref DZNoBuildZonesZone> NoBuildZones;

    void DZNoBuildZonesSettings() {
        IgnoredItems = new ref array<string>;
        NoBuildZones = new ref array<ref DZNoBuildZonesZone>;
    }

    // string GetWarningMessage(string Description = ""){
    //     string NewWarningMessage = zf_NoBuildZones.WarningMessage;
    //     NewWarningMessage.Replace("$$0$$", Description);
    //     return NewWarningMessage;
    // }

    // void SendWarningMessage(PlayerBase player) {
    //     if (player.GetNoBuildZonesUseNotification()) {
    //         string Message = player.GetNoBuildZonesWarningMessage();
    //         Message.Replace("$$0$$", player.GetActiveNoBuildZone().Description);
    //         bool MessageSent = false;

    //         // #ifdef EXPANSIONMOD
    //         // if (!MessageSent) {
    //         //     // Send Expansion notification
    //         //     MessageSent = true;
    //         // }
    //         // #endif
    //         // #ifdef
    //         // if (!MessageSent) {
    //         //     // Send VPPAdminTools notification
    //         //     MessageSent = true;
    //         // }
    //         // #endif
    //         if (!MessageSent) {
    //             SendChatMessage(player);
    //             MessageSent = true;
    //         }
    //     }
    // }        

    // void SendChatMessage(PlayerBase player) {
    //     Param2<string, string> NoBZVars = new Param2<string, string>( player.GetActiveNoBuildZone().Name, player.GetActiveNoBuildZone().Description );
    //     ScriptRPC rpc = new ScriptRPC();
    //     GetGame().RPCSingleParam(player, NOBUILDZONE.NOBZ_MESSAGE, NoBZVars, true, player.GetIdentity()) ;
    // }

    // bool GetUseNotifications() {
    //     return UseNotifications;
    // }

    void SendZonesToPlayer() {
        GetRPCManager().SendRPC("DZNoBuildZones", "SendZoneSettings", new Param1<ref DZNoBuildZonesSettings>(this), true, NULL);
    }

    void Load() {
        if (FileExist(NO_BUILD_ZONES_PATH)) {
            JsonFileLoader<DZNoBuildZonesSettings>.JsonLoadFile(NO_BUILD_ZONES_PATH, this);
        } else {
            Save();
        }
    }

    void Save() {
        JsonFileLoader<DZNoBuildZonesSettings>.JsonSaveFile(NO_BUILD_ZONES_PATH, this);
    }
}

class DZNoBuildZonesZone {
    string Name;
    string Description;
    float X;
    float Y;
    int Radius;

    void DZNoBuildZonesZone(string name, string description, float x, float y, int radius) {
        Name = name;
        Description = description;
        X = x;
        Y = y;
        Radius = radius;
    }
}

static ref DZNoBuildZonesSettings DZNoBuildZones() {
    if (!zf_NoBuildZones) {
        zf_NoBuildZones = new DZNoBuildZonesSettings;
        zf_NoBuildZones.Load();
    }

    return zf_NoBuildZones;
}