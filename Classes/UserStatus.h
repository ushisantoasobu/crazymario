#ifndef __test__UserStatus__
#define __test__UserStatus__

#include "cocos2d.h"

class UserStatus
{
private:
    UserStatus();
    static UserStatus* m_mySingleton;
    
public:
    static UserStatus* sharedUserStatus();
    
    int score;
    int currentStageId;
};

#endif /* defined(__test__UserStatus__) */
