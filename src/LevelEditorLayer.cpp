//#include <Geode/Geode.hpp>
//using namespace geode::prelude;
//#include "saved.cpp"
//#include <time.h>
//#include <cvolton.level-id-api/include/EditorIDs.hpp>
//#include <Geode/modify/LevelEditorLayer.hpp>
//class $modify(LevelEditorLayer) {
//	bool init(GJGameLevel * level, bool p0) {
//		if (!LevelEditorLayer::init(level, p0)) return false;
//		auto Tot = Mod::get()->getSavedValue<Total>("Tot");
//		Tot.attTot = level->m_timestamp;
//		Mod::get()->setSavedValue("Tot", Tot);
//		Mod::get()->saveData();
//		log::error("LevelEditorLayer");
//		return true;
//	}
//}; обойдетесь