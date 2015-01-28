#pragma once

// Entity/Scene node category, used to dispatch commands
namespace Category
{
    enum Type
    {
        None            = 0,        // 0 0 0 0
        Scene           = 1 << 0,   // 0 0 0 1
        PlayerAircraft  = 1 << 1,   // 0 0 1 0
        AlliedAircraft  = 1 << 2,   // 0 1 0 0
        EnemyAircraft   = 1 << 3,   // 1 0 0 0
    };
}