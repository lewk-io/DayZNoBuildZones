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
    static string Prefix = "NO BUILD ZONE";
    static string WarningMessage = "You are too close to $$0$$ to build.";
    ref array<string> IgnoredItems;
    ref array<ref NoBZ_Location> NoBuildZones;

    void NoBuildZonesSettings()
    {
        IgnoredItems = new ref array<string>;
        NoBuildZones = new ref array<ref NoBZ_Location>;
    }

    static string GetWarningMessage( string Description = "" )
    {
        string NewWarningMessage = m_NoBuildZonesSettings.WarningMessage;
        NewWarningMessage.Replace( "$$0$$", Description );
        return NewWarningMessage;
    }

    void SendWarningMessage( PlayerBase player )
    {
        bool NotificationWasSent = false;
        string message = GetWarningMessage( player.GetNoBZDesc() );
        if ( EnableMessages )
        {
            if ( UseNotifications )
            {
                string icon = "DayZNoBuildZones/Data/NoBuildZoneIcon.edds";
                PlayerIdentity sender = player.GetIdentity();
                #ifdef JM_COT
                if ( !NotificationWasSent )
                {
                    NotificationSystem.CreateNotification( new StringLocaliser( m_NoBuildZonesSettings.Prefix ), new StringLocaliser( message ), icon, ARGB( 255, 231, 76, 60 ), 7, sender );
                    NotificationWasSent = false;
                }
                #endif
                #ifdef VPPADMINTOOLS
                if ( !NotificationWasSent && GetGame().IsClient() )
                {
                    VPPNotificationManager.SendMessage( new VPPMessageProps( m_NoBuildZonesSettings.Prefix, message, 5.0, 1.0, icon ), sender );
                    NotificationWasSent = false;
                }
                #endif
                if ( !NotificationWasSent ) SendChatMessage( player )

            } else {
                SendChatMessage( player );
            }
        }
    }

    void SendChatMessage( PlayerBase player )
    {
        Param2<string, string> NoBZVars = new Param2<string, string>( player.GetNoBZName(), player.GetNoBZDesc() );
        ScriptRPC rpc = new ScriptRPC();
        GetGame().RPCSingleParam( player, NOBUILDZONE.NOBZ_MESSAGE, NoBZVars, true, player.GetIdentity() ) ;
    }

    bool ShouldUseNotifications()
    {
        if ( UseNotifications )
        {
            #ifdef JM_COT
            return UseNotifications;
            #endif
            #ifdef VPPADMINTOOLS
            return UseNotifications;
            #endif
            return false;
        }
        return true;
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