#ifndef BT_ATTACK_NODE_H_
#define BT_ATTACK_NODE_H_
#include "../include/bt/bt_action_node.h"

class BtAttackNode final : public BtActionNode
{
public:
    BtAttackNode(BtNode* parent) : BtActionNode(parent) {}
    bool Init(Json::Value& js) override;

protected:
    bool StartAction(BtProxy* proxy, int32_t now_time) override;
    BT_STATUS DoAction(BtProxy* proxy, int32_t now_time) override;
    void FinshAction(BtProxy* proxy) override;

private:
    int32_t m_TargetID = 0;
    int32_t m_SkillID = 0;
    std::string m_ParamName = "";
};

#endif
