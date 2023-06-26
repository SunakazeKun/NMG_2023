#include "syati.h"

/*
* Authors: Aurum
*/
namespace pt {
    /*
    * Error Message Fallback
    *
    * Missing text will usualy crash the game. This small patch will display the text label whose message data could not be
    * located instead of nothing. This tells developers what text is missing.
    */
    static wchar_t cErrorMessageBuffer[128]; // Buffer for missing text label. Last wchar should always be NULL.

    const wchar_t* getErrorMessage(const char *pLabel) {
        asm("mr %0, r31" : "=r" (pLabel));

        size_t len = strlen(pLabel) + 1;

        if (len > 127) {
            len = 127;
        }

        mbstowcs(cErrorMessageBuffer, pLabel, len);

        return cErrorMessageBuffer;
    }

    kmCall(0x800413F0, getErrorMessage); // MR::getGameMessageDirect will return the error message instead of NULL


    /*
    * Green Launch Star
    *
    * Unsurprisingly, all the BTP and BRK frames for the green Launch Star is still found inside SuperSpinDriver.arc. Here,
    * we hijack calls to initColor in order to check for the green color first. If the Launch Star's color is set to green,
    * we apply its animation frames. Otherwise, we call initColor to set up the other colors.
    */
    void initSuperSpinDriverGreenColor(SuperSpinDriver *pActor) {
        if (pActor->mColor == SUPER_SPIN_DRIVER_GREEN) {
            MR::startBtpAndSetFrameAndStop(pActor, "SuperSpinDriver", 1.0f);
            MR::startBrk(pActor, "Green");

            pActor->mSpinDriverPathDrawer->mColor = 0;
        }
        else {
            pActor->initColor();
        }
    }

    kmCall(0x8031E29C, initSuperSpinDriverGreenColor); // redirect initColor in init

    /*
    * The Green Launch Star is coded to load a model from SuperSpinDriverEmpty.arc. This was used for the transparent model
    * in SMG1 to mark its position before all green stars are collected. However, we have no use of this property in SMG2,
    * so we can safely disable this here. This also improves memory usage since this model would be loaded at all times.
    */
    kmWrite32(0x8031E2A4, 0x60000000); // NOP call to initEmptyModel.


    /*
    * KeySwitch fix
    *
    * If a KeySwitch is constructed by Teresa or KuriboChief, it will crash the game due to an oversight by the developers.
    * This feature works perfectly fine in SMG1, however, SMG2 introduced a new Obj_arg that does not check if the given
    * JMapInfoIter is valid before attempting to read the Obj_arg value. This will cause the game to access invalid data
    * and thus causing a crash.
    */
    void initKeySwitchSafeGetShadowDropLength(const JMapInfoIter &rIter, f32 *pDest) {
        if (MR::isValidInfo(rIter)) {
            MR::getJMapInfoArg0NoInit(rIter, pDest);
        }
    }

    kmCall(0x802BDE80, initKeySwitchSafeGetShadowDropLength); // overwrite call to getJMapInfoArg0NoInit


    /*
    * HipDropSwitch & Pull Star crash fix
    *
    * Fixes the crash when using a Pull Star while standing on a HipDropSwitch. Thanks Zyphro!
    */
    f32 fixHipDropSwitchPullStarCrash(TVec3f& rVecA, TVec3f& rVecB) {
        return MR::isOnGroundPlayer() ? rVecA.dot(rVecB) : 0.0f;
    }

    kmCall(0x802AF938, fixHipDropSwitchPullStarCrash);
}
