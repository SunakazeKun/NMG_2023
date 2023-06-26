#include "syati.h"

namespace pt {
    /*
    * New Dummy items
    *
    * New variants can be easily added and created here. This extends the existing set of dummy models. This replaces
    * all calls to MR::tryCreateDummyModel, but uses the original function to initialize the base game's items.
    */

    DummyDisplayModelInfo cNewDummyDisplayModels[] = {
        /* 15 */ { "PowerUpFire",       NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 16 */ { "PowerUpIce",        NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 17 */ { "PowerUpBee",        NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 18 */ { "PowerUpHopper",     NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 19 */ { "PowerUpTeresa",     NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 20 */ { "PowerUpFoo",        NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 21 */ { "PowerUpCloud",      NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 22 */ { "PowerUpRock",       NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 23 */ { "PowerUpInvincible", NULL,    { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
        /* 24 */ { "EarthenPipe",       NULL,    { 0.0f, 120.0f, 0.0f }, 16, NULL, false },
        /* 25 */ { "LifeUpHeart",       "Dummy", { 0.0f, 70.0f, 0.0f }, 16, NULL, false },
    };

#define NUM_NEW_DUMMY_MODEL_ITEMS (s32)(sizeof(cNewDummyDisplayModels) / sizeof(DummyDisplayModelInfo))

    DummyDisplayModel* tryCreateNewDummyModel(LiveActor *pHost, const JMapInfoIter &rIter, s32 defaultId, int v4) {
        s32 modelId = MR::getDummyDisplayModelId(rIter, defaultId);

        if (modelId < 0 || modelId > 14 + NUM_NEW_DUMMY_MODEL_ITEMS) {
            return NULL;
        }

        if (modelId <= 14) {
            return MR::tryCreateDummyModel(pHost, rIter, modelId, v4);
        }

        s32 colorId = 0;

        if (MR::isValidInfo(rIter)) {
            MR::getJMapInfoArg6NoInit(rIter, &colorId);
        }

        DummyDisplayModelInfo *pInfo = &cNewDummyDisplayModels[modelId - 15];
        DummyDisplayModel *pModel = new DummyDisplayModel(pHost, pInfo, v4, modelId, colorId);
        pModel->initWithoutIter();

        // EarthenPipe doesn't use ColorChange.brk
        if (modelId == 24) {
            MR::startBrkAndSetFrameAndStop(pModel, "EarthenPipe", colorId);
        }

        return pModel;
    }

    // Hooks
    kmCall(0x80295BB0, tryCreateNewDummyModel);
    kmCall(0x80295C28, tryCreateNewDummyModel);
    kmCall(0x80295CAC, tryCreateNewDummyModel);
    kmCall(0x80295D04, tryCreateNewDummyModel);
    kmCall(0x80295D88, tryCreateNewDummyModel);

    // Skip repeated reading of Obj_arg7 field
    kmWrite32(0x80295464, 0x7CA32B78);
    kmWrite32(0x80295468, 0x60000000);
}
