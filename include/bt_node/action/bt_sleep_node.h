#ifndef BT_SLEEP_NODE_H
#define BT_SLEEP_NODE_H
#include "../include/bt/bt_action_node.h"

class BtSleepNode final : public BtActionNode
{
public:
    BtSleepNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

protected:
    bool StartAction(BtProxy* proxy, int32_t now_time) override;
    BT_STATUS DoAction(BtProxy* proxy, int32_t now_time) override;
    void FinshAction(BtProxy* proxy) override;

private:
    int32_t m_SleepSkillID = 0;
};

#endif // BT_SLEEP_NODE_H
