modded class MissionGameplay {
    // private ref Widget zf_NoBuildZoneWidget;
    // private ref TextWidget zf_NoBuildZoneTextWidget;

    // void ~MissionGameplay() {
    //     delete zf_NoBuildZoneWidget;
    // }

    // override void OnMissionStart() {
    //     super.OnMissionStart();

    //     zf_NoBuildZoneWidget = GetGame().GetWorkspace().CreateWidgets("DayZNoBuildZones/Data/Overlay.layout");
    //     zf_NoBuildZoneTextWidget = TextWidget.Cast(zf_NoBuildZoneWidget.FindAnyWidget("zf_NoBuildZoneTextWidget"));
    //     zf_NoBuildZoneTextWidget.Show(true);
    // }

    // void SetNoBuildZoneTextWidgetText(string Text) {
    //     zf_NoBuildZoneTextWidget.SetText(Text);
    // }

	// override void OnUpdate(float timeslice) {
    //     super.OnUpdate(timeslice);

    //     if (!zf_NoBuildZoneWidget || !zf_NoBuildZoneTextWidget) return;

    //     PlayerBase Player = PlayerBase.Cast(GetGame().GetPlayer());

    //     if (Player.GetIsInNoBuildZone()) {
    //         string Message = Player.GetNoBuildZonesWarningMessage();
    //         Message.Replace("$$0$$", Player.GetActiveNoBuildZone().Description);
    //         SetNoBuildZoneTextWidgetText(Message);
    //     } else {
    //         SetNoBuildZoneTextWidgetText("");
    //     }
    // }
}