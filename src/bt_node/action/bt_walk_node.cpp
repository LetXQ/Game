#include "../include/bt_node/action/bt_walk_node.h"
#include "../include/common/common_json_func.h"

bool BtWalkNode::Init(Json::Value &js)
{
    if (!js["ParamWalkSkillID"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamWalkSkillID"], "SkillID", m_WalkSkillID);
    }

    if (!js["ParamWalkAreaRadius"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamWalkAreaRadius"], "WalkAreaRadius", m_WalkAreaRadius);
    }

    if (!js["ParamWalkSpeed"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamWalkSpeed"], "WalkSpeed", m_WalkSpeed);
    }
    return true;
}

bool BtWalkNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    return true;
}

BT_STATUS BtWalkNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    return S_SUCCESS;
}

void BtWalkNode::FinshAction(BtProxy *proxy)
{

}
