#include "ShowChestIndicator.h"

namespace cheat {
    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);

    ShowChestIndicator::ShowChestIndicator() {
	f_Enabled = config::getValue("functions:ShowChestIndicator", "enabled", false);
	f_Waypoints = config::getValue("functions:ShowChestIndicator", "waypoints", false);
	f_Chests = config::getValue("functions:ShowChestIndicator", "chests", true);
        f_Hotkey = Hotkey("functions:ShowChestIndicator");

        HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);
    }

    ShowChestIndicator& ShowChestIndicator::getInstance() {
        static ShowChestIndicator instance;
        return instance;
    }

    void ShowChestIndicator::GUI() {
        ConfigCheckbox(_("Show indicators"), f_Enabled, _("Show chests or/and waypoints indicators."));

        if (f_Enabled.getValue()) {
            ImGui::Indent();
	    ConfigCheckbox(_("Show chests indicators"), f_Chests, _("Show chests indicators."));
	    ConfigCheckbox(_("Show waypoints indicators"), f_Waypoints, _("Show waypoints indicators."));

            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ShowChestIndicator::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void ShowChestIndicator::Status() {
        if (f_Enabled.getValue())
            ImGui::Text("Show Chest Indicator");
    }

    std::string ShowChestIndicator::getModule() {
        return _("Visuals");
    }

    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
	auto& showChestIndicator = ShowChestIndicator::getInstance();
	bool isWaypoint = (__this->fields._dataItem->fields.ownerUid == 0);

	bool showIcon = (showChestIndicator.f_Chests.getValue() && !isWaypoint) ||
	    (showChestIndicator.f_Waypoints.getValue() && isWaypoint) ||
	    (showChestIndicator.f_Chests.getValue() && showChestIndicator.f_Waypoints.getValue());

	if (showIcon)
	    app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
	else
	    app::MoleMole_LCIndicatorPlugin_HideIcon(__this);

	return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
    }
}
