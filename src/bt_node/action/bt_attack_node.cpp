#include "../include/bt_node/action/bt_attack_node.h"
#include "../include/common/common_json_func.h"

bool BtAttackNode::Init(Json::Value &js)
{
    if (!js["ParamAttackSkillID"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamAttackSkillID"], "SkillID", m_SkillID);
    }

    if (!js["ParamAttackTarget"].isNull())
    {
        CommonJsonFunc::ParseStringtByKey(js["ParamAttackTarget"], "Name", m_ParamName);
    }
    return true;
}

bool BtAttackNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    return true;
}

BT_STATUS BtAttackNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    return S_SUCCESS;
}

void BtAttackNode::FinshAction(BtProxy *proxy)
{

}
