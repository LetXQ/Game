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
    std::cout << "Walk init\n";
    return true;
}

bool BtWalkNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    // check obj pos in  walk area
    std::cout << "Start Walk\n";
    return true;
}

BT_STATUS BtWalkNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    // use walk skill
    std::cout << "Execute Walk\n";
    return S_SUCCESS;
}

void BtWalkNode::FinshAction(BtProxy *proxy)
{
    std::cout << "Finish Walk\n";
    // stop walk
}
