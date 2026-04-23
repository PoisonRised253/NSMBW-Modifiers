#ifndef __H_SCSTAGE
#define __H_SCSTAGE

//Shorthand
typedef nw4r::g3d::Camera Camera;

class dGameDisplay_c
{
public:
    void setTimer(int);
    int m_currentTime;
};

class dScStage_c
{
    static dScStage_c *m_instance;

    enum Exit {
        EXIT_DEFAULT = 0,
        EXIT_FAIL,
        EXIT_SUCCESS,
        EXIT_PLAYER_CHOICE = 3
    };

public:
    static dScStage_c *instance()
    {
        return m_instance;
    }

    static void setStarCoinState(int coin, int state);

    static dGameDisplay_c *getGameDisplay();

    // This Might not truely be gamemode.
    static u32 m_gameMode;
    static u32 m_exitMode;
    static u32 sc_CannonNextWorld;

    u8 fill[0x22];
    u8 area;
    u8 fill2[0x44 - 0x23];
    u32 wmNode;
    u8 fill3[0x50 - 0x48];
    u32 enteredWorld;
    u32 enteredLevel;

    void setCamera(Camera c); //Camera instance can be obtained using this->getCamera(GetCurrentCamera())
    Camera* getCamera(int camIDProbs); //Possibly input from GetCurrentCameraID()
    void setLoopType(int unk);
    void getLoopPosX(float unk);
    void setChangePosFunc(int unk);
    void changePosNormal(Vec3* unk);
    void changePosLoop1(Vec* unk);
    void addUnitTexArcList(char* name);
    void deleteUnitTexArcList();
    void addObjectArcList(const char* name);
    void deleteObjectArcList();
    void addObjectArcListEx(const char* name);
    void deleteObjectArcListEx();
    void addBossEffResList(int unk); //Likely ID (Boss)
    void deleteBossEffResList();
    void deleteReplayPlay();
    void play();
    bool isNowReplay();
    void ReplayEnd();
    void calcTitleSwitchCount();
    void calcTitleCount();
    void setTitleReplayRandomTable();
    u32 getExitMode();

    void setNextScene(unsigned short unk, int unk2, Exit exitValue);

    void *mCdArcName;
    void *m_unit_res_list;
    void *m_object_res_list;
    void *m_objectEx_res_list;
    void *m_boss_eff_list;
    void *mCollectionCoin;
    void *m_titleRandomTable;
    void *m_replayPlay_p;

    float m_otehonTimer;
    void *m_startFadeType;

    Camera *m_camera;
    void* mDummyActor;
    s64* m_stageFlag_p[2];
    void *m_BgParameter_p;
    void *m_swichflag_p;
    void *m_actorGroup_p;
    void *m_actorCreate_p;
    void *m_objblock_p;
    bool* m_balloon_p; // Only Maybe Bool
    void *m_center_save_p;
    bool* m_OtehonClear_p; // Only Maybe Bool
    s32 m_titleSwitchCount;
    s32 m_titleCount;
    s32 m_goalType;
    s32 m_exeFrame;
    static u32 m_loopType;
    void *m_unit_res_num;
    void *m_object_res_num;
    void *m_objectEx_res_num;
    void *m_boss_eff_num;
    bool m_isCourseIn;
    bool m_isCourseOut;
    bool m_isOtehonReturn;
    bool m_isStaffCredit;
    bool m_miniGame;
    bool m_replayMode;
    void *m_unitcol_pat;
    bool m_isReplayGoal;
    void* m_KoopaJrEscape; //Maybe Bool
    void* changePos;
    void* m_pReplayDataHeap;
};

#endif