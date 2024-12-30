#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "saved.cpp"
#include <time.h>
#include <Geode/ui/Popup.hpp>
class LevTT : public geode::Popup<std::string const&, std::string const&> {
protected:
    CCSize winSize = CCDirector::get()->getWinSize();
	int kolumn = true + true + 1;
    float Width = (winSize.width / 1.5 - (kolumn+1) * 6) / kolumn;
    float Height = winSize.height / 1.5 - 36 - 8;

    std::map<std::string, LevDayGame> LevDayGamee;
    std::map<std::string, LevGameSes> LevGameSess;
    ScrollLayer* DayList = ScrollLayer::create({ Width, Height });
    ScrollLayer* GameList = ScrollLayer::create({ Width, Height });
    ScrollLayer* LevList = ScrollLayer::create({ Width, Height });
    bool setup(std::string const& Type, std::string const& ID) override {
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        auto Lev = Level[Type].Level[ID];
        this->setTitle(fmt::format("{}{}", formatTime(Lev.tPlayLev), formatAtt(Lev.attLev)));

        auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
        input->hideBG();
        input->setString(Lev.textLev);
        input->setCallback([Type, ID](std::string const& text) {
            auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
            Level[Type].Level[ID].textLev = text;
            Mod::get()->setSavedValue("Level", Level);
            Mod::get()->saveData();
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

        if (true) { LevTT::onButton(Type, ID); }
        if (true) { LevTT::onDButton(LevDayGamee, Type, ID); }
        if (true) { LevTT::onGButton(LevGameSess, Type, ID); }

        lists->addChild(DayList);
        lists->addChild(GameList);
        lists->addChild(LevList);
        lists->updateLayout();
        return true;
    }
    void onButton(std::string const& Type, std::string const& ID) {
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        auto Lev = Level[Type].Level[ID];
        for (const auto& [LevDayKey, LevDayValue] : Lev.LevDay) {
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
            struct tm* time = localtime(&LevDayValue.stLevDay);
            LevDayGamee = LevDayValue.LevDayGame;
            std::string S[7] = { "Sun", "Mon", "Tus", "Wed", "Thu", "Fri", "Sat" };
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{} {} - {}\n{}{}", S[time->tm_wday], time->tm_mday, LevDayGamee.size(), formatTime(LevDayValue.tPlayLevDay), formatAtt(LevDayValue.attLevDay)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this, LevDayKey, Type, ID](auto) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                auto Lev = Level[Type].Level[ID];
                LevTT::onDButton(Lev.LevDay[LevDayKey].LevDayGame, Type, ID);
                });
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(LevDayValue.textLevDay);
            input->setCallback([LevDayKey, Type, ID](std::string const& text) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                auto Lev = Level[Type].Level[ID];
                Lev.LevDay[LevDayKey].textLevDay = text;
                Mod::get()->setSavedValue("Level", Level);
                Mod::get()->saveData();
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
    void onDButton(std::map<std::string, LevDayGame>& LevDayGamee, std::string const& Type, std::string const& ID) {
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        auto Lev = Level[Type].Level[ID];
        GameList->m_contentLayer->removeAllChildren();
        for (const auto& [LevDayGameKey, LevDayGameValue] : LevDayGamee) {
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
            auto LevGame = Lev.LevGame[std::to_string(LevDayGameValue.stLevDayGame)];
            struct tm* timest = localtime(&LevGame.stGameSes);
            int sth = timest->tm_hour;
            int stm = timest->tm_min;
            struct tm* timeend = localtime(&LevGame.endLevGame);
            LevGameSess = LevGame.LevGameSes;
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{:02}:{:02}-{:02}:{:02} - {}\n{}{}", sth, stm, timeend->tm_hour, timeend->tm_min, LevGameSess.size(), formatTime(LevGame.tPlayLevGame), formatAtt(LevGame.attLevGame)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this, LevDayGameValue, Type, ID](auto) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                LevTT::onGButton(Level[Type].Level[ID].LevGame[std::to_string(LevDayGameValue.stLevDayGame)].LevGameSes, Type, ID);
                });
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(LevGame.textLevGame);
            input->setCallback([LevDayGameValue, Type, ID](std::string const& text) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                Level[Type].Level[ID].LevGame[std::to_string(LevDayGameValue.stLevDayGame)].textLevGame = text;
                Mod::get()->setSavedValue("Level", Level);
                Mod::get()->saveData();
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
    void onGButton(std::map<std::string, LevGameSes> LevGameSess, std::string const& Type, std::string const& ID) {
        auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
        auto Lev = Level[Type].Level[ID];
        LevList->m_contentLayer->removeAllChildren();
        for (const auto& [GameSesKey, GameSesValue] : LevGameSess) {
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
            auto LevSes = Lev.LevSes[std::to_string(GameSesValue.stGameSes)];
            struct tm* timest = localtime(&LevSes.stLevSes);
            int sth = timest->tm_hour;
            int stm = timest->tm_min;
            struct tm* timeend = localtime(&LevSes.endLevSes);
            auto text = cocos2d::CCLabelBMFont::create(fmt::format("{:02}:{:02}-{:02}:{:02}\n{}{}", sth, stm, timeend->tm_hour, timeend->tm_min, formatTime(LevSes.tPlayLevSes), formatAtt(LevSes.attLevSes)).c_str(), "chatFont.fnt");
            auto input = TextInput::create(Width / 1.5, "", "chatFont.fnt");
            auto Button = CCMenuItemExt::createSpriteExtraWithFrameName("navArrowBtn_001.png", 0.5f, [this](auto) {});
            Button->setVisible(false);
            text->setScale(0.5);
            input->setContentHeight(16.5);
            input->hideBG();
            input->setString(LevSes.textLevSes);
            input->setCallback([GameSesValue, Type, ID](std::string const& text) {
                auto Level = Mod::get()->getSavedValue<std::map<std::string, Levels>>("Level", {});
                Level[Type].Level[ID].LevSes[std::to_string(GameSesValue.stGameSes)].textLevSes = text;
                Mod::get()->setSavedValue("Level", Level);
                Mod::get()->saveData();
                });
            input->setTextAlign(TextInputAlign::Left);
            LevList->m_contentLayer->addChild(Menu);
            Menu->addChild(text);
            Menu->addChild(input);
            Menu->addChild(Button);
            Menu->setContentWidth(Width);
            Menu->setContentHeight(33);
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

        long long time = long long(ceil(ttime));
        std::string text;
        if (time >= 3600) text += std::to_string(int(time / 3600)) + "h";
        if (time >= 60) text += std::to_string(int(time % 3600 / 60)) + "m";
        text += std::to_string(int(time % 60)) + "s ";
        return text;
    }
    std::string formatAtt(int att) {
        //std::string text;
        //if (att) text = std::to_string(att) + "att";
        //return text;

        std::string text;
        return text + std::to_string(att) + "att";
    }
public:
    static LevTT* create(std::string const& Type, std::string const& ID) {
        auto ret = new LevTT();
        auto winSize = CCDirector::get()->getWinSize();
        int kolumn = true + true + 1;
        if (ret->initAnchored((winSize.width / 1.5 - 4 * 6) / 3 * kolumn + 6 * (kolumn + 1), winSize.height / 1.5, Type, ID)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};