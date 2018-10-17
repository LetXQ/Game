#ifndef BT_ACTION_NODE_H
#define BT_ACTION_NODE_H
#include "bt_node.h"

class BtActionNode : public BtNode
{
public:
    BtActionNode(BtNode* parent) : BtNode(parent) {}
};

class BtAttackNode : public BtActionNode
{
public:
    BtAttackNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

private:
    int32_t m_SkillID = 0;
    std::string m_ParamName = "";
};

class BtSleepNode : public BtActionNode
{
public:
    BtSleepNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

private:
    int32_t m_SleepTime = 0;
};

class BtWalkNode : public BtActionNode
{
public:
    BtWalkNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

private:
    int32_t m_WalkTime = 0;
    int32_t m_WalkMaxDist = 0;
};

#endif // BT_ACTION_NODE_H
