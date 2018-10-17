#ifndef BT_PROXY_H
#define BT_PROXY_H

class BtNode;
class BtProxy
{
public:
    bool Init(const std::string& obj_name);
    void OnTimeUpdate(int32_t now_time);
private:
    BtNode* m_pRoot = nullptr;
};

#endif // BT_PROXY_H
