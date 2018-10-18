#ifndef BT_PROXY_H
#define BT_PROXY_H
#include <string.h>
#include <iostream>

class BtNode;
class BtProxy
{
public:
    bool Init(const std::string& obj_name);
    void OnTimeUpdate(int32_t now_time);
    bool LastRunning() const;

private:
    bool m_LastRunning = false;
    BtNode* m_pRoot = nullptr;
};

#endif // BT_PROXY_H
