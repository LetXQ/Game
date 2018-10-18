#include "../include/bt_node/action/bt_walk_node.h"
#include "../include/common/common_func.h"

bool BtWalkNode::Init(Json::Value &js)
{
    if (!js["ParamWalkTime"].isNull())
    {
        CommonFuncs::ParseIntByKey(js["ParamWalkTime"], "WalkTime", m_WalkTime);
    }

    if (!js["ParamWalkTime"].isNull())
    {
        CommonFuncs::ParseIntByKey(js["ParamWalkTime"], "MaxDistance", m_WalkMaxDist);
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
