#include "../include/config/bt_parse.h"
#include "../include/common/common_func.h"
#include "../include/bt/bt_node_factory.h"
#include "../include/bt/bt_node.h"

bool BtParse::ParseConfigFile(const std::string &file_name)
{
    m_sFile = file_name;
    Json::Value msg;
    if (CommonFuncs::ParseJsonFile(m_sFile, msg))
    {
        CommonFuncs::ParseIntByKey(msg, "version", m_iVersion);
        if (!msg["root"].isNull())
        {
            return ParseBtData(msg["root"]);
        }
    }
    return false;
}

BtNode *BtParse::GetBtRootNode(const string &obj_name)
{
    return nullptr;
}

bool BtParse::ParseBtData(Json::Value &msg)
{
    std::string obj_name = "";
    CommonFuncs::ParseStringtByKey(msg, "Name", obj_name);
    return true;
}

bool BtParse::ParseNode(Json::Value &data, BtNode *parent_node)
{
    int32_t id = 0;
    std::string type = "";
    CommonFuncs::ParseIntByKey(data, "ID", id);
    CommonFuncs::ParseStringtByKey(data, "Type", type);

    BtNode* new_node = BtNodeFactory::Instance().CreateNode(type, parent_node);
    if (!new_node)
        return false;

    new_node->SetID(id);
    new_node->Init(data);

    if (!data["Children"].isNull())
    {
        for (auto& elem : data["Children"])
        {
            if (!ParseNode(elem, new_node))
            {
                return false;
            }
        }
    }
    return true;
}
