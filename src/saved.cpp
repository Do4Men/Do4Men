#pragma once
#include <Geode/Geode.hpp>
#include <matjson.hpp>
#include <matjson/std.hpp>
#include <matjson/stl_serialize.hpp>
using namespace geode::prelude;
struct Total {
    double tPlayTot;
    double tBuildTot;
    int attTot;
    std::string textTot;
};
struct GameSes {
    long long stGameSes;
    int IDGameLev;
    std::string TypeGameLev;
};
struct Games {
    long long stGame;
    long long endGame;
    double tPlayGame;
    double tBuildGame;
    int attGame;
    std::string textGame;
    std::map<std::string, GameSes> GameSes;
};
struct DayGame {
    long long stDayGame;
};
struct Days {
    long long stDay;
    double tPlayDay;
    double tBuildDay;
    int attDay;
    std::string textDay;
    std::map<std::string, DayGame> DayGame;
};

struct LevDayGame {
    long long stLevDayGame;
};
struct LevDay {
    long long stLevDay;
    double tPlayLevDay;
    double tBuildLevDay;
    int attLevDay;
    std::string textLevDay;
    std::map<std::string, LevDayGame> LevDayGame;
};
struct LevGameSes {
    long long stGameSes;
};
struct LevGame {
    long long stGameSes;
    long long endLevGame;
    double tPlayLevGame;
    double tBuildLevGame;
    int attLevGame;
    std::string textLevGame;
    std::map<std::string, LevGameSes> LevGameSes;
};
struct LevSes {
    long long stLevSes;
    long long endLevSes;
    double tPlayLevSes;
    double tBuildLevSes;
    int attLevSes;
    std::string textLevSes;
};
struct Level {
    int IDLev;
    std::string nameLev;
    double tPlayLev;
    double tBuildLev;
    int attLev;
    std::string textLev;
    std::map<std::string, LevDay> LevDay;
    std::map<std::string, LevGame> LevGame;
    std::map<std::string, LevSes> LevSes;
};
struct Levels {
    std::map<std::string, Level> Level;
};
template<>
struct matjson::Serialize<Total> {
    static geode::Result<Total> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(double tPlayTot, value["tPlayTot"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildTot, value["tBuildTot"].asDouble());
        GEODE_UNWRAP_INTO(int attTot, value["attTot"].asInt());
        GEODE_UNWRAP_INTO(std::string textTot, value["textTot"].asString());
        return geode::Ok(Total{ tPlayTot, tBuildTot, attTot, textTot });
    }
    static matjson::Value toJson(const Total& value) {
        return matjson::makeObject({
            {"tPlayTot", value.tPlayTot},
            {"tBuildTot", value.tBuildTot},
            {"attTot", value.attTot},
            {"textTot", value.textTot}
            });
    }
};
template<>
struct matjson::Serialize<GameSes> {
    static geode::Result<GameSes> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stGameSes, value["stGameSes"].asInt());
        GEODE_UNWRAP_INTO(int IDGameLev, value["IDGameLev"].asInt());
        GEODE_UNWRAP_INTO(std::string TypeGameLev, value["TypeGameLev"].asString());
        return geode::Ok(GameSes{ stGameSes, IDGameLev, TypeGameLev });
    }
    static matjson::Value toJson(const GameSes& value) {
        return matjson::makeObject({
            {"stGameSes", value.stGameSes},
            {"IDGameLev", value.IDGameLev},
            {"TypeGameLev", value.TypeGameLev}
            });
    }
};
template<>
struct matjson::Serialize<Games> {
    static geode::Result<Games> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stGame, value["stGame"].asInt());
        GEODE_UNWRAP_INTO(long long endGame, value["endGame"].asInt());
        GEODE_UNWRAP_INTO(double tPlayGame, value["tPlayGame"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildGame, value["tBuildGame"].asDouble());
        GEODE_UNWRAP_INTO(int attGame, value["attGame"].asInt());
        GEODE_UNWRAP_INTO(std::string textGame, value["textGame"].asString());
        GEODE_UNWRAP_INTO(std::map GameSes, value["GameSes"].as<std::map<std::string, GameSes>>());
        return geode::Ok(Games{ stGame, endGame, tPlayGame, tBuildGame, attGame, textGame, GameSes });
    }
    static matjson::Value toJson(const Games& value) {
        return matjson::makeObject({
            {"stGame", value.stGame},
            {"endGame", value.endGame},
            {"tPlayGame", value.tPlayGame},
            {"tBuildGame", value.tBuildGame},
            {"attGame", value.attGame},
            {"textGame", value.textGame},
            {"GameSes", value.GameSes}
            });
    }
};
template<>
struct matjson::Serialize<DayGame> {
    static geode::Result<DayGame> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stDayGame, value["stDayGame"].asInt());
        return geode::Ok(DayGame{ stDayGame });
    }
    static matjson::Value toJson(const DayGame& value) {
        return matjson::makeObject({
            {"stDayGame", value.stDayGame}
            });
    }
};
template<>
struct matjson::Serialize<Days> {
    static geode::Result<Days> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stDay, value["stDay"].asInt());
        GEODE_UNWRAP_INTO(double tPlayDay, value["tPlayDay"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildDay, value["tBuildDay"].asDouble());
        GEODE_UNWRAP_INTO(int attDay, value["attDay"].asInt());
        GEODE_UNWRAP_INTO(std::string textDay, value["textDay"].asString());
        GEODE_UNWRAP_INTO(std::map DayGame, value["DayGame"].as<std::map<std::string, DayGame>>());
        return geode::Ok(Days{ stDay, tPlayDay, tBuildDay, attDay, textDay, DayGame });
    }
    static matjson::Value toJson(const Days& value) {
        return matjson::makeObject({
            {"stDay", value.stDay},
            {"tPlayDay", value.tPlayDay},
            {"tBuildDay", value.tBuildDay},
            {"attDay", value.attDay},
            {"textDay", value.textDay},
            {"DayGame", value.DayGame}
            });
    }
};
template<>
struct matjson::Serialize<LevDayGame> {
    static geode::Result<LevDayGame> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stLevDayGame, value["stLevDayGame"].asInt());
        return geode::Ok(LevDayGame{ stLevDayGame });
    }
    static matjson::Value toJson(const LevDayGame& value) {
        return matjson::makeObject({
            {"stLevDayGame", value.stLevDayGame}
            });
    }
};
template<>
struct matjson::Serialize<LevDay> {
    static geode::Result<LevDay> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stLevDay, value["stLevDay"].asInt());
        GEODE_UNWRAP_INTO(double tPlayLevDay, value["tPlayLevDay"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildLevDay, value["tBuildLevDay"].asDouble());
        GEODE_UNWRAP_INTO(int attLevDay, value["attLevDay"].asInt());
        GEODE_UNWRAP_INTO(std::string textLevDay, value["textLevDay"].asString());
        GEODE_UNWRAP_INTO(std::map LevDayGame, value["LevDayGame"].as<std::map<std::string, LevDayGame>>());
        return geode::Ok(LevDay{ stLevDay, tPlayLevDay,tBuildLevDay, attLevDay, textLevDay, LevDayGame });
    }
    static matjson::Value toJson(const LevDay& value) {
        return matjson::makeObject({
            {"stLevDay", value.stLevDay},
            {"tPlayLevDay", value.tPlayLevDay},
            {"tBuildLevDay", value.tBuildLevDay},
            {"attLevDay", value.attLevDay},
            {"textLevDay", value.textLevDay},
            {"LevDayGame", value.LevDayGame}
            });
    }
};
template<>
struct matjson::Serialize<LevGameSes> {
    static geode::Result<LevGameSes> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stGameSes, value["stGameSes"].asInt());
        return geode::Ok(LevGameSes{ stGameSes });
    }
    static matjson::Value toJson(const LevGameSes& value) {
        return matjson::makeObject({
            {"stGameSes", value.stGameSes}
            });
    }
};
template<>
struct matjson::Serialize<LevGame> {
    static geode::Result<LevGame> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stGameSes, value["stGameSes"].asInt());
        GEODE_UNWRAP_INTO(long long endLevGame, value["endLevGame"].asInt());
        GEODE_UNWRAP_INTO(double tPlayLevGame, value["tPlayLevGame"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildLevGame, value["tBuildLevGame"].asDouble());
        GEODE_UNWRAP_INTO(int attLevGame, value["attLevGame"].asInt());
        GEODE_UNWRAP_INTO(std::string textLevGame, value["textLevGame"].asString());
        GEODE_UNWRAP_INTO(std::map LevGameSes, value["LevGameSes"].as<std::map<std::string, LevGameSes>>());
        return geode::Ok(LevGame{ stGameSes, endLevGame, tPlayLevGame, tBuildLevGame, attLevGame, textLevGame, LevGameSes });
    }
    static matjson::Value toJson(const LevGame& value) {
        return matjson::makeObject({
            {"stGameSes", value.stGameSes},
            {"endLevGame", value.endLevGame},
            {"tPlayLevGame", value.tPlayLevGame},
            {"tBuildLevGame", value.tBuildLevGame},
            {"attLevGame", value.attLevGame},
            {"textLevGame", value.textLevGame},
            {"LevGameSes", value.LevGameSes}
            });
    }
};
template<>
struct matjson::Serialize<LevSes> {
    static geode::Result<LevSes> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(long long stLevSes, value["stLevSes"].asInt());
        GEODE_UNWRAP_INTO(long long endLevSes, value["endLevSes"].asInt());
        GEODE_UNWRAP_INTO(double tPlayLevSes, value["tPlayLevSes"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildLevSes, value["tBuildLevSes"].asDouble());
        GEODE_UNWRAP_INTO(int attLevSes, value["attLevSes"].asInt());
        GEODE_UNWRAP_INTO(std::string textLevSes, value["textLevSes"].asString());
        return geode::Ok(LevSes{ stLevSes, endLevSes, tPlayLevSes,tBuildLevSes, attLevSes, textLevSes });
    }
    static matjson::Value toJson(const LevSes& value) {
        return matjson::makeObject({
            {"stLevSes", value.stLevSes},
            {"endLevSes", value.endLevSes},
            {"tPlayLevSes", value.tPlayLevSes},
            {"tBuildLevSes", value.tBuildLevSes},
            {"attLevSes", value.attLevSes},
            {"textLevSes", value.textLevSes}
            });
    }
};
template<>
struct matjson::Serialize<Level> {
    static geode::Result<Level> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(int IDLev, value["IDLev"].asInt());
        GEODE_UNWRAP_INTO(std::string nameLev, value["nameLev"].asString());
        GEODE_UNWRAP_INTO(double tPlayLev, value["tPlayLev"].asDouble());
        GEODE_UNWRAP_INTO(double tBuildLev, value["tBuildLev"].asDouble());
        GEODE_UNWRAP_INTO(int attLev, value["attLev"].asInt());
        GEODE_UNWRAP_INTO(std::string textLev, value["textLev"].asString());
        GEODE_UNWRAP_INTO(std::map LevDay, value["LevDay"].as<std::map<std::string, LevDay>>());
        GEODE_UNWRAP_INTO(std::map LevGame, value["LevGame"].as<std::map<std::string, LevGame>>());
        GEODE_UNWRAP_INTO(std::map LevSes, value["LevSes"].as<std::map<std::string, LevSes>>());
        return geode::Ok(Level{ IDLev, nameLev, tPlayLev, tBuildLev, attLev, textLev, LevDay, LevGame, LevSes });
    }
    static matjson::Value toJson(const Level& value) {
        return matjson::makeObject({
            {"IDLev", value.IDLev},
            {"nameLev", value.nameLev},
            {"tPlayLev", value.tPlayLev},
            {"tBuildLev", value.tBuildLev},
            {"attLev", value.attLev},
            {"textLev", value.textLev},
            {"LevDay", value.LevDay},
            {"LevGame", value.LevGame},
            {"LevSes", value.LevSes}
            });
    }
};
template<>
struct matjson::Serialize<Levels> {
    static geode::Result<Levels> fromJson(const matjson::Value& value) {
        GEODE_UNWRAP_INTO(std::map Level, value["Level"].as<std::map<std::string, Level>>());
        return geode::Ok(Levels{ Level });
    }
    static matjson::Value toJson(const Levels& value) {
        return matjson::makeObject({
            {"Level", value.Level}
            });
    }
};