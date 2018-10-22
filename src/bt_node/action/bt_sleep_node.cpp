#include "../include/bt_node/action/bt_sleep_node.h"
#include "../include/common/common_json_func.h"

bool BtSleepNode::Init(Json::Value &js)
{
    if (!js["ParamSleepSkillID"].isNull())
    {
        CommonJsonFunc::ParseIntByKey(js["ParamSleepSkillID"], "SkillID", m_SleepSkillID);
    }
    std::cout << "Sleep init\n";
    return true;
}

bool BtSleepNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    // check status ok
     std::cout << "Start Sleep\n";
    return true;
}

BT_STATUS BtSleepNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    // use sleep skill
    std::cout << "Sleep\n";
    return S_RUNNING;
}

void BtSleepNode::FinshAction(BtProxy *proxy)
{
     std::cout << "Finsh Sleep\n";
    // change status;
}
