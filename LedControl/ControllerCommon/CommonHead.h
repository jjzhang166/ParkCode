#ifndef COMMONHEAD_H
#define COMMONHEAD_H

//
// Pure c data type
//

namespace LedControll {

const unsigned int  nLOCATION_SIZE = 128;

    typedef enum __EPath {
        PathConfig
    } EPath;

    typedef struct __SComConfig {
        unsigned char nComName;
        unsigned char nBaudRate;
        unsigned char nDataBit;
        unsigned char nParity;
        unsigned char nStopBit;
        unsigned char nFlowCtrl;
    } SComConfig;

    typedef struct __SNewSysConfig {
        unsigned char nFlashTime;
        unsigned char nFlashRadiance;
        unsigned char nFlashActivated;
        unsigned char nFlashSwitch;
        unsigned char nFlashMode;
        unsigned char nFrequencyTime;
        unsigned char nFrequencyRadiance;
        unsigned char nFrequencyActivated;
        unsigned char nFrequencySwitch;
        unsigned char nFrequencyMode;
        unsigned char nFrameFreqMode;
        wchar_t cLocation[ nLOCATION_SIZE ];
    } SNewSysConfig;

    typedef struct __SSysConfig {
        unsigned char nRunMode;
        unsigned char nSyncMode;
        unsigned char nBaseRadiance;
        unsigned char nActivatedSwitch;
        unsigned char nFrequencyTime;
        unsigned char nFrequencyRadiance;
        unsigned char nFlashTime;
        unsigned char nFlashRadiance;
        SNewSysConfig sNewConfig;
        wchar_t cLocation[ nLOCATION_SIZE ];
    } SSysConfig;

    typedef enum __ECommand {
        CmdFlashStateAlwaysRadianceChange, // Cmd 0x01
        CmdFlashFrenquencyIntensityTune, // 0x02
        CmdFlashGearSet, // 0x03
        CmdFrenquencyGearSet,
        CmdFlashFrenquencyGearClose, // 0x04
        CmdFlashGearAlwaysRadianceClose, // 0x05
        CmdFlashGearAlwaysRadianceOpen, // 0x06
        CmdFlashFrenquencyGearWorkTimeSet, // 0x07
        CmdFlashFrenquencyLightSensitiveIfWork, // 0x08
        CmdSyncModeDownTrigger, // 0x09
        CmdSyncModeUpTrigger,
        CmdSyncModeFollowTrigger,
        CmdSyncModeFollowDownTrigger,
        CmdTestFlashOpen,    // 0x0A
        CmdTestFlashClose,
        //CmdSyncModeForFreq,
        CmdSyncModeForFlash,
        CmdLedTemperature, // New Device
        CmdLedFrequency,
        CmdLedWorkVoltage,
        CmdLedExternalTriggerSignalState,
        CmdFlashRadianceChange,
        CmdFrenquencyRadianceChange,
        CmdTestConnect,
        CmdFrameFrequency
    } ECommand;
}

#endif // COMMONHEAD_H
