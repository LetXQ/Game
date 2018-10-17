#include "../include/bt/bt_action_node.h"
#include "../include/common/common_func.h"

bool BtAttackNode::Init(Json::Value &js)
{
    if (!js["ParamAttackSkillID"].isNull())
    {
        CommonFuncs::ParseIntByKey(js["ParamAttackSkillID"], "SkillID", m_SkillID);
    }

    if (!js["ParamAttackTarget"].isNull())
    {
        CommonFuncs::ParseStringtByKey(js["ParamAttackTarget"], "Name", m_ParamName);
    }
    return true;
}

bool BtSleepNode::Init(Json::Value &js)
{
    if (!js["ParamSleepTime"].isNull())
    {
        CommonFuncs::ParseIntByKey(js["ParamSleepTime"], "SleepTime", m_SleepTime);
    }
    return true;
}

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
