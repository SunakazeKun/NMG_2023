#include "neo/NPC/Butler.h"

namespace neo {
    Butler::Butler(const char *pName) : NPCActor(pName) {

    }

    void Butler::init(const JMapInfoIter & rIter) {
        NPCActorCaps capabilities("Butler");
        capabilities.setDefault();
        capabilities.mBodySensorJoint = "Body";
        capabilities.mBodySensorRadius = 50.0f;
        capabilities.mBodySensorOffset.zero();

        mActionWait = "Wait";
        mActionWaitTurn = "Wait";
        mActionTalk = "Talk";
        mActionTalkTurn = "Talk";
        mActionSpinName = "Spin";
        mActionTrampledName = "Trampled";
        mActionPointingName = "Pointing";
        mActionReactionName = "Spin";

        initialize(rIter, capabilities, NULL, NULL, false);
    }

    void Butler::kill() {
        MR::forceDeleteEffectAll(this);
        NPCActor::kill();
    }

    void Butler::control() {
        if (mReactTrampleAttack) {
            MR::startActionSound(this, "SmNpcTrampled", -1, -1, -1);
            MR::startActionSound(this, "SvButlerTrampled", -1, -1, -1);
        }

        if (mReactStarPieceAttack) {
            MR::limitedStarPieceHitSound();
            MR::startActionSound(this, "SmButlerAbsorb", -1, -1, -1);
        }

        if (NPCActor::isPointingSe()) {
            MR::startActionSound(this, "SvButlerPoint", -1, -1, -1);
        }

        NPCActor::control();
    }
}
