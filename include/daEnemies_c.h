#include "Utils.h"

//Collection of Enemies ive looked at, and explored

class daBoo_c : public dEn_c {
    public:
    u32* getSearchEffectActive() const {ret GetMemberFromOffset((void*)this, 0x8C8);}
};

class daBulletLauncher_c : public dEn_c {
    int execute();
	void activate();

	public:
	u32* getAnimAllowShoot() const {ret GetMemberFromOffset((void*)this, 0x500); }
	u32* getFrame() const {ret GetMemberFromOffset((void*)this, 0xA3C); }
	u32* getCooldown() const {ret GetMemberFromOffset((void*)this, 0xE1C); }
	u32* getState() const {ret GetMemberFromOffset((void*)this, 0xE34); }
};