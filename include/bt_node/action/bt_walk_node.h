#ifndef BT_WALK_NODE_H
#define BT_WALK_NODE_H
#include "../include/bt/bt_action_node.h"

class BtWalkNode final : public BtActionNode
{
public:
    BtWalkNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

protected:
    bool StartAction(BtProxy* proxy, int32_t now_time) override;
    BT_STATUS DoAction(BtProxy* proxy, int32_t now_time) override;
    void FinshAction(BtProxy* proxy) override;

private:
    int32_t m_WalkTime = 0;
    int32_t m_WalkMaxDist = 0;
};

#endif // BT_WALK_NODE_H
