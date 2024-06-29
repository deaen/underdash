#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "utMenuBackground.hpp"


utMenuBackground* utMenuBackground::create() {
    auto ret = new utMenuBackground();
    if (ret && ret->init()) {
        ret->autorelease();
    }
    else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool utMenuBackground::init() {

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setID("UtMenuBackground"_spr);

    auto doorSpr = CCSprite::create("door.png"_spr);
    doorSpr->setPosition({ winSize.width / 2, winSize.height });
    doorSpr->setScale(1.5f);
    doorSpr->setID("background-door"_spr);
    doorSpr->setZOrder(-100);
    this->addChild(doorSpr);

    auto groundSpr = CCSprite::create("ground.png"_spr);
    groundSpr->setPosition({ winSize.width / 2, winSize.height / 6 });
    groundSpr->setScale(1.5f);
    groundSpr->setID("background-door"_spr);
    groundSpr->setZOrder(-100);
    this->addChild(groundSpr);


    SimplePlayer* playerSpr = curPlayer();
    playerSpr->setPosition({ winSize.width / 2, winSize.height / 4 });
    playerSpr->setID("player-icon"_spr);
    playerSpr->setZOrder(-99);
    this->addChild(playerSpr);

    std::string cLabel = "GEOMETRY DASH V"+ Loader::get() -> getGameVersion() +" (C) RobTopGames 2013-2024";
    auto copyrightLabel = CCLabelBMFont::create(cLabel.c_str(), "cryptFont.fnt"_spr);
    copyrightLabel->setPosition({ winSize.width / 2, winSize.height / 50});
    copyrightLabel->setZOrder(-100);
    copyrightLabel->setID("copyirght-label"_spr);
    copyrightLabel->setScale(0.3f);
    this->addChild(copyrightLabel);
    return true;
}

int utMenuBackground::iconIndex(IconType type) {
    auto gm = GameManager::sharedState();

    switch (type) {
    case IconType::Ship:
        return gm->getPlayerShip();
    case IconType::Ball:
        return gm->getPlayerBall();
    case IconType::Ufo:
        return gm->getPlayerBird();
    case IconType::Wave:
        return gm->getPlayerDart();
    case IconType::Robot:
        return gm->getPlayerRobot();
    case IconType::Spider:
        return gm->getPlayerSpider();
    case IconType::Swing:
        return gm->getPlayerSwing();
    case IconType::Jetpack:
        return gm->getPlayerJetpack();
    default:
        return gm->getPlayerFrame();
    }
}

SimplePlayer* utMenuBackground::curPlayer() {
    auto gm = GameManager::sharedState();

    SimplePlayer* player = SimplePlayer::create(0);
    player->updatePlayerFrame(iconIndex(gm->m_playerIconType), gm->m_playerIconType);
    player->setColor(gm->colorForIdx(gm->getPlayerColor()));
    player->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
    player->setColor(gm->colorForIdx(gm->getPlayerColor()));
    if (gm->getPlayerGlow()) player->setGlowOutline(gm->colorForIdx(gm->getPlayerGlowColor()));
    return player;
}