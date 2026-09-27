#include "PADV-NEXT/defines.h"

ext volatile void FallPlatformPatch()
{
    asm("srwi r0, r0, 4\n andi. r0, r0, 0xF");
    asm("cmpwi r0, 0\n beq+ zero");
    asm("cmpwi r0, 1\n beq+ one");
    asm("cmpwi r0, 2\n beq- two");
    asm("cmpwi r0, 3\n beq- three");
    asm("b zero");

    asm("zero:\n lfs f1, 0x0028(r4)\n lfs f0, 0x002C(r4)\n stfs f2, 0xF4(r3)\n stfs f1, 0xF8(r3)\n stfs f2, 0xFC(r3)\nstfs	f0, 0x114(r3)\n blr");
    asm("one:\n lis	r4, 0x8096\naddi r4, r4, 28668\nlfs	f0, 0x0010(r4)\nstfs f0, 0x00F8(r3)\nstfs f2, 0x00F4(r3)\nstfs f2, 0x00FC(r3)\nlfs f0, 0x000C(r4)\nstfs	f0, 0x0114(r3)\n blr");
    asm("two:\n lfs f1, 0x0028(r4)\n fneg f1, f1\nlfs f0, 0x002C(r4)\n stfs f2, 0xF4(r3)\n stfs f1, 0xF8(r3)\n stfs f2, 0xFC(r3)\nstfs f0, 0x114(r3)\n blr");
    asm("three:\n lis r4, 0x8096\naddi r4, r4, 28668\nlfs f0, 0x0010(r4)\nfneg f0, f0\nstfs f0, 0x00F8(r3)\nstfs f2, 0x00F4(r3)\nstfs f2, 0x00FC(r3)\nlfs f0, 0x000C(r4)\nstfs f0, 0x0114(r3)\n blr");
}

ext void DeathMushHandler(dAcPy_c *toucher)
{
    asm("lwz r25, +0x04(r31)\nandi. r25, r25, 0xFF\ncmpwi r25, 0xF9\n bne+ skip");
    smitePlayer = (dEn_c *)toucher;
    asm("skip:");
    return;
}

kmBranchDefCpp(0x80837a80, NULL, void, void) { FallPlatformPatch(); }

kmBranchDefCpp(0x80147600, NULL, void, dAcPy_c *player) { DeathMushHandler(player); }
