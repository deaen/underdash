#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;


class utMenuBackground : public CCLayer {
public:
    static utMenuBackground* create();
private:
    bool init();
    int iconIndex(IconType type);
    SimplePlayer* curPlayer();

};