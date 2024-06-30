#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;


class utMenuBackground : public CCLayer {
public:
    static utMenuBackground* create();
private:
    bool init();
    int selectedGamemode(IconType type);
    SimplePlayer* curPlayer(int iconIndex, IconType gamemode);
    void createIcons(CCLayer* layer);
};