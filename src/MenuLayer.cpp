#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "saved.cpp"
#include "GameTT.cpp"
#include <time.h>
#include <Geode/modify/MenuLayer.hpp>
inline time_t stGame;
inline long long stDay;
class $modify(D4MLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        if (!Mod::get()->hasSavedValue("Tot")) {
            Mod::get()->setSavedValue("Tot", Total{});
            Mod::get()->saveData();
        }
        static bool isStart = false;
        if (!isStart) {
            //кнопка чтоб убрать краши
            stGame = time(NULL);
            isStart = true;

            struct tm* stGtm = localtime(&stGame);
            stDay = stGame - stGtm->tm_hour * 3600 - stGtm->tm_min * 60 - stGtm->tm_sec;
            auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
            Day[std::to_string(stDay)].stDay = stDay;

            Day[std::to_string(stDay)].DayGame[std::to_string(stGame)] = DayGame{
                .stDayGame = stGame };

            auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
            Game[std::to_string(stGame)] = Games{
                .stGame = stGame };

            Mod::get()->setSavedValue("Day", Day);
            Mod::get()->setSavedValue("Game", Game);
            Mod::get()->saveData();
        }
        auto D4Mbutton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_statsBtn_001.png"),
            this,
            menu_selector(D4MLayer::onD4MMenu));
        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(D4Mbutton);

        //this->removeChildByID("social-media-menu");
        //this->getChildByID("profile-menu")->setPositionY(45);
        //this->getChildByID("player-username")->setPositionY(45 + 36);
        //this->getChildByID("more-games-menu")->removeChildByID("more-games-button");
        //this->getChildByID("bottom-menu")->removeChildByID("newgrounds-button");
        //static_cast<AxisLayout*>(this->getChildByID("right-side-menu")->getLayout())->setAxisAlignment(AxisAlignment::Start);
        //this->getChildByID("right-side-menu")->setPositionY(114);
        //this->getChildByID("right-side-menu")->updateLayout();
        menu->updateLayout();
        return true;
    }
    void onD4MMenu(CCObject*) {
        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        Game[std::to_string(stGame)].endGame = time(NULL);
        Mod::get()->setSavedValue("Game", Game);
        Mod::get()->saveData();
        GameTT::create()->show();

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
#include <Geode/modify/AppDelegate.hpp>
class $modify(AppDelegate) {
    void trySaveGame(bool p0) {
        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        Game[std::to_string(stGame)].endGame = time(NULL);
        Mod::get()->setSavedValue("Game", Game);
        Mod::get()->saveData();
        if (Game[std::to_string(stGame)].GameSes.empty()) {
            auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
            auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});

            Day[std::to_string(stDay)].DayGame.erase(std::to_string(stGame));
            Game.erase(std::to_string(stGame));

            Mod::get()->setSavedValue("Day", Day);
            Mod::get()->setSavedValue("Game", Game);
            Mod::get()->saveData();
        }
        auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
        if (Day[std::to_string(stDay)].DayGame.empty()) {
            auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
            Day.erase(std::to_string(stDay));
            Mod::get()->setSavedValue("Day", Day);
            Mod::get()->saveData();
        }
        AppDelegate::trySaveGame(p0);
    }
};