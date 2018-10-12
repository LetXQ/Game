#ifndef BT_PARSE_H
#define BT_PARSE_H
#include <string.h>
#include <map>
#include "../common/singleton.h"
#include "../include/json/json.h"

class BtNode;
class BtParse : public Singleton<BtParse>
{
public:
    bool ParseConfigFile(const std::string& file_name);
    BtNode* GetBtRootNode(const std::string& obj_name);

private:
    bool ParseBtData(Json::Value& msg);
    bool ParseNode(Json::Value& data, BtNode* parent_node);
private:
    int32_t m_iVersion = 0;
    std::string m_sFile = "";
};
#endif // BT_PARSE_H
