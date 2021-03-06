#ifndef BT_PARSE_H
#define BT_PARSE_H
#include <string.h>
#include <map>
#include "../common/singleton.h"
#include "../include/json/json.h"

using bt_json_map_t = std::map<std::string, Json::Value>;
class BtNode;
class BtParse : public Singleton<BtParse>
{
public:
    bool ParseConfigFile(const std::string& file_name);
    BtNode* GetBtRootNode(const std::string& obj_name);

private:
    bool ParseBtData(Json::Value& msg);
    bool ParseNode(Json::Value& data, BtNode*& root_p, BtNode* parent_node = nullptr);
private:
    int32_t m_iVersion = 0;
    std::string m_sFile = "";
    bt_json_map_t m_BtJsonMap;
};
#endif // BT_PARSE_H
