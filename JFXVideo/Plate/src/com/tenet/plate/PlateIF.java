/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.tenet.plate;

import com.sun.jna.*;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import com.sun.jna.examples.win32.GDI32;
import com.sun.jna.win32.StdCallLibrary;
import java.util.Arrays;
import java.util.List;
import com.sun.jna.examples.win32.GDI32.*;

/**
 *
 * @author Administrator
 */
public interface PlateIF extends StdCallLibrary {

    PlateIF INSTANCE = (PlateIF) Native.loadLibrary("LPKernelEx", PlateIF.class);

    public static class TH_RECT extends Structure {
        public int left;
        public int top;
        public int right;
        public int bottom;
        
        public static class ByValue extends PlateIF.TH_RECT implements Structure.ByValue {
        }

        public static class ByReference extends PlateIF.TH_RECT implements Structure.ByReference {
        }
    }

    public static class TH_PlateResult extends Structure {
        public byte[] license = new byte[16];// 车牌号码
        public byte[] color = new byte[8];      // 车牌颜色
        public int nColor;			// 车牌颜色序号
        public int nType;			// 车牌类型
        public int nConfidence;	// 车牌可信度
        public int nBright;		// 亮度评价
        public int nDirection;		// 运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down	
        public TH_RECT rcLocation = new TH_RECT(); //车牌位置
        public int nTime;          //识别所用时间
        public byte nCarBright;		//车的亮度
        public byte nCarColor;		//车的颜色
        public byte[] reserved = new byte[100];      // 车牌颜色
        
        public static class ByValue extends PlateIF.TH_PlateResult implements Structure.ByValue {
        }

        public static class ByReference extends PlateIF.TH_PlateResult implements Structure.ByReference {
        }
    }

//    boolean LPR_SetParameters(boolean bMovingImage,
//            int nPlatesNum,
//            boolean bFlipVertical,
//            int nColorOrder,
//            boolean bVertCompress,
//            int nImageplateThr, int nImageRecogThr,
//            int nMinPlateWidth, int nMaxPlateWidth,
//            byte[] LocalProvince,
//            boolean bDwordAligned,
//            boolean bInputHalfHeightImage,
//            boolean bOutputSingleFrame,
//            boolean bYellow2, boolean bIndivi, boolean bArmPol, boolean bArmy2, boolean bTractor,
//            boolean bNight,
//            int nChannel);

    boolean LPR_SetImageFormat(boolean bMovingImage,
            boolean bFlipVertical,
            int nColorOrder,
            boolean bVertCompress,
            int nMinPlateWidth,
            int nMaxPlateWidth,
            boolean bDwordAligned,
            boolean bInputHalfHeightImage,
            boolean bOutputSingleFrame,
            int nChannel);

    boolean LPR_SetPlateType(boolean bYellow2,
            boolean bIndivi,
            boolean bArmPol,
            boolean bArmy2,
            boolean bTractor,
            boolean bOnlyDyellow,
            boolean bEmbassy,
            boolean bDarmpolice,
            boolean bOnlyLocation,
            int nChannel);
//
//    boolean LPR_SetSpecialParameters(boolean bNight,
//            int nImageplateThr,
//            int nImageRecogThr,
//            int nPlatesNum,
//            byte[] LocalProvince,
//            int nChannel);

    boolean LPR_InitEx(int nChannel);

    void LPR_UninitEx(int nChannel);

//    boolean LPR_RGB888Ex(byte[] pImg, int nWidth, int nHeight, TH_PlateResult.ByReference pResult, int nRecogNum, TH_RECT.ByReference[] prcRange, int nChannel);
//
//    boolean LPR_GetImageBuf(byte[] pImageBuf, int nWidth, int nHeight, int nSize, int nChannel);
    
    boolean LPR_FileEx(String lpszFileName, String lpszPlateFile, TH_PlateResult[] pResult, byte[] nRecogNum, TH_RECT rect, int nChannel);
}
