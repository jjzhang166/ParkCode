#ifndef ENUMTYPE_H
#define ENUMTYPE_H

// 抽象命令类型
typedef enum __CmdType {
    CmdNone,
    CmdWriteCardID,
    CmdReadCardID,
    //票箱地感
    CmdInBallotSenseEnter, //车辆进入
    CmdInBallotSenseLeave, //车辆离开
    CmdOutBallotSenseEnter, //车辆进入
    CmdOutBallotSenseLeave, //车辆离开
    //道闸地感
    CmdInGateSenseEnter, //车辆进入
    CmdInGateSenseLeave, //车辆离开
    CmdOutGateSenseEnter, //车辆进入
    CmdOutGateSenseLeave, //车辆离开
    //开关闸
    CmdInOpenGate, //入口开闸
    CmdOutOpenGate,
    CmdInCloseGate,
    CmdOutCloseGate
} CmdType;

typedef enum __CtrlType {
    CtrlXw,
    CtrlVz
} CtrlType;

#endif // ENUMTYPE_H
