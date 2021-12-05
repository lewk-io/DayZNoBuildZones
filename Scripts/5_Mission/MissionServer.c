modded class MissionServer {
	override void OnInit() {
		super.OnInit();

		DZNoBuildZones();
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) {
		super.InvokeOnConnect(player, identity);

		DZNoBuildZones().SendZonesToPlayer();
	}
}