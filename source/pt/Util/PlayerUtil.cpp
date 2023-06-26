#include "pt/Util/PlayerUtil.h"

namespace pt {
    bool isPlayerElementMode(s32 mode) {
        return MarioAccess::getPlayerActor()->mPlayerMode == mode;
    }
}
