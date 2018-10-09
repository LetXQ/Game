#ifndef LOCK_H
#define LOCK_H
#include <pthread.h>

class ILock
{
public:
    virtual void Lock() = 0;
    virtual void Unlock() = 0;
};

class CMutex : public ILock
{
private:
    mutable pthread_mutex_t m_mutex;
public:
    CMutex();
    ~CMutex();
    void Lock() override;
    void Unlock() override;
};

class Lock
{
public:
    Lock(ILock& lock);
    ~Lock();
private:
    ILock& m_lock;
};

#endif // LOCK_H
