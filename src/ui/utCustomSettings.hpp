#pragma once
using namespace geode::prelude;

using namespace geode::prelude;

class utSettingTitle : public SettingV3
{
public:
    static Result<std::shared_ptr<SettingV3>> parse(std::string const &key, std::string const &modID, matjson::Value const &json)
    {
        auto res = std::make_shared<utSettingTitle>();
        auto root = checkJson(json, "utSettingTitle");

        res->init(key, modID, root);
        res->parseNameAndDescription(root);
        res->parseEnableIf(root);

        root.checkUnknownKeys();
        return root.ok(std::static_pointer_cast<SettingV3>(res));
    }
    bool load(matjson::Value const &json) override
    {
        return true;
    }
    bool save(matjson::Value &json) const override
    {
        return true;
    }
    bool isDefaultValue() const override
    {
        return true;
    }
    void reset() override {}

    SettingNodeV3 *createNode(float width) override;
};

class utSettingTitleNode : public SettingNodeV3
{
protected:
    CCLabelBMFont *m_titleLabel;
    CCLabelBMFont *m_descLabel;
    bool init(std::shared_ptr<utSettingTitle> setting, float width)
    {
        if (!SettingNodeV3::init(setting, width))
            return false;

        std::string title = setting->getDisplayName();
        m_titleLabel = CCLabelBMFont::create(title.c_str(), "utFont.fnt"_spr);
        m_titleLabel->setColor({242, 242, 0});
        this->addChildAtPosition(m_titleLabel, Anchor::Center);

        if (auto desc = setting->getDescription())
        {
            std::string descString = "(" + desc.value() + ")";
            m_descLabel = CCLabelBMFont::create(descString.c_str(), "utFont.fnt"_spr);
            m_descLabel->setScale(0.5f);
            m_descLabel->setColor({242, 242, 0});
            this->setContentHeight(32);
            m_titleLabel->updateAnchoredPosition(Anchor::Top, {0, -(m_titleLabel->getScaledContentHeight() / 1.5f)});
            this->addChildAtPosition(m_descLabel, Anchor::Bottom, {0, m_descLabel->getScaledContentHeight() / 1.5f});
        }

        if (auto menu = this->getChildByType<CCMenu>(0))
        {
            menu->setVisible(false);
        }
        return true;
    }

    void onCommit() override {}
    void onResetToDefault() override {}

public:
    static utSettingTitleNode *create(std::shared_ptr<utSettingTitle> setting, float width)
    {
        auto ret = new utSettingTitleNode();
        if (ret->init(setting, width))
        {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool hasUncommittedChanges() const override
    {
        return false;
    }
    bool hasNonDefaultValue() const override
    {
        return false;
    }
};

SettingNodeV3 *utSettingTitle::createNode(float width)
{
    return utSettingTitleNode::create(
        std::static_pointer_cast<utSettingTitle>(shared_from_this()),
        width);
}

$execute
{
    (void)Mod::get()->registerCustomSettingType("section-title", &utSettingTitle::parse);
}
