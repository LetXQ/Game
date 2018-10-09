#include "../include/common/lock.h"

CMutex::CMutex()
{
    pthread_mutex_init(&m_mutex, nullptr);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void CMutex::Lock()
{
    pthread_mutex_lock(&m_mutex);
}

void CMutex::Unlock()
{
    pthread_mutex_unlock(&m_mutex);
}

Lock::Lock(ILock& lock)
    : m_lock(lock)
{
    m_lock.Lock();
}

Lock::~Lock()
{
    m_lock.Unlock();
}
