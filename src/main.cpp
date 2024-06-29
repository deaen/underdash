#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include "ui/utMenuBackground.hpp"
using namespace geode::prelude;

bool showUtMenu = true;
class $modify(MyMenuLayer, MenuLayer) {

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        createUtMenu();

        return true;
    }

    void createUtMenu() {
        // CREATE CLASSIC MENU BUTTON //
        auto utMenuButton = CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSprite("soul.png"_spr, 0.9f), this, menu_selector(MyMenuLayer::onShowUtMenu));
        auto menu = this->getChildByID("bottom-menu");
        menu->addChild(utMenuButton);
        utMenuButton->setID("utMenuButton"_spr);
        menu->updateLayout();

        // HIDE CLASSIC MENU AND CREATE UT MENU
        onShowUtMenu();
        if (this->getChildByID("UtMenuBackground"_spr) == nullptr) this->addChild(utMenuBackground::create());
        createItemMenu();
    }

    void onShowUtMenu(CCObject * = nullptr) {
        CCObject* obj;
        CCARRAY_FOREACH(this -> getChildren(), obj) {
            auto item = typeinfo_cast<CCNode*>(obj);
            if (item != nullptr) item->setVisible(false);
        }
        if (this->getChildByID("UtMenuBackground"_spr) != nullptr) this->getChildByID("UtMenuBackground"_spr)->setVisible(true);
        if (this->getChildByID("ut-item-menu"_spr) != nullptr) this->getChildByID("ut-item-menu"_spr)->setVisible(true);
        if (this->getChildByID("ut-extra-menu"_spr) != nullptr) this->getChildByID("ut-extra-menu"_spr)->setVisible(true);
    }

    void onShowClassicMenu(CCObject * = nullptr) {
        CCObject* obj;
        CCARRAY_FOREACH(this -> getChildren(), obj) {
            auto item = typeinfo_cast<CCNode*>(obj);
            if (item != nullptr) item->setVisible(true);
        }
        if (this->getChildByID("UtMenuBackground"_spr) != nullptr) this->getChildByID("UtMenuBackground"_spr)->setVisible(false);
        if (this->getChildByID("ut-item-menu"_spr) != nullptr) this->getChildByID("ut-item-menu"_spr)->setVisible(false);
        if (this->getChildByID("ut-extra-menu"_spr) != nullptr) this->getChildByID("ut-extra-menu"_spr)->setVisible(false);
    }

    void createItemMenu() {
        auto menu = CCMenu::create();
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        menu->setID("ut-item-menu"_spr);
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
        this->addChild(menu);

        auto utIconKitButton = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Icon Kit", "utFont.fnt"_spr), this, menu_selector(MenuLayer::onGarage));
        utIconKitButton->setID("ut-icon-kit-button"_spr);
        menu->addChild(utIconKitButton);

        auto utOnlineButton = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Online", "utFont.fnt"_spr), this, menu_selector(MenuLayer::onCreator));
        utOnlineButton->setID("ut-online-button"_spr);
        menu->addChild(utOnlineButton);

        auto utPlayButton = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Play", "utFont.fnt"_spr), this, menu_selector(MenuLayer::onPlay));
        utPlayButton->setID("ut-play-button"_spr);
        menu->addChild(utPlayButton);

        auto utOptionsButton = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Options", "utFont.fnt"_spr), this, menu_selector(MenuLayer::onOptions));
        utOptionsButton->setID("ut-options-button"_spr);
        menu->addChild(utOptionsButton);

        auto utMoreButton = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("More", "utFont.fnt"_spr), this, menu_selector(MyMenuLayer::onShowClassicMenu));
        utMoreButton->setID("ut-more-button"_spr);
        menu->addChild(utMoreButton);

        menu->updateLayout();
        menu->setPosition({winSize.width / 2, winSize.height / 2});

        auto extraMenu = CCMenu::create();
        extraMenu->setLayout(
            AxisLayout::create()
            ->setGap(60.f)
            ->setAxisAlignment(AxisAlignment::Center)
            ->setAxis(Axis::Row)
            ->setDefaultScaleLimits(0.f, 0.9f)
        );
        extraMenu->setID("ut-extra-menu"_spr);
        extraMenu->setPositionY(winSize.height - 90.f);
        this->addChild(extraMenu);

        auto name = CCMenuItemSpriteExtra::create(CCLabelBMFont::create(GameManager::sharedState()->m_playerName.c_str(), "utFont.fnt"_spr), this, menu_selector(MenuLayer::onMyProfile));
        name->setID("ut-player-button"_spr);
        extraMenu->addChild(name);

        auto geodeSelector = (this->getChildByIDRecursive("geode.loader/geode-button") != nullptr && typeinfo_cast<CCMenuItem*>(this->getChildByIDRecursive("geode.loader/geode-button")) != nullptr) ? typeinfo_cast<CCMenuItem*>(this->getChildByIDRecursive("geode.loader/geode-button"))->m_pfnSelector : nullptr;
        auto geode = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Geode", "utFont.fnt"_spr), this, geodeSelector);
        geode->setID("ut-geode-button"_spr);
        extraMenu->addChild(geode);

        auto daily = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("Daily", "utFont.fnt"_spr), this, menu_selector(MenuLayer::onDaily));
        daily->setID("ut-daily-button"_spr);
        extraMenu->addChild(daily);

        extraMenu->updateLayout();
    }
};



class $modify(GameManager) {
    void fadeInMenuMusic() {
        FMODAudioEngine::sharedEngine()->playMusic("menu.ogg"_spr, true, 0.0f, 0);
    }
    void playMenuMusic(){
       FMODAudioEngine::sharedEngine()->playMusic("menu.ogg"_spr, true, 0.0f, 0);
    }
};
