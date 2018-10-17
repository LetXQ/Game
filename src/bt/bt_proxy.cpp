#include "../include/bt/bt_proxy.h"
#include "../include/bt/bt_node.h"
#include "../include/config/bt_parse.h"

bool BtProxy::Init(const std::string &obj_name)
{
    m_pRoot = BtParse::Instance().GetBtRootNode(obj_name);

    if (!m_pRoot)
        return false;
    return true;
}

void BtProxy::OnTimeUpdate(int32_t now_time)
{

}

