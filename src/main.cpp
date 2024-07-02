#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/loader/SettingEvent.hpp>
#include "ui/utMenuBackground.hpp"
#include "ui/utMenuItemLayer.hpp"
#include "ui/utSettingsHeader.hpp"
using namespace geode::prelude;

bool playSfx;
class $modify(MyMenuLayer, MenuLayer) {

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }
        createUtMenu();
        playSfx = true;
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
        if (this->getChildByID("UtMenuItemLayer"_spr) == nullptr) this->addChild(utMenuItemLayer::create(this, menu_selector(MyMenuLayer::onShowClassicMenu)));
    }

    void onShowUtMenu(CCObject * = nullptr) {
        CCObject* obj;
        CCARRAY_FOREACH(this -> getChildren(), obj) {
            auto item = typeinfo_cast<CCNode*>(obj);
            if (item != nullptr && item->getID() != "FLAlertLayer") item->setVisible(false);
        }
        if (this->getChildByID("UtMenuBackground"_spr) != nullptr) this->getChildByID("UtMenuBackground"_spr)->setVisible(true);
        if (this->getChildByID("UtMenuItemLayer"_spr) != nullptr) this->getChildByID("UtMenuItemLayer"_spr)->setVisible(true);

    }

    void onShowClassicMenu(CCObject * = nullptr) {
        CCObject* obj;
        CCARRAY_FOREACH(this -> getChildren(), obj) {
            auto item = typeinfo_cast<CCNode*>(obj);
            if (item != nullptr) item->setVisible(true);
        }
        if (this->getChildByID("UtMenuBackground"_spr) != nullptr) this->getChildByID("UtMenuBackground"_spr)->setVisible(false);
        if (this->getChildByID("UtMenuItemLayer"_spr) != nullptr) this->getChildByID("UtMenuItemLayer"_spr)->setVisible(false);
    }
};

class $modify(GameManager) {
    void fadeInMenuMusic() {
        if (Mod::get()->getSettingValue<bool>("utMusic")) {
            FMODAudioEngine::sharedEngine()->playMusic("menu.ogg"_spr, true, 0.0f, 0);
        }
        else {
            GameManager::fadeInMenuMusic();
        }
    }
    void playMenuMusic() {
        if (Mod::get()->getSettingValue<bool>("utMusic")) {
            FMODAudioEngine::sharedEngine()->playMusic("menu.ogg"_spr, true, 0.0f, 0);
        }
        else {
            GameManager::fadeInMenuMusic();
        }
    }
};

$execute{
    listenForSettingChanges("utMusic", +[](bool value) {
        GameManager::sharedState()->fadeInMenuMusic();
    });
}

class $modify(LoadingLayer) {

    bool init(bool p0) {
        if (!LoadingLayer::init(p0)) return false;

        auto barBool = Mod::get()->getSettingValue<bool>("loadingBar");

        if (!barBool) {
            CCObject* obj;
            CCARRAY_FOREACH(this -> getChildren(), obj) {
                auto item = typeinfo_cast<CCNode*>(obj);
                if (item != nullptr) item->setVisible(false);
            }
        }
        else {
            CCObject* obj;
            CCARRAY_FOREACH(this -> getChildren(), obj) {
                auto item = typeinfo_cast<CCNode*>(obj);
                if (item != nullptr && item->getID() != "progress-slider" && item->getID() != "geode-small-label" && item->getID() != "geode-small-label-2") item->setVisible(false);
            }
        }
        return true;
    }

    void loadAssets() {
        LoadingLayer::loadAssets();

        auto utLogo = CCSprite::create("loading_logo.png"_spr);
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        utLogo->setScale(1.5);
        utLogo->setPosition({ winSize.width / 2, winSize.height / 2 });
        this->addChild(utLogo);

        if (!playSfx) { FMODAudioEngine::sharedEngine()->playEffect("loading_sfx.ogg"_spr); playSfx = true; }

        if (this->getChildByIDRecursive("geode-small-label") != nullptr) {
            auto geodeLabel = typeinfo_cast<CCLabelBMFont*>(this->getChildByIDRecursive("geode-small-label"));
            geodeLabel->setFntFile("utFont.fnt"_spr);
            geodeLabel->setVisible(true);
        }
        if (this->getChildByIDRecursive("geode-small-label-2") != nullptr) {
            auto geodeLabel = typeinfo_cast<CCLabelBMFont*>(this->getChildByIDRecursive("geode-small-label-2"));
            geodeLabel->setFntFile("utFont.fnt"_spr);
            geodeLabel->setVisible(true);
        }
    }
};

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<HeaderValue>("icon-section", 0);
    Mod::get()->addCustomSetting<HeaderValue>("menu-section", 0);
    Mod::get()->addCustomSetting<HeaderValue>("other-section", 0);
}