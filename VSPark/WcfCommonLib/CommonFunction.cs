using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WcfCommonLib
{
    public static class CommonFunction
    {
        public static StringBuilder GetExceptionMessage(Exception ex)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append("Exception Message ");
            builder.Append(ex.Message);
            builder.Append("\nCall stack ");
            builder.Append(ex.StackTrace);

            return builder;
        }
    }
}
