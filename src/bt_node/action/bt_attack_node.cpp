#include "../include/bt_node/action/bt_attack_node.h"
#include "../include/common/common_json_func.h"
#include "../include/bt/bt_parameter.h"
#include "../include/bt/bt_proxy.h"

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

    std::cout << "Attack init\n";
    return true;
}

bool BtAttackNode::StartAction(BtProxy *proxy, int32_t now_time)
{
    if (proxy)
    {
        const auto& param = proxy->GetParam(m_ParamName);
        if (param && param->IsInt32())
        {
            m_TargetID = param->AsInt32();
            return true;
        }
    }
    return false;
}

BT_STATUS BtAttackNode::DoAction(BtProxy *proxy, int32_t now_time)
{
    std::cout << "Attack target: " << m_TargetID << std::endl;
    return S_SUCCESS;
}

void BtAttackNode::FinshAction(BtProxy *proxy)
{
    m_TargetID = 0;
}
