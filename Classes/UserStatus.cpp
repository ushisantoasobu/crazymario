#include "UserStatus.h"

UserStatus* UserStatus::m_mySingleton = NULL;

UserStatus::UserStatus()
{
}

UserStatus* UserStatus::sharedUserStatus()
{
    if(NULL == m_mySingleton)
    {
        m_mySingleton = new UserStatus();
        m_mySingleton->score = 0;
        m_mySingleton->currentStageId = 0;
    }
    return m_mySingleton;
}