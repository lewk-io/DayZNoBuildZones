modded class MissionServer
{
	float m_BZ_UpdateTime = m_BZ_UpdateTime;

	override void OnInit()
	{
		super.OnInit();
		NoBZ();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		m_BZ_UpdateTime += timeslice;

        if (m_BZ_UpdateTime >= NoBZ().RefreshTimer)
        {
            m_BZ_UpdateTime = 0;

			for ( int i = 0; i < m_Players.Count(); i++ )
			{
				PlayerBase player = PlayerBase.Cast(m_Players.Get(i));

				if ( !player ) continue;
                if ( !player.IsAlive() ) continue;

				if ( player.GetIsInNoBZ() ) player.SetIsInNoBZ( false );

				for ( int j = 0; j < NoBZ().NoBuildZones.Count(); j++ )
				{
					float x = NoBZ().NoBuildZones.Get(j).X;
					float y = NoBZ().NoBuildZones.Get(j).Y;
					vector NoBZ_Location_Position = NoBZ().NoBZLocationToVector( x, y );

					if ( vector.Distance( player.GetPosition(), NoBZ_Location_Position ) <= NoBZ().NoBuildZones.Get(j).Radius )
					{
						if ( !player.GetIsInNoBZ() ) player.SetIsInNoBZ( true, NoBZ().NoBuildZones.Get(j).Name, NoBZ().NoBuildZones.Get(j).Description );
					}
				}
            }
        }
    }
}