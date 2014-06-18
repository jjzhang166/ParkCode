using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Diagnostics;

namespace WcfRoadService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public delegate void Test( int value );

    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession)]
    public class RoadService : IRoadService
    {
        static public Test t;

        public string GetData(int value)
        {
            if (null != t)
            {
                t( value );
            }

            return string.Format("You entered: {0}", value);
        }

        public string GetData1(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public void CenterCall()
        {
            Debug.Print( "Center call" );
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite == null)
            {
                throw new ArgumentNullException("composite");
            }
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }
    }
}
