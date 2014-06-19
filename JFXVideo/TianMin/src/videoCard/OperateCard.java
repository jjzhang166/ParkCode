/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package videoCard;

import java.lang.*;

import com.sun.jna.Native;
import com.sun.jna.NativeLong;
import com.sun.jna.Pointer;
import com.sun.jna.Structure;
import com.sun.jna.Union;
import com.sun.jna.examples.win32.GDI32.RECT;
import com.sun.jna.examples.win32.W32API;
import com.sun.jna.examples.win32.W32API.HWND;
import com.sun.jna.ptr.ByteByReference;
import com.sun.jna.win32.StdCallLibrary;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.NativeLongByReference;
import com.sun.jna.ptr.ShortByReference;

/**
 *
 * @author park
 */
public interface OperateCard extends StdCallLibrary {
    
    OperateCard INSTANCE = ( OperateCard ) Native.loadLibrary( "Sa7134Capture", OperateCard.class );
    
    public final int XVID_CBR_MODE = 0;
    public final int XVID_VBR_MODE = 1;
   
    public final int MPEG4_AVIFILE_ONLY = 0;
    public final int MPEG4_CALLBACK_ONLY = 1;
    public final int MPEG4_AVIFILE_CALLBACK = 2;
    
    public final int CAP_NULL_STREAM = 0;	
    public final int CAP_ORIGIN_STREAM = 1;
    public final int CAP_MPEG4_STREAM = 2;	
    public final int CAP_MPEG4_XVID_STREAM = 3;
    public final int CAP_ORIGIN_MPEG4_STREAM = 4;
    public final int CAP_ORIGIN_XVID_STREAM = 5;
    public final int CAP_WMV9_STREAM = 6;
    public final int CAP_ORIGIN_WMV9_STREAM = 7;

    
    public final int UYVY    = 0;
    public final int YUY2    = 1; 
    public final int Y41P    = 2; 
    public final int Y8      = 3; 
    public final int YV12    = 4; 
    public final int YU12    = 5; 
    public final int YVU9    = 6; 
    public final int RGB565  = 7; 
    public final int RGB888  = 8; 
    public final int RGB888a = 9; 
    public final int RGBa555 = 10;
    public final int GB55a5 = 11; 

    
    
    public final int NOT_DISPLAY = 0;
    public final int PCI_VIEDOMEMORY = 1;
    public final int PCI_MEMORY_VIDEOMEMORY = 2; 
    public final int PCI_OFFSCREEN_VIDEOMEMORY = 3;
    
    public static interface PrcVidMpegCallBack extends StdCallCallback {
        public void invoke( int dwCard, ByteByReference pbuff, int dwSize, boolean isKeyFrm );
    }


    // hWndMain:overlay窗口句柄，overlay窗口就是包含多路显示小窗口的大窗口。overlay窗口必须有一个，多路显示小窗口必须包含再其内部。
    public boolean VCAInitSdk( HWND hWndMain, int nDispTransType/* PCI_VIEDOMEMORY */, boolean bInitAudDev /* FALSE */  );
    public void VCAUnInitSdk( );
    
    public int VCAGetDevNum( );
    
    public boolean VCAOpenDevice( int dwCard, HWND hPreviewWnd );
    public boolean VCACloseDevice( int dwCard );
    public boolean VCAStartVideoPreview( int dwCard );
    public boolean VCAStopVideoPreview( int dwCard );
    public boolean VCAUpdateVideoPreview( int dwCard, HWND hPreviewWnd );
    public boolean VCAUpdateOverlayWnd(HWND hOverlayWnd);
    
    public boolean VCASaveAsJpegFile ( int dwCard, String lpFileName, int dwQuality /* 100 */  );
    
    public boolean VCAStartVideoCapture( int  dwCard, int enCapMode, int enMp4Mode, String lpFileName );
    public boolean VCAStopVideoCapture( int dwCard );

    public boolean VCAInitVidDev( int nDispTransType );
    public boolean VCAInitAudDev( );
    
    public boolean VCASetVidCapColorFormat( int dwCard, int cfColor );
    public boolean VCASetVidCapSize( int dwCard, int dwWidth, int dwHeight );
    
    public int VCAStartVideoCaptureEx( int dwCard );
    public int VCAStopVideoCaptureEx( int dwCard );
    
    public int VCACreateEnCodec( int dwCard, int enCapMode );
    public int VCACloseEnCodec( int dwCard );
    
    public int VCACreateAVIFile( int dwCard, String pFileName );
    public int VCACloseAVIFile( int dwCard );

    public boolean VCASetVidCapFrameRate( int dwCard, int dwFrameRate, boolean bFrameRateReduction );
    public boolean VCASetKeyFrmInterval( int dwCard, int dwKeyFrmInterval );
    public boolean VCASetBitRate( int dwCard, int dwBitRate );
    public boolean VCASetXVIDQuality( int dwCard, int dwQuantizer, int dwMotionPrecision );
    public boolean VCASetXVIDCompressMode( int dwCard, int enCompessMode );
    public int VCAWriteFrameToAVIFile( int dwCard, Pointer lpData, int lSize, int nFrameType );
    
    public boolean VCARegVidMpegCallBack( int dwCard, PrcVidMpegCallBack ppCall );

}
