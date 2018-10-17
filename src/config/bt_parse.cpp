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
        BtNodeFactory::Instance().Init();
        CommonFuncs::ParseIntByKey(msg, "version", m_iVersion);
        if (!msg["root"].isNull())
        {
            return ParseBtData(msg["root"]);
        }
    }
    else
        std::cout << "ParseJsonFile " << m_sFile << " Failed\n";
    return false;
}

BtNode *BtParse::GetBtRootNode(const string &obj_name)
{
    auto iter = m_BtJsonMap.find(obj_name);
    if (iter != m_BtJsonMap.end())
    {
        BtNode * root_node = nullptr;

        bool ret = ParseNode(iter->second, root_node);
        if (ret && root_node)
        {
            return root_node;
        }
        std::cout << "--------\n";
    }
    return nullptr;
}

bool BtParse::ParseBtData(Json::Value &msg)
{
    std::string obj_name = "";
    CommonFuncs::ParseStringtByKey(msg, "Name", obj_name);
    m_BtJsonMap.insert(std::make_pair(obj_name, msg));
    return true;
}

bool BtParse::ParseNode(Json::Value &data, BtNode *&root_p, BtNode *parent_node)
{
    int32_t id = 0;
    std::string type = "", str = "";
    CommonFuncs::ParseIntByKey(data, "ID", id);
    CommonFuncs::ParseStringtByKey(data, "Type", str);

    CommonFuncs::GetLastToken(str, type);
    BtNode* new_node = BtNodeFactory::Instance().CreateNode(type, parent_node);
    if (!new_node)
    {
        std::cout << "Create " << type <<  " failed\n";
        return false;
    }

    if (!parent_node)
    {
        root_p = new_node;
    }

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
