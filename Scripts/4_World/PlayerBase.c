modded class PlayerBase
{
    bool m_isInNoBZ = false;
    string m_NoBZ_Name = "";
    string m_NoBZ_Desc = "";

    bool GetIsInNoBZ()
    {
        return m_isInNoBZ;
    }

    string GetNoBZName()
    {
        return m_NoBZ_Name;
    }

    string GetNoBZDesc()
    {
        return m_NoBZ_Desc;
    }

    void SetIsInNoBZ( bool b, string name = "", string desc = "" )
    {
        m_isInNoBZ = b;
        m_NoBZ_Name = name;
        m_NoBZ_Desc = desc;
    }

	override void OnRPC( PlayerIdentity sender, int rpc_type, ParamsReadContext ctx )
	{
		super.OnRPC( sender, rpc_type, ctx );	

        if ( GetGame().IsClient() && rpc_type == NOBUILDZONE.NOBZ_MESSAGE )
		{
            Param2<string, string> data;
            if( !ctx.Read( data ) ) return;
            string message = "[" + NoBuildZonesSettings.Prefix + "] " + NoBuildZonesSettings.GetWarningMessage( data.param2 );
            this.Message( message, "colorImportant" );
        }
    }
}