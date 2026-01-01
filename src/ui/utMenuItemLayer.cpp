#include "utMenuItemLayer.hpp"

utMenuItemLayer* utMenuItemLayer::create(CCNode* target, SEL_MenuHandler showClassicMenu) {
    auto ret = new utMenuItemLayer();
    if (ret && ret->init(target, showClassicMenu)) {
        ret->autorelease();
    }
    else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool utMenuItemLayer::init(CCNode* target, SEL_MenuHandler showClassicMenu) {

    this->setID("UtMenuItemLayer"_spr);
    this->setLayout(
    AxisLayout::create()
        ->setAxisAlignment(AxisAlignment::Center)
        ->setAxis(Axis::Column)
    );

    this->addChild(createItemMenu(target, showClassicMenu));
    this->addChild(createExtraMenu(target));


    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(winSize.width / 2, (winSize.height / 2) + 10.f);
    this->setContentSize(winSize);
    this->updateLayout();
    return true;
}

CCMenu* utMenuItemLayer::createItemMenu(CCNode* target, SEL_MenuHandler showClassicMenu) {
    auto menu = CCMenu::create();
    menu->setLayout(
        AxisLayout::create()
        ->setGap(20.f)
        ->setAxisAlignment(AxisAlignment::Center)
        ->setAxis(Axis::Row)
        ->setGrowCrossAxis(true)
        ->setCrossAxisOverflow(false)
    );
    auto menuSize = CCSize(200, 100);
    menu->setContentSize(menuSize);
    menu->setID("ut-item-menu"_spr);

    utButton::create("Icon kit", target, menu_selector(MenuLayer::onGarage), "ut-icon-kit-button"_spr, menu);
    utButton::create("Online", target, menu_selector(MenuLayer::onCreator), "ut-online-button"_spr, menu);
    utButton::create("Play", target, menu_selector(MenuLayer::onPlay), "ut-play-button"_spr, menu);
    utButton::create("Settings", target, menu_selector(MenuLayer::onOptions), "ut-options-button"_spr, menu);
    utButton::create("More", target, showClassicMenu, "ut-classic-button"_spr, menu);
    menu->updateLayout();

    return menu;
}

CCMenu* utMenuItemLayer::createExtraMenu(CCNode* target) {
    auto menu = CCMenu::create();
    auto menuLayout = AxisLayout::create()
        ->setAxisAlignment(AxisAlignment::Center)
        ->setAxis(Axis::Row)
        ->setGap(60.f)
        ->setDefaultScaleLimits(0.f, 0.9f)
        ->setGrowCrossAxis(true);
    menu->setLayout(menuLayout);
    menu->setID("ut-extra-menu"_spr);
    menu->setContentWidth(CCDirector::sharedDirector()->getWinSize().width - 50);

    if (Mod::get()->getSettingValue<bool>("profile")) utButton::create(GameManager::sharedState()->m_playerName, target, menu_selector(MenuLayer::onMyProfile), "ut-profile-button"_spr, menu);

    if (typeinfo_cast<CCMenuItem*>(target->getChildByIDRecursive("geode.loader/geode-button")) != nullptr && Mod::get()->getSettingValue<bool>("geode")) {
        auto geodeSelector = typeinfo_cast<CCMenuItem*>(target->getChildByIDRecursive("geode.loader/geode-button"))->m_pfnSelector;
        utButton::create("Geode", target, geodeSelector, "ut-geode-button"_spr, menu);
    }
    if (typeinfo_cast<CCMenuItem*>(target->getChildByIDRecursive("dankmeme.globed2/main-menu-button")) != nullptr && Mod::get()->getSettingValue<bool>("globed")) {
        auto globedSelector = typeinfo_cast<CCMenuItem*>(target->getChildByIDRecursive("dankmeme.globed2/main-menu-button"))->m_pfnSelector;
        utButton::create("Globed", target, globedSelector, "ut-globed-button"_spr, menu);
    }
    if (Mod::get()->getSettingValue<bool>("achievements")) utButton::create("Achievements", target, menu_selector(MenuLayer::onAchievements), "ut-achievements-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("stats")) utButton::create("Stats", target, menu_selector(MenuLayer::onStats), "ut-stats-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("search")) utButton::create("Search", target, menu_selector(CreatorLayer::onOnlineLevels), "ut-search-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("saved")) utButton::create("Saved", target, menu_selector(CreatorLayer::onSavedLevels), "ut-saved-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("create")) utButton::create("Create", target, menu_selector(CreatorLayer::onMyLevels), "ut-create-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("featured")) utButton::create("Featured", target, menu_selector(CreatorLayer::onFeaturedLevels), "ut-featured-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("daily")) utButton::create("Daily", target, menu_selector(CreatorLayer::onDailyLevel), "ut-daily-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("weekly")) utButton::create("Weekly", target, menu_selector(CreatorLayer::onWeeklyLevel), "ut-weekly-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("chests")) utButton::create("Chests", target, menu_selector(MenuLayer::onDaily), "ut-chests-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("quit")) utButton::create("Quit", target, menu_selector(MenuLayer::onQuit), "ut-quit-button"_spr, menu);
    if (Mod::get()->getSettingValue<bool>("restart")) utButton::create("Restart", target, menu_selector(utMenuItemLayer::onUtRestart), "ut-restart-button"_spr, menu);
   
    menu->updateLayout();
    
    if (menu->getContentHeight() > 70) {
        menu->setLayout(menuLayout->setGap(17.f));
        menu->setContentWidth(CCDirector::sharedDirector()->getWinSize().width - 15);
        menu->updateLayout();
    }
    else if (menu->getContentHeight() > 20) {
        menu->setLayout(menuLayout->setGap(30.f));
        menu->updateLayout();
    }
    return menu;
}

void utMenuItemLayer::onUtRestart(CCObject* sender){
    geode::createQuickPopup("Restart Game",
        "Are you sure you want to <cg>restart</c>?",
        "Cancel", "Yes",
        [](auto, bool btn2) {
            if (btn2) {
            game::restart(true);
            }
        }
    );
}