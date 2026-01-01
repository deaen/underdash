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

    auto iconLayer = CCLayer::create();

    iconLayer->setID("ut-icon-layer"_spr);
    iconLayer->setLayout(
        AxisLayout::create()
        ->setGap(40.f)
        ->setAxisAlignment(AxisAlignment::Center)
        ->setAxis(Axis::Row)
        ->setGrowCrossAxis(true)
    );
    iconLayer->setZOrder(-99);
    iconLayer->setPosition({ winSize.width / 2, winSize.height / 4 });
    this->addChild(iconLayer);
    createIcons(iconLayer);
    iconLayer->updateLayout();

    std::string cLabel = "GEOMETRY DASH V" + Loader::get()->getGameVersion() + " (C) RobTopGames 2013-" + std::to_string(1970 + std::time(nullptr) / 31537970); // lol
    auto copyrightLabel = CCLabelBMFont::create(cLabel.c_str(), "cryptFont.fnt"_spr);
    copyrightLabel->setPosition({ winSize.width / 2, winSize.height / 50 });
    copyrightLabel->setZOrder(-100);
    copyrightLabel->setID("copyirght-label"_spr);
    copyrightLabel->setScale(0.3f);
    this->addChild(copyrightLabel);
    return true;
}

int utMenuBackground::selectedGamemode(IconType type) {
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

SimplePlayer* utMenuBackground::curPlayer(int iconIndex, IconType gamemode) {
    auto gm = GameManager::sharedState();
    SimplePlayer* player = SimplePlayer::create(0);
    player->updatePlayerFrame(iconIndex, gamemode);
    player->setColor(gm->colorForIdx(gm->getPlayerColor()));
    player->setSecondColor(gm->colorForIdx(gm->getPlayerColor2()));
    player->setColor(gm->colorForIdx(gm->getPlayerColor()));
    if (gm->getPlayerGlow()) player->setGlowOutline(gm->colorForIdx(gm->getPlayerGlowColor()));
    return player;
}

void utMenuBackground::createIcons(CCLayer* layer){
    auto activeIcon = Mod::get()->getSettingValue<bool>("activeIcon");
    auto iconCube = Mod::get()->getSettingValue<bool>("iconCube");
    auto iconShip = Mod::get()->getSettingValue<bool>("iconShip");
    auto iconBall = Mod::get()->getSettingValue<bool>("iconBall");
    auto iconUfo = Mod::get()->getSettingValue<bool>("iconUfo");
    auto iconWave = Mod::get()->getSettingValue<bool>("iconWave");
    auto iconRobot = Mod::get()->getSettingValue<bool>("iconRobot");
    auto iconSpider = Mod::get()->getSettingValue<bool>("iconSpider");
    auto iconSwing = Mod::get()->getSettingValue<bool>("iconSwing");
    auto iconJetpack = Mod::get()->getSettingValue<bool>("iconJetpack");
    auto gm = GameManager::sharedState();

    SimplePlayer* playerSpr;
    if (activeIcon){
            playerSpr = curPlayer(selectedGamemode(gm->m_playerIconType), gm->m_playerIconType);
            playerSpr->setID("active-icon"_spr);
            layer->addChild(playerSpr);
    }
    else
    {
        if (iconCube)
        {
            playerSpr = curPlayer(gm->getPlayerFrame(), IconType::Cube);
            playerSpr->setID("icon-cube"_spr);
            layer->addChild(playerSpr);
        }
        if (iconShip)
        {
            playerSpr = curPlayer(gm->getPlayerShip(), IconType::Ship);
            playerSpr->setID("icon-ship"_spr);
            layer->addChild(playerSpr);
        }
        if (iconBall)
        {
            playerSpr = curPlayer(gm->getPlayerBall(), IconType::Ball);
            playerSpr->setID("icon-ball"_spr);
            layer->addChild(playerSpr);
        }
        if (iconUfo)
        {
            playerSpr = curPlayer(gm->getPlayerBird(), IconType::Ufo);
            playerSpr->setID("icon-ufo"_spr);
            layer->addChild(playerSpr);
        }
        if (iconWave)
        {
            playerSpr = curPlayer(gm->getPlayerDart(), IconType::Wave);
            playerSpr->setID("icon-wave"_spr);
            layer->addChild(playerSpr);
        }
        if (iconRobot)
        {
            playerSpr = curPlayer(gm->getPlayerRobot(), IconType::Robot);
            playerSpr->setID("icon-robot"_spr);
            layer->addChild(playerSpr);
        }
        if (iconSpider)
        {
            playerSpr = curPlayer(gm->getPlayerSpider(), IconType::Spider);
            playerSpr->setID("icon-spider"_spr);
            layer->addChild(playerSpr);
        }
        if (iconSwing)
        {
            playerSpr = curPlayer(gm->getPlayerSwing(), IconType::Swing);
            playerSpr->setID("icon-swing"_spr);
            layer->addChild(playerSpr);
        }
        if (iconJetpack)
        {
            playerSpr = curPlayer(gm->getPlayerJetpack(), IconType::Jetpack);
            playerSpr->setID("icon-jetpack"_spr);
            layer->addChild(playerSpr);
        }
    }
}