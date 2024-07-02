#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;


class utMenuItemLayer : public CCLayer {
public:
    static utMenuItemLayer* create(CCNode* target, SEL_MenuHandler showClassicMenu);
private:
    bool init(CCNode* target, SEL_MenuHandler showClassicMenu);
    CCMenu* createItemMenu(CCNode* target, SEL_MenuHandler showClassicMenu);
    CCMenu* createExtraMenu(CCNode* target);
};