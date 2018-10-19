#include "../include/bt_node/action/bt_sleep_node.h"
#include "../include/common/common_json_func.h"

bool BtSleepNode::Init(Json::Value &js)
{
    if (!js["ParamSleepSkillID"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamSleepSkillID"], "SkillID", m_SleepSkillID);
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
