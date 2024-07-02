#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class utButton: public CCMenuItemSpriteExtra {

public:
    static utButton* create(gd::string bttnText, CCObject* target, SEL_MenuHandler callback, std::string id, CCMenu* menu);
    void selected();
    void unselected();
    void activate();

};