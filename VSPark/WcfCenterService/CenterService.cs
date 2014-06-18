using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using Newtonsoft.Json;
using System.IO;
using System.Configuration;
using WcfCommonLib;
using System.Data;
using System.Xml;

namespace WcfCenterService
{
    // > PM Install-Package Newtonsoft.Json
    //http://james.newtonking.com/json/help/index.html
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public delegate void LogCallback( object strLog );

    [ServiceBehavior(InstanceContextMode = InstanceContextMode.PerSession)]
    public class CenterService : ICenterService
    {
        static public LogCallback logCB = null;
        private string strImagePath = null;
        private SQLServerAccessor dbSQLServer = new SQLServerAccessor(); 

        public CenterService()
        {
            strImagePath = ConfigurationManager.AppSettings.Get("ImagePath");
            if (null == strImagePath)
            {
                strImagePath = "c:\\";
            }

            if ( !Directory.Exists( strImagePath ) ) {
                Directory.CreateDirectory(strImagePath);
            }
        }

        //
        // Get vehicle record image
        // Get peer socket by strLocationID 
        // Get an image from roadserver by strRecordID, bEnter
        //

        private void DisplyaLog(object strLog)
        {
            if (null != logCB)
            {
                logCB(strLog);
            }
        }
        public void  UploadInOutImage( string strLocationID, string strRecordID, byte[ ] inImage, byte[ ] outImage )
        //public void UploadInOutImage(string strLocationID, string strRecordID, MemoryStream streamInImage, MemoryStream streamOutImage )
        //public void UploadInOutImage(byte[] inImag)
        {
            StringBuilder builder = new StringBuilder();

            try {
                if (null != inImage)
                {
                    GetFileName(builder, strLocationID, strRecordID, true);
                    SaveFile(builder, inImage);
                }

                if (null != outImage)
                {
                    GetFileName(builder, strLocationID, strRecordID, false);
                    SaveFile(builder, outImage);
                }
            } catch( Exception ex ) {
                DisplyaLog(CommonFunction.GetExceptionMessage(ex));
            }
        }

        private void SaveFile(StringBuilder strName, byte[] image)
        {
            string strFile = strImagePath + strName.ToString( );
            FileInfo info = new FileInfo(strFile);

            if (info.Exists && 0 != info.Length )
            {
                return;
            }

            info = null;

            File.WriteAllBytes(strFile, image );
        }

        private void GetFileName(StringBuilder builder, string strLocationID, string strRecordID, bool bEnter )
        {
            builder.Clear();
            builder.Append(strLocationID);
            builder.Append("_");
            builder.Append(strRecordID);
            builder.Append("_");
            builder.Append(bEnter ? "1" : "0" );
            builder.Append(".JPG");
        }

        public StringBuilder GetFeeData(string strParkID)
        {
            StringBuilder builder = null;
            try
            {
                builder = dbSQLServer.GetFeeRateData(strParkID);
                DisplyaLog("【下载费率】" + builder.ToString( ));
            }
            catch (Exception ex)
            {
                DisplyaLog(CommonFunction.GetExceptionMessage(ex));
            }

            return builder;
        }

        public void UploadRecordData2(DataTable table)
        {
            try
            {
                dbSQLServer.WriteRecordData(table);
                DisplyaLog("【上传数据】" + table.ToString( ));
            }
            catch (Exception ex)
            {
                DisplyaLog(CommonFunction.GetExceptionMessage(ex));
            }
        }

        private DataTable CreateInOutTable(XmlDocument doc)
        {
            DataTable table = new DataTable(doc.DocumentElement.Name);

            table.Columns.Add("RecordID", typeof(UInt64));
            table.Columns.Add("LocationID", typeof(string));
            table.Columns.Add("EnterTime", typeof(string));
            table.Columns.Add("LeaveTime", typeof(string));
            table.Columns.Add("EnterPlate", typeof(string));
            table.Columns.Add("LeavePlate", typeof(string));
            table.Columns.Add("State", typeof(Int16));

            StringReader reader = new StringReader(doc.OuterXml);
            table.ReadXml(reader);

            reader.Close();
            reader.Dispose();
            
            return table;
        }

        private DataTable CreateFeeTable(XmlDocument doc)
        {
            DataTable table = new DataTable(doc.DocumentElement.Name);
            table.Columns.Add("LocationID", typeof(string));
            table.Columns.Add("RecordID", typeof(UInt64));
            table.Columns.Add("FreeType", typeof(string));
            table.Columns.Add("Prepayment", typeof(Int16));
            table.Columns.Add("Payment", typeof(Int16));
            table.Columns.Add("FeeReceivable", typeof(Int16));
            //table.Columns.Add("PrepaymentOperator", typeof(string));
            table.Columns.Add("PrepaymentTime", typeof(string));
            table.Columns.Add("PaymentTime", typeof(string));
            //table.Columns.Add("PaymentOperator", typeof(string));
            table.Columns.Add("PrepaymentUserID", typeof(string));
            table.Columns.Add("PaymentUserID", typeof(string));
            //table.Columns.Add("FreeType", typeof(Int16));

            StringReader reader = new StringReader(doc.OuterXml);
            table.ReadXml(reader);

            reader.Close();
            reader.Dispose();

            return table;
        }

        DataTable CreateTable(String json)
        {
            System.Diagnostics.Debug.Print(json);
            XmlDocument doc = JsonConvert.DeserializeXmlNode(json);

            String strName = doc.DocumentElement.Name;
            DataTable table = null;

            System.Diagnostics.Debug.Print(doc.OuterXml);

            if ("zd_jccwxx" == strName.ToLower())
            {
                //table = CreateInOutTable(doc);
                table = new DataTable(strName);
                dbSQLServer.WriteRecordData(doc.OuterXml);
            }
            else if ("zd_ysfxx" == strName.ToLower())
            {
                table = CreateFeeTable(doc);
            }

            return table;
        }

        public void UploadRecordData(StringBuilder builder)
        {
            String strJson = builder.ToString();
            string[] strJsons = strJson.Split(new char[] { '|' });
            if (null == strJsons || 0 == strJsons.Length) 
            {
                return;
            }
            
            DataTable table =null;

            try
            {
                foreach (string json in strJsons)
                {
                    if (string.Empty == json)
                    {
                        continue;
                    }

                    table = CreateTable(json);
                    if (null == table)
                    {
                        continue;
                    }

                    dbSQLServer.WriteRecordData(table);
                    DisplyaLog("【上传数据】" + table.ToString());
                }
            }
            catch (Exception ex)
            {
                DisplyaLog(CommonFunction.GetExceptionMessage(ex));
            }
        }

        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
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
