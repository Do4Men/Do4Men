#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "LevTT.cpp"
#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(D4MLayer, LevelInfoLayer) {
	bool init(GJGameLevel * level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;
		auto menu = this->getChildByID("other-menu");
		auto D4Mbutton = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_statsBtn_001.png", 0.65f, [this](auto) {
			D4MLayer::onD4MLevelInfo(this);
			});
		D4Mbutton->setPositionX(76);
		menu->addChild(D4Mbutton);
		menu->updateLayout();
		return true;
	}
	void onD4MLevelInfo(CCObject*) {
		std::string Type;
		if (m_level->m_levelType == GJLevelType::Local) Type = "Local";
		if (m_level->m_levelType == GJLevelType::Editor) Type = "Editor";
		if (m_level->m_levelType == GJLevelType::Saved) Type = "Saved";

		std::string ID = std::to_string(EditorIDs::getID(m_level));
		LevTT::create(Type, ID)->show();

		srand(time(0));
		int Rand = rand() % 100;
		if (!Rand) {
			geode::createQuickPopup(
				"Wow",            // title
				"Mega reklama",   // content
				"Nah", "Femboys",      // buttons
				[](auto, bool btn2) {
					if (btn2) ShellExecuteA(0, 0, "https://t.me/utro14", 0, 0, SW_SHOW);
				}
			);
		}
	}
};