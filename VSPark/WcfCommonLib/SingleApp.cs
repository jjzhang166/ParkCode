using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace WcfCommonLib
{
    public static class SingleApp
    {
        //public SingleApp()
        //{
        //}

        const UInt32 ERROR_ALREADY_EXISTS = 0xB7;

        [DllImport( "kernel32.dll", CharSet = CharSet.Unicode )]
        private static extern IntPtr CreateEvent( IntPtr lpEventAttributes, Int32 bManualReset, Int32 bInitialState, string lpName );

        [DllImport( "kernel32.dll", CharSet = CharSet.Unicode )]
        private static extern UInt32 GetLastError();

        public static bool AppExist( string strGUID )
        {
            IntPtr hEvent = CreateEvent(IntPtr.Zero, 1, 0, strGUID);
            UInt32 nRet = GetLastError();

            return ERROR_ALREADY_EXISTS == nRet;
        }
    }
}
