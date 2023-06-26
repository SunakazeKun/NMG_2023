#include "syati.h"

class Meramera : public LiveActor {
public:
    u8 _90[0x1C4 - 0x90];
};

namespace {
    void initChokomeraModel(Meramera *pActor, const JMapInfoIter &rIter, const char *pModelName, bool unk) {
        if (MR::isValidInfo(rIter)) {
            MR::getObjectName(&pModelName, rIter);
        }

        MR::processInitFunction(pActor, rIter, pModelName, unk);
    }

    kmCall(0x801C657C, initChokomeraModel);
}
