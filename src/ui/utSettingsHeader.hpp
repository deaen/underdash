#pragma once
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;

class HeaderValue;
class HeaderNode;

class HeaderValue : public SettingValue {
private:
    int m_something;
public:
    HeaderValue(std::string const& key, std::string const& mod, int const& something)
        : SettingValue(key, mod), m_something(something) {}

    bool load(matjson::Value const& json) override {
        return true;
    }
    bool save(matjson::Value& json) const override {
        return true;
    }
    SettingNode* createNode(float width) override;
};

class HeaderNode : public SettingNode {
protected:
    bool init(HeaderValue* value, float width) {
        if (!SettingNode::init(value)) return false;

        this->setContentSize({ width, 40.f });
        std::string sectionName = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");
        auto label = CCLabelBMFont::create(sectionName.c_str(), "utFont.fnt"_spr);
        label->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
        label->setColor({ 242, 242, 0 });
        this->addChild(label);
        return true;
    }

public:
    void commit() override {
        this->dispatchCommitted();
    }

    bool hasUncommittedChanges() override {
        return false;
    }

    bool hasNonDefaultValue() override {
        return true;
    }

    void resetToDefault() override {

    }
    static HeaderNode* create(HeaderValue* value, float width) {
        auto ret = new HeaderNode;
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

SettingNode* HeaderValue::createNode(float width) {
    return HeaderNode::create(this, width);
}