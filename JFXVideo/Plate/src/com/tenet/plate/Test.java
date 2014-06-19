/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.tenet.plate;

import com.sun.jna.examples.win32.GDI32;
import java.util.Arrays;

/**
 *
 * @author Administrator
 */
public class Test {

    public static void main(String[] args) {
        go(0, "D:\\WinParkUI\\JFXVideo\\Plate\\test.jpg");
    }

    private static boolean go(int argc, String argv) {
        boolean b;
        String image_path = argv;
        // 通道号
        int nchannel = 1;
        // 初始化车牌识别
        b = PlateIF.INSTANCE.LPR_SetImageFormat(false, false, 1, false, 80, 400, true, false, true, nchannel);
        if (!b) {
            return false;
        }

        b = PlateIF.INSTANCE.LPR_InitEx(nchannel);
        if (!b) {
            return false;
        }

        b = PlateIF.INSTANCE.LPR_SetPlateType(false, false, false, false, false, false, false, false, false, nchannel);
        if (!b) {
            return false;
        }

        PlateIF.TH_RECT rcRange = new PlateIF.TH_RECT( );
        rcRange.bottom = 0;
        rcRange.left = 0;
        rcRange.right = 0;
        rcRange.top = 0;

        PlateIF.TH_PlateResult.ByValue sResult = new PlateIF.TH_PlateResult.ByValue( );
        PlateIF.TH_PlateResult.ByValue[] iresult = ( PlateIF.TH_PlateResult.ByValue[]) sResult.toArray( 6 );
        for (int i = 0; i < iresult.length; i++) {
            //iresult[i] = new PlateIF.TH_PlateResult( );
            iresult[i].license = new byte[16];          // 车牌号码
            iresult[i].color = new byte[8];             // 车牌颜色
            iresult[i].nColor = 0;			// 车牌颜色序号
            iresult[i].nType = 0;			// 车牌类型
            iresult[i].nConfidence = 0;	// 车牌可信度
            iresult[i].nBright = 0;		// 亮度评价
            iresult[i].nDirection = 0;		// 运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down	
            //iresult[i].rcLocation.;
            iresult[i].nTime = 0;          //识别所用时间
            iresult[i].nCarBright = (byte) 0;		//车的亮度
            iresult[i].nCarColor = (byte) 0;		//车的颜色
            iresult[i].reserved = new byte[100];        //保留
        }
        byte[] nRecoNum = new byte[4];
        // 设置车牌识别区域，默认是全图识别

        b = PlateIF.INSTANCE.LPR_FileEx(image_path, null, iresult, nRecoNum, rcRange, nchannel);
        if (!b) {
            System.out.println("false");
            return false;
        }
        for (int i = 0; i < 6; i++) {
            System.out.println("*** 识别结果:\n" + Arrays.toString(iresult[i].license));
        }
        PlateIF.INSTANCE.LPR_UninitEx(argc);
        return false;
    }
}
