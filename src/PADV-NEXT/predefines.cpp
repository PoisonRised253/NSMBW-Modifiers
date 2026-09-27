#include "PADV-NEXT/predefines.hpp"

// More CallsPerSecond = Less Calls. Basically inverted... Think 30 = 2 Calls/s
extern "C" bool CallSpacer(int callsPerSecond)
{
    return callsPerSecond && (FrameTimer % callsPerSecond == 0);
}

extern "C" u32 *GetMemberFromOffset(void *object, u32 offset)
{
    return (u32*)((unsigned char *)object + offset);
}