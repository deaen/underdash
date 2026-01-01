#include "utButton.hpp"


utButton* utButton::create(gd::string bttnText, CCObject* target, SEL_MenuHandler callback, std::string id, CCMenu* menu) {
    auto ret = new utButton();

    auto ButtonLabel = CCLabelBMFont::create(bttnText.c_str(), "utFont.fnt"_spr);

    if (ret && ret->init(ButtonLabel, nullptr, target, callback)) {
        ret->autorelease();
        ret->setID(id);
        menu->addChild(ret);
        ret -> m_animationEnabled = false;
    }
    else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void utButton::selected() {
    this->setColor({ 242, 242, 0 });
}

void utButton::activate() {
    this->setColor({ 242, 242, 0 });
    CCMenuItem::activate();
    auto tint = CCTintTo::create(1, 255, 255, 255);
    this -> runAction(tint);
}

void utButton::unselected() {
    this->setColor({ 255, 255, 255 });
}