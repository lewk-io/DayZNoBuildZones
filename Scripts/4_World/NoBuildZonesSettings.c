/**
 * 
 * NoBuildZonesSettings
 * 
 * NoBuildZones example:
 * [
 *      {
 *          "Name": "No build zone 1",
 *          "Description": "zone 1",
 *          "X": "7500",
 *          "Y": "7500",
 *          "Radius": "1000"
 *      }
 * ]
 * 
 **/

ref NoBuildZonesSettings m_NoBuildZonesSettings;

class NoBuildZonesSettings
{
    protected static string NoBZ_CONFIG = "$profile:NoBuildZones.json";

    bool EnableMessages = true;
    bool UseNotifications = true;
    float RefreshTimer = 1;
    string Prefix = "NO BUILD ZONE";
    string WarningMessage = "You are too close to $$0$$ to build.";
    ref array<string> IgnoredItems;
    ref array<ref NoBZ_Location> NoBuildZones;

    void NoBuildZonesSettings()
    {
        IgnoredItems = new ref array<string>;
        NoBuildZones = new ref array<ref NoBZ_Location>;
    }

    string GetWarningMessage( string Description = "" )
    {
        string WarningMessage = m_NoBuildZonesSettings.WarningMessage;
        WarningMessage.Replace( "$$0$$", Description );
        return WarningMessage;
    }

    void SendWarningMessage( PlayerBase player )
    {
        string message = GetWarningMessage( player.GetNoBZDesc() );
        if ( EnableMessages )
        {
            if ( UseNotifications )
            {
                PlayerIdentity sender = player.GetIdentity();
                NotificationSystem.CreateNotification( new StringLocaliser( m_NoBuildZonesSettings.Prefix ), new StringLocaliser( message ), "DayZNoBuildZones/Data/NoBuildZoneIcon.edds", ARGB( 255, 231, 76, 60 ), 7, sender );
            } else {
                GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCSystem, "", m_NoBuildZonesSettings.Prefix + " | " + message, "colorImportant"));
                GetGame().Chat( m_NoBuildZonesSettings.Prefix + " | " + message, "colorImportant" );
            }
        }
    }

    vector NoBZLocationToVector( float x, float y )
    {
        string sPosition = "" + x + " " + GetGame().SurfaceY(x, y) + " " + y;
        return sPosition.ToVector();
    }

    void Load()
    {
        ref NoBuildZonesSettings settings = new NoBuildZonesSettings();

        if ( FileExist( NoBZ_CONFIG ) )
        {
            JsonFileLoader<NoBuildZonesSettings>.JsonLoadFile( NoBZ_CONFIG, this );
        } else {
            IgnoredItems.Insert( "Fireplace" );
            NoBuildZones.Insert( new ref NoBZ_Location( "No build zone 1 exmaple", "zone 1 example", 7500, 7500, 1000 ) );
            JsonFileLoader<NoBuildZonesSettings>.JsonSaveFile( NoBZ_CONFIG, this );
        }
    }
}

static ref NoBuildZonesSettings NoBZ()
{
    if (!m_NoBuildZonesSettings)
    {
        m_NoBuildZonesSettings = new NoBuildZonesSettings;
        m_NoBuildZonesSettings.Load();
    }
    return m_NoBuildZonesSettings;
};