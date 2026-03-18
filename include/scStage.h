#ifndef __H_SCSTAGE
#define __H_SCSTAGE

class dGameDisplay_c {
    public:
    void setTimer(int);
    int m_currentTime;
};

class dScStage_c
{
    static dScStage_c *m_instance;

public:
    static dScStage_c *instance()
    {
        return m_instance;
    }

    static void setStarCoinState(int coin, int state);

    static dGameDisplay_c* getGameDisplay();

    //This Might not truely be gamemode.
    static u32 m_gameMode;
    static u32 m_exitMode;

    u8 fill[0x22];
    u8 area;
    u8 fill2[0x44 - 0x23];
    u32 wmNode;
    u8 fill3[0x50 - 0x48];
    u32 enteredWorld;
    u32 enteredLevel;
};

#endif