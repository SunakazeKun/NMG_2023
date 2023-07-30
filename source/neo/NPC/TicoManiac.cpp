#include "neo/NPC/TicoManiac.h"

namespace neo {
	TicoManiac::TicoManiac(const char *pName) : NPCActor(pName) {

	}

	void TicoManiac::init(const JMapInfoIter &rIter) {
		NPCActorCaps caps("TicoShop");
		caps.setDefault();
		caps.mTalkMsgLabel = "TicoManiac";
		initialize(rIter, caps, "TicoShop", NULL, false);

		MR::registerKillFunc(mTalkCtrl, TalkMessageFunc(this, &killFunc));

		mActionWait = "Wait";
		mActionWaitTurn = "Wait";
		mActionTalk = "Talk";
		mActionTalkTurn = "Talk";
		mActionSpinName = "Spin";
		mActionTrampledName = "Trampled";
		mActionPointingName = "Pointing";
		mActionReactionName = "Reaction";

		MR::startBva(this, "Small0");
		MR::startBrkAndSetFrameAndStop(this, "Metamorphosis", 0.0f);
		MR::setDistanceToTalk(mTalkCtrl, 350.0f);
		MR::invalidateShadow(this, "RKinoko");
		MR::invalidateShadow(this, "LKinoko");
		MR::invalidateShadow(this, "RLine");
		MR::invalidateShadow(this, "LLine");
	}

	void TicoManiac::calcAnim() {
		NPCActor::calcAnim();
		MR::hideMaterial(this, "Stick_v");
		MR::hideMaterial(this, "Stick_v(2)");
		MR::hideMaterial(this, "Stick_v(3)");
	}

	void TicoManiac::control() {
		if (mReactTrampleAttack) {
			MR::startActionSound(this, "SmNpcTrampled", -1, -1, -1);
			MR::startActionSound(this, "SvTicoShopTrampled", -1, -1, -1);
		}

		if (NPCActor::isPointingSe()) {
			MR::startActionSound(this, "SvTicoshopPoint", -1, -1, -1);
		}

		if (mReactSpinAttack) {
			MR::startActionSound(this, "SmTicoshopSpin", -1, -1, -1);
		}

		if (mReactStarPieceAttack) {
			MR::startActionSound(this, "SvTicoshopStarPieceHit", -1, -1, -1);
		}

		NPCActor::control();
	}

	void TicoManiac::exeMeta() {
		if (MR::isFirstStep(this)) {
			MR::startAction(this, "Metamorphosis");
			MR::startActionSound(this, "SmTicofatMeta", -1, -1, -1);
		}

		if (MR::isActionEnd(this)) {
			MR::startActionSound(this, "SmMetamorphoseSmoke", -1, -1, -1);
			kill();
		}
	}

	bool TicoManiac::killFunc(u32 funcType) {
		setNerve(NrvTicoManiacMeta);
		return true;
	}

	namespace NrvTicoManiac {
		void NrvMeta::execute(Spine *pSpine) const {
			TicoManiac* pActor = (TicoManiac*)pSpine->mExecutor;
			pActor->exeMeta();
		}

		NrvMeta(NrvMeta::sInstance);
	}
}
