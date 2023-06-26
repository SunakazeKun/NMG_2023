#include "neo/MapObj/TransparentWall.h"
#include "pt/Util.h"

namespace neo {
    TransparentWall::TransparentWall(const char *pName) : InvisiblePolygonObj(pName) {
        mAllowFlags = -1;
        mValidated = false;
    }

    void TransparentWall::init(const JMapInfoIter &rIter) {
        InvisiblePolygonObj::init(rIter);
        MR::getJMapInfoArg4NoInit(rIter, &mAllowFlags);
        MR::invalidateCollisionParts(this);
        MR::setSensorType(this, "Body", ATYPE_ICEJUMP_WALL);
    }

    void TransparentWall::control() {
        if (!mValidated) {
            for (s32 i = 0; i < TRANSPARENT_WALL_FLAG_EXTRA_START; i++) {
                if (checkAllowed(i) && pt::isPlayerElementMode(i)) {
                    mValidated = true;
                    break;
                }
            }

            if (checkAllowed(TRANSPARENT_WALL_CHECK_PLAYER_TERESA_DISAPPEAR) && !MR::isPlayerTeresaDisappear()) {
                mValidated = true;
            }

            if (mValidated) {
                MR::validateCollisionParts(this);
            }
        }
        else {
            bool invalidate = true;

            for (s32 i = 0; i < TRANSPARENT_WALL_FLAG_EXTRA_START; i++) {
                if (checkAllowed(i) && pt::isPlayerElementMode(i)) {
                    invalidate = false;
                    break;
                }
            }

            if (checkAllowed(TRANSPARENT_WALL_CHECK_PLAYER_TERESA_DISAPPEAR)) {
                invalidate = MR::isPlayerTeresaDisappear();
            }

            if (invalidate) {
                MR::invalidateCollisionParts(this);
                mValidated = false;
            }
        }
    }
}
