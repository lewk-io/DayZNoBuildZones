modded class ActionDeployObject
{			 	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( player.GetIsInNoBZ() && ( NoBZ().IgnoredItems.Find( item.GetType() ) < 0 ) )
        {
            NoBZ().SendWarningMessage( player );
            return false;
        }

		return super.ActionCondition( player, target, item );
	}
};
