#include "../include/bt_node/action/bt_sleep_node.h"
#include "../include/common/common_func.h"

bool BtSleepNode::Init(Json::Value &js)
{
    if (!js["ParamSleepTime"].isNull())
    {
        CommonFuncs::ParseIntByKey(js["ParamSleepTime"], "SleepTime", m_SleepTime);
    }
    return true;
}

bool BtSleepNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    return true;
}

BT_STATUS BtSleepNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    return S_SUCCESS;
}

void BtSleepNode::FinshAction(BtProxy *proxy)
{

}
