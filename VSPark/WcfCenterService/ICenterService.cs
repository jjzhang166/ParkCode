using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.IO;
using System.Data;

namespace WcfCenterService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface ICenterService
    {
        //
        // Get vehicle record image
        //
        
        [OperationContract(IsOneWay=true)]
        void UploadInOutImage( string strLocationID, string strRecordID, byte[] inImage, byte[] outImage);
        //void UploadInOutImage(string strLocationID, string strRecordID, MemoryStream streamInImage, MemoryStream streamOutImage );
        //void UploadInOutImage(byte[] inImag);

        [OperationContract(IsOneWay=false)]
        StringBuilder GetFeeData(string strParkID);

        [OperationContract(IsOneWay = true)]
        void UploadRecordData2(DataTable table);

        [OperationContract(IsOneWay = true)]
        void UploadRecordData(StringBuilder builder);

        [OperationContract]
        string GetData(int value);

        [OperationContract]
        CompositeType GetDataUsingDataContract(CompositeType composite);

        // TODO: Add your service operations here
    }

    // Use a data contract as illustrated in the sample below to add composite types to service operations
    [DataContract]
    public class CompositeType
    {
        bool boolValue = true;
        string stringValue = "Hello ";

        [DataMember]
        public bool BoolValue
        {
            get { return boolValue; }
            set { boolValue = value; }
        }

        [DataMember]
        public string StringValue
        {
            get { return stringValue; }
            set { stringValue = value; }
        }
    }
}
