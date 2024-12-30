#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "saved.cpp"
#include "MenuLayer.cpp"
#include <time.h>
#include <cvolton.level-id-api/include/EditorIDs.hpp>
#include <Geode/modify/PlayLayer.hpp>
inline time_t stSes;
class $modify(PlayLayer) {
    bool init(GJGameLevel * level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        if (!stSes) stSes = time(NULL); 
        int ID = EditorIDs::getID(m_level);

        std::string Type;
        if (m_level->m_levelType == GJLevelType::Local) Type = "Local";
        if (m_level->m_levelType == GJLevelType::Editor) Type = "Editor";
        if (m_level->m_levelType == GJLevelType::Saved) Type = "Saved";

        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        Game[std::to_string(stGame)].GameSes[std::to_string(stSes)].stGameSes = stSes;
        Game[std::to_string(stGame)].GameSes[std::to_string(stSes)].IDGameLev = ID;
        Game[std::to_string(stGame)].GameSes[std::to_string(stSes)].TypeGameLev = Type;

        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        Level[Type].Level[std::to_string(ID)].IDLev = ID;
        Level[Type].Level[std::to_string(ID)].nameLev = m_level->m_levelName;
        Level[Type].Level[std::to_string(ID)].LevDay[std::to_string(stDay)].stLevDay = stDay;
        Level[Type].Level[std::to_string(ID)].LevDay[std::to_string(stDay)].LevDayGame[std::to_string(stGame)].stLevDayGame = stGame;
        if (!Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].stGameSes) Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].stGameSes = stSes; 
        Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].LevGameSes[std::to_string(stSes)].stGameSes = stSes;
        Level[Type].Level[std::to_string(ID)].LevSes[std::to_string(stSes)].stLevSes = stSes;
        Mod::get()->setSavedValue("Game", Game);
        Mod::get()->setSavedValue("Level", Level);
        Mod::get()->saveData();
        return true;
    }
    void resetLevel() {
        if (!stSes) stSes = time(NULL); 
        auto Tot = Mod::get()->getSavedValue<Total>("Tot");
        auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});

        int ID = EditorIDs::getID(m_level);
        std::string Type;
        if (m_level->m_levelType == GJLevelType::Local) Type = "Local"; 
        if (m_level->m_levelType == GJLevelType::Editor) Type = "Editor"; 
        if (m_level->m_levelType == GJLevelType::Saved) Type = "Saved"; 

        Tot.tPlayTot += m_attemptTime;
        Tot.attTot++;

        Day[std::to_string(stDay)].tPlayDay += m_attemptTime;
        Day[std::to_string(stDay)].attDay++;

        Game[std::to_string(stGame)].tPlayGame += m_attemptTime;
        Game[std::to_string(stGame)].attGame++;

        Level[Type].Level[std::to_string(ID)].tPlayLev += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].attLev++;

        Level[Type].Level[std::to_string(ID)].LevDay[std::to_string(stDay)].tPlayLevDay += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].LevDay[std::to_string(stDay)].attLevDay++;

        Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].tPlayLevGame += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].attLevGame++;

        Level[Type].Level[std::to_string(ID)].LevSes[std::to_string(stSes)].tPlayLevSes += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].LevSes[std::to_string(stSes)].attLevSes++;

        Mod::get()->setSavedValue("Tot", Tot);
        Mod::get()->setSavedValue("Day", Day);
        Mod::get()->setSavedValue("Game", Game);
        Mod::get()->setSavedValue("Level", Level);
        Mod::get()->saveData();
        PlayLayer::resetLevel();
    }
    void onQuit() {
        time_t endT = time(NULL);
        auto Tot = Mod::get()->getSavedValue<Total>("Tot");
        auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});

        int ID = EditorIDs::getID(m_level);
        std::string Type;
        if (m_level->m_levelType == GJLevelType::Local) Type = "Local";
        if (m_level->m_levelType == GJLevelType::Editor) Type = "Editor";
        if (m_level->m_levelType == GJLevelType::Saved) Type = "Saved";

        Tot.tPlayTot += m_attemptTime;

        Day[std::to_string(stDay)].tPlayDay += m_attemptTime;

        Game[std::to_string(stGame)].tPlayGame += m_attemptTime;
        Game[std::to_string(stGame)].endGame = endT;

        Level[Type].Level[std::to_string(ID)].tPlayLev += m_attemptTime;

        Level[Type].Level[std::to_string(ID)].LevDay[std::to_string(stDay)].tPlayLevDay += m_attemptTime;

        Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].tPlayLevGame += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].LevGame[std::to_string(stGame)].endLevGame = endT;

        Level[Type].Level[std::to_string(ID)].LevSes[std::to_string(stSes)].tPlayLevSes += m_attemptTime;
        Level[Type].Level[std::to_string(ID)].LevSes[std::to_string(stSes)].endLevSes = endT;

        Mod::get()->setSavedValue("Tot", Tot);
        Mod::get()->setSavedValue("Day", Day);
        Mod::get()->setSavedValue("Game", Game);
        Mod::get()->setSavedValue("Level", Level);
        Mod::get()->saveData();
        stSes = 0;
        PlayLayer::onQuit();
    }
};