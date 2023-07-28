#include "syati.h"
#include "neo/core.h"

namespace {
    /*****************************************************************************************************************/
    /* Coins don't replenish health                                                                                  */
    /*****************************************************************************************************************/
    // kmWrite32(0x80023AE4, NOP);


    /*****************************************************************************************************************/
    /* Animate Rainbow power-up properly                                                                             */
    /*****************************************************************************************************************/
    void invokeInvincibleMarioModelCalcAnim(ModelHolder *pModelHolder) {
        MR::onCalcAnim(pModelHolder);
        pModelHolder->calcAnim();
    }

    kmCall(0x803C4A0C, invokeInvincibleMarioModelCalcAnim);


    /*****************************************************************************************************************/
    /* Silver Stars replenish Air                                                                                    */
    /*****************************************************************************************************************/
    void strayTicoFillAirAndRumblePad(LiveActor *pStrayTico, s32 rumbleArg) {
        MR::incPlayerOxygen(8);
        MR::tryRumblePadMiddle(pStrayTico, rumbleArg);
    }

    kmCall(0x8035FE68, strayTicoFillAirAndRumblePad);


    /*****************************************************************************************************************/
    /* Timer Clocks can be collected while player is "riding" an object                                              */
    /*****************************************************************************************************************/
    bool checkTimeAttackClockSensor(const HitSensor *pSensor) {
        return MR::isSensorPlayerOrRide(pSensor);
    }

    kmCall(0x80323544, checkTimeAttackClockSensor);


    /*****************************************************************************************************************/
    /* Message responses                                                                                             */
    /*****************************************************************************************************************/
    // Petari
    bool checkPetariPlayerAttacks(u32 msg) {
        return MR::isMsgFreezeAttack(msg) || MR::isMsgInvincibleAttack(msg);
    }

    kmCall(0x801E9B80, checkPetariPlayerAttacks);


    // Pukupuku
    bool checkPukupukuPlayerAttacks(u32 msg) {
        return MR::isMsgYoshiProjectile(msg) || MR::isMsgInvincibleAttack(msg);
    }

    kmCall(0x801F17F4, checkPukupukuPlayerAttacks);


    /*****************************************************************************************************************/
    /* Hide fix for Octopus                                                                                          */
    /*****************************************************************************************************************/
    kmWrite32(0x801DCBB4, 0x40820014);


    /*****************************************************************************************************************/
    /* Cosmic Spirit also appears when playing as Luigi                                                              */
    /*****************************************************************************************************************/
    kmWrite32(0x80360D54, LI_R3_0); // SuperDreamer::init ignores Luigi
    kmWrite32(0x804D7EAC, LI_R3_0); // GameSequenceFunction::isAllowDreamerInStage ignores Luigi


    /*****************************************************************************************************************/
    /* Skippable intro after collecting a Power Star                                                                 */
    /*****************************************************************************************************************/
    kmWrite32(0x804D254C, 0x60000005);


    /*****************************************************************************************************************/
    /* Clipping fix for Warp Pipes in Gloomy Galleon Galaxy                                                          */
    /*****************************************************************************************************************/
    bool checkEarthenPipeClipping(const char *origStageCheck) {
        register LiveActor *earthenPipe;
        __asm {
            mr earthenPipe, r28
        }

        if (MR::isEqualStageName(STAGE_GLOOMY_GALLEON_GALAXY)) {
            MR::setClippingTypeSphere(earthenPipe, 2000.0f);
            return false;
        }
        else {
            return MR::isEqualStageName(origStageCheck);
        }
    }

    kmCall(0x80296F90, checkEarthenPipeClipping);
}
