#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "saved.hpp"
#include <time.h>
#include <Geode/ui/Popup.hpp>
class GameTT : public geode::Popup<> {
protected:
    CCSize winSize = CCDirector::get()->getWinSize();
    int kolumn = true + true + 1;
    float Width = (winSize.width / 1.5 - (kolumn+1) * 6) / kolumn;
    float Height = winSize.height / 1.5 - 36 - 8;

    std::map<std::string, DayGame> DayGamee;
    std::map<std::string, GameSes> GameSess;
    ScrollLayer* DayList = ScrollLayer::create({ Width, Height });
    ScrollLayer* GameList = ScrollLayer::create({ Width, Height });
    ScrollLayer* LevList = ScrollLayer::create({ Width, Height });
    bool setup() override {
        auto Tot = Mod::get()->getSavedValue<Total>("Tot");
        this->setTitle(fmt::format("{}{}", formatTime(Tot.tPlayTot), formatAtt(Tot.attTot)));

        auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
        input->hideBG();
        input->setString(Tot.textTot);
        input->setCallback([](std::string const& text) {
            auto Tot = Mod::get()->getSavedValue<Total>("Tot");
            Tot.textTot = text;
            Mod::get()->setSavedValue("Tot", Tot);
            });
        m_mainLayer->addChildAtPosition(input, Anchor::Top, { 0, -10 });

        auto lists = CCNode::create();;
        m_mainLayer->addChild(lists);
        lists->setPosition({ 6,8 });
        lists->setContentHeight(Height);
        lists->setLayout(
            ColumnLayout::create()
            ->setGrowCrossAxis(true)
            ->setCrossAxisAlignment(AxisAlignment::Between)
            ->setCrossAxisReverse(true)
            ->setGap(6.0f)
        );

        DayList->m_contentLayer->setLayout(
            ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(Height)
            ->setGap(6.0f)
        );
        GameList->m_contentLayer->setLayout(
            ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(Height)
            ->setGap(6.0f)
        );
        LevList->m_contentLayer->setLayout(
            ColumnLayout::create()
            ->setAxisAlignment(AxisAlignment::End)
            ->setAutoGrowAxis(Height)
            ->setGap(6.0f)
        );

        if (true) { GameTT::onButton(); }
        if (true) { GameTT::onDButton(DayGamee); }
        if (true) { GameTT::onGButton(GameSess); }

        lists->addChild(DayList);
        lists->addChild(GameList);
        lists->addChild(LevList);
        lists->updateLayout();
        return true;
    }
    void onButton() {
        auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
        DayList->m_contentLayer->removeAllChildren();
        for (const auto& [DayKey, DayValue] : Day) {
            auto Menu = CCMenu::create();
            Menu->setLayout(ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisLineAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
                ->setCrossAxisReverse(true)
                ->setGrowCrossAxis(true)
                ->setAutoScale(false)
                ->setCrossAxisOverflow(false)
            );
            Menu->setAnchorPoint({ 0, 0 });
            struct tm time = fmt::localtime(DayValue.stDay);
            DayGamee = DayValue.DayGame;
            std::string S[7] = { "Sun", "Mon", "Tus", "Wed", "Thu", "Fri", "Sat" };
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{} {} - {}\n{}{}", S[time.tm_wday], time.tm_mday, DayGamee.size(), formatTime(DayValue.tPlayDay), formatAtt(DayValue.attDay)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this, DayKey](auto) {
                auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
                GameTT::onDButton(Day[DayKey].DayGame);
                });
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(DayValue.textDay);
            input->setCallback([DayKey](std::string const& text) {
                auto Day = Mod::get()->getSavedValue<std::map<std::string, Days>>("Day", {});
                Day[DayKey].textDay = text;
                Mod::get()->setSavedValue("Day", Day);
                });
            input->setTextAlign(TextInputAlign::Left);
            DayList->m_contentLayer->addChild(Menu);
            Menu->addChild(text);
            Menu->addChild(input);
            Menu->addChild(Button);
            Menu->setContentWidth(Width);
            Menu->setContentHeight(33);
            Menu->updateLayout();
        };
        DayList->m_contentLayer->updateLayout();
        DayList->scrollToTop();
    }
    void onDButton(std::map<std::string, DayGame>& DayGamee) {
        auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
        GameList->m_contentLayer->removeAllChildren();
        for (const auto& [LevDayGameKey, LevDayGameValue] : DayGamee) {
            auto Menu = CCMenu::create();
            Menu->setLayout(ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisLineAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
                ->setCrossAxisReverse(true)
                ->setGrowCrossAxis(true)
                ->setAutoScale(false)
                ->setCrossAxisOverflow(false)
            );
            Menu->setAnchorPoint({ 0, 0 });
            auto DayGame = Game[std::to_string(LevDayGameValue.stDayGame)];
            struct tm timest = fmt::localtime(DayGame.stGame);
            int sth = timest.tm_hour;
            int stm = timest.tm_min;
            struct tm timeend = fmt::localtime(DayGame.endGame);
            GameSess = DayGame.GameSes;
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{:02}:{:02}-{:02}:{:02} - {}\n{}{}", sth, stm, timeend.tm_hour, timeend.tm_min, GameSess.size(), formatTime(DayGame.tPlayGame), formatAtt(DayGame.attGame)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this, LevDayGameValue](auto) {
                auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
                GameTT::onGButton(Game[std::to_string(LevDayGameValue.stDayGame)].GameSes);
                });
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(DayGame.textGame);
            input->setCallback([LevDayGameValue](std::string const& text) {
                auto Game = Mod::get()->getSavedValue<std::map<std::string, Games>>("Game", {});
                Game[std::to_string(LevDayGameValue.stDayGame)].textGame = text;
                Mod::get()->setSavedValue("Game", Game);
                });
            input->setTextAlign(TextInputAlign::Left);
            GameList->m_contentLayer->addChild(Menu);
            Menu->addChild(text);
            Menu->addChild(input);
            Menu->addChild(Button);
            Menu->setContentWidth(Width);
            Menu->setContentHeight(33);
            Menu->updateLayout();
        }
        GameList->m_contentLayer->updateLayout();
        GameList->scrollToTop();
    };
    void onGButton(std::map<std::string, GameSes> GameSess){
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        LevList->m_contentLayer->removeAllChildren();
        for (const auto& [GameSesKey, GameSesValue] : GameSess) {
            auto Menu = CCMenu::create();
            Menu->setLayout(ColumnLayout::create()
                ->setAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisLineAlignment(AxisAlignment::Start)
                ->setAxisReverse(true)
                ->setCrossAxisReverse(true)
                ->setGrowCrossAxis(true)
                ->setAutoScale(false)
                ->setCrossAxisOverflow(false)
            );
            Menu->setAnchorPoint({ 0, 0 });
            auto Lev = Level[GameSesValue.TypeGameLev].Level[std::to_string(GameSesValue.IDGameLev)];
            auto LevSes = Lev.LevSes[std::to_string(GameSesValue.stGameSes)];
            struct tm timest = fmt::localtime(LevSes.stLevSes);
            int sth = timest.tm_hour;
            int stm = timest.tm_min;
            struct tm timeend = fmt::localtime(LevSes.endLevSes);
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{} {}\n{:02}:{:02}-{:02}:{:02}\n{}{}", Lev.nameLev, Lev.IDLev, sth, stm, timeend.tm_hour, timeend.tm_min, formatTime(LevSes.tPlayLevSes), formatAtt(LevSes.attLevSes)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this](auto) {});
            Button->setVisible(false);
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(LevSes.textLevSes);
            input->setCallback([GameSesValue](std::string const& text) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                Level[GameSesValue.TypeGameLev].Level[std::to_string(GameSesValue.IDGameLev)].LevSes[std::to_string(GameSesValue.stGameSes)].textLevSes = text;
                Mod::get()->setSavedValue("Level", Level);
                });
            input->setTextAlign(TextInputAlign::Left);
            LevList->m_contentLayer->addChild(Menu);
            Menu->addChild(text);
            Menu->addChild(input);
            Menu->addChild(Button);
            Menu->setContentWidth(Width);
            Menu->setContentHeight(8.25 * 3 + 16.5);
            Menu->updateLayout();
        }
        LevList->m_contentLayer->updateLayout();
        LevList->scrollToTop();
    }
    std::string formatTime(double ttime) {
        //if (!ttime) { return ""; }
        //if (ttime < 0) { ttime *= -1; }
        //long long time = long long(ceil(ttime));
        //std::string text;
        //if (time >= 3600) {
        //    text += std::to_string(int(time / 3600)) + "h";
        //}
        //if (time >= 60) {
        //    text += std::to_string(int(time % 3600 / 60)) + "m";
        //}
        //if (time < 3600 && time > 0) {
        //    text += std::to_string(int(time%60)) + "s";
        //}
        //text += " ";
        //return text;

        long long time = (long long)ceil(ttime);
        std::string text;
        if (time >= 3600) text += std::to_string(int(time / 3600)) + "h";
        if (time >= 60) text += std::to_string(int(time % 3600 / 60)) + "m";
        text += std::to_string(int(time % 60)) + "s ";
        return text;
    }
    std::string formatAtt(int att) {
        //std::string text;
        //if (att) text = std::to_string(att)+"att";
        //return text;

        std::string text;
        return text + std::to_string(att) + "att";
    }
public:
    static GameTT* create() {
        auto ret = new GameTT();
        auto winSize = CCDirector::get()->getWinSize();
        int kolumn = true + true + 1;
        if (ret->initAnchored((winSize.width / 1.5 - 4*6) / 3 * kolumn + 6*(kolumn +1), winSize.height / 1.5)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};