modded class ActionDeployObject {			 	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (player.GetIsInNoBuildZone() && player.GetNoBuildZoneIgnoredItems().Find(item.GetType()) < 0) return false;

        return super.ActionCondition(player, target, item);
	}
};