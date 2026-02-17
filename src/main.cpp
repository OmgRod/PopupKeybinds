#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/loader/GameEvent.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		if (!FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale)) return false;

		this->addEventListener(KeybindSettingPressedEventV3(Mod::get(), "btn1"), [this](Keybind const& keybind, bool down, bool repeat, double timestamp) {
            if (down && !repeat) {
                onBtn1(nullptr);
            }
        });

		this->addEventListener(KeybindSettingPressedEventV3(Mod::get(), "btn2"), [this](Keybind const& keybind, bool down, bool repeat, double timestamp) {
            if (down && !repeat) {
                onBtn2(nullptr);
            }
        });

		return true;
	}
};