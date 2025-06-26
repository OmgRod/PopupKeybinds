#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;
using namespace keybinds;

$execute {
    BindManager::get()->registerBindable({
        "btn1"_spr,
        "Button 1",
        "Popup button 1 keybind (typically for cancelling)",
        { Keybind::create(KEY_C, Modifier::None) },
        "Global/Popups"
    });

	BindManager::get()->registerBindable({
        "btn2"_spr,
        "Button 2",
        "Popup button 2 keybind (typically for accepting something)",
        { Keybind::create(KEY_Space, Modifier::None), Keybind::create(KEY_Enter, Modifier::None) },
        "Global/Popups"
    });
}

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		if (!FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale)) return false;

		this->template addEventListener<InvokeBindFilter>([&](InvokeBindEvent* event) {
			if (event->isDown()) {
				onBtn1(nullptr);
				return ListenerResult::Stop;
			}
			return ListenerResult::Propagate;
		}, "btn1"_spr);

		if (btn2) {
			this->template addEventListener<InvokeBindFilter>([&](InvokeBindEvent* event) {
				if (event->isDown()) {
					onBtn2(nullptr);
					return ListenerResult::Stop;
				}
				return ListenerResult::Propagate;
			}, "btn2"_spr);
		}

		return true;
	}
};