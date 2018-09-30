#ifndef LOCK_H
#define LOCK_H

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
    Lock(const ILock& lock);
    ~Lock();
private:
    const ILock& m_lock;
};

#endif // LOCK_H
