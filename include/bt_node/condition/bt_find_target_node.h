#ifndef BT_FIND_TARGET_NODE_H_
#define BT_FIND_TARGET_NODE_H_
#include "../include/bt/bt_condition_node.h"

class BtFindTargetNode final : public BtConditionNode
{
public:
    BtFindTargetNode(BtNode* parent) : BtConditionNode(parent) {}
    bool Init(Json::Value& js) override;

protected:
    bool IsValid(BtProxy *proxy, int32_t now_time) override;
};

#endif
