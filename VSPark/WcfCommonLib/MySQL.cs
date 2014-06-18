using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Configuration;

namespace WcfCommonLib
{
    public class MySQLAccessor
    {
        private string strConnString = null;

        public MySQLAccessor()
        {
            strConnString = ConfigurationManager.ConnectionStrings["MySQL"].ConnectionString;
        }

        private void CreateParameter( MySqlCommand sqlCmd, object parmaValue, string strName, MySqlDbType dbType, System.Data.ParameterDirection paramDirect  )
        {
            MySqlParameter param = null;
            if (!sqlCmd.Parameters.Contains(strName))
            {
                param = sqlCmd.CreateParameter();
                param.ParameterName = strName;
                sqlCmd.Parameters.Add(param);
            }
            else
            {
                param = sqlCmd.Parameters[strName];
            }
            
            param.DbType = (System.Data.DbType)dbType;
            param.Value = parmaValue;
            param.Direction = paramDirect;
        }

        public void GetImage(string strWhere, out byte[ ] inImage, out byte[ ] outImage)
        {
            inImage = null;
            outImage = null;

            MySqlConnection sqlConn = new MySqlConnection(strConnString);
            MySqlCommand sqlCmd = sqlConn.CreateCommand();

            sqlConn.Open();
            sqlCmd.CommandType = System.Data.CommandType.StoredProcedure;
            sqlCmd.CommandText = "CenterQueryImage";
            CreateParameter(sqlCmd, strWhere, "@strRecordID", MySqlDbType.VarChar, System.Data.ParameterDirection.Input);
            CreateParameter(sqlCmd, null, "@inImage", MySqlDbType.LongBlob, System.Data.ParameterDirection.Output);
            CreateParameter(sqlCmd, null, "@outImage", MySqlDbType.LongBlob, System.Data.ParameterDirection.Output);
     
            sqlCmd.ExecuteNonQuery();

            object objImage = sqlCmd.Parameters["@inImage"].Value;
            if (null != objImage  && DBNull.Value != objImage) 
            {
                inImage =  ( byte[ ] ) objImage;
            }

            objImage = sqlCmd.Parameters["@outImage"].Value;
            if (null != objImage && DBNull.Value != objImage)
            {
                outImage = (byte[])objImage;
            }

            sqlCmd.Dispose();
            sqlConn.Close();
            sqlConn.Dispose();
        }

        public void DeleteUploadRecordData()
        {
            MySqlConnection sqlConn = new MySqlConnection(strConnString);
            MySqlCommand sqlCmd = sqlConn.CreateCommand();

            sqlCmd.CommandType = System.Data.CommandType.StoredProcedure;
            sqlCmd.CommandText = "DeleteUploadRecordData";

            sqlConn.Open();
            MySqlTransaction trans = sqlConn.BeginTransaction();
            Exception exRethrow = null;
            try
            {
                sqlCmd.Transaction = trans;
                sqlCmd.ExecuteNonQuery();
                trans.Commit();
            }
            catch (Exception ex)
            {
                trans.Rollback();
                exRethrow = ex;
            }

            trans.Dispose();
            sqlCmd.Dispose();
            sqlConn.Close();
            sqlConn.Dispose();

            if (null != exRethrow)
            {
                throw exRethrow;
            }
        }

        public void GetRecordData(StringBuilder builder)
        {
            // JSON Format
            // Convert to XML Format
            builder.Clear();

            MySqlConnection sqlConn = new MySqlConnection(strConnString);
            MySqlCommand sqlCmd = sqlConn.CreateCommand( );

            sqlCmd.CommandType = System.Data.CommandType.StoredProcedure;
            sqlCmd.CommandText = "UploadRecord2Center";
            CreateParameter(sqlCmd, null, "@record", MySqlDbType.LongText, System.Data.ParameterDirection.Output);

            sqlConn.Open();
            //MySqlDataReader reader = 
            MySqlTransaction trans = sqlConn.BeginTransaction();
            Exception exRethrow = null;
            try
            {
                sqlCmd.Transaction = trans;
                sqlCmd.ExecuteNonQuery();
                trans.Commit();
            }
            catch (Exception ex)
            {
                trans.Rollback();
                exRethrow = ex;
            }

            byte[] arrRecord = null;
            object objRecord = sqlCmd.Parameters["@record"].Value;
            if (null != objRecord && DBNull.Value != objRecord)
            {
                arrRecord = (byte[])objRecord;
            }
            if (null != arrRecord)
            {
                string strRecord = Encoding.UTF8.GetString(arrRecord);

                if ("|" != strRecord)
                {
                    builder.Append(strRecord);
                }
            }

            //reader.Close();
            //reader.Dispose();
            trans.Dispose();
            sqlCmd.Dispose();
            sqlConn.Close();
            sqlConn.Dispose();

            if (null != exRethrow)
            {
                throw exRethrow;
            }
        }

        public void WriteData(StringBuilder builder)
        {
            MySqlConnection sqlConn = new MySqlConnection(strConnString);
            MySqlCommand sqlCmd = sqlConn.CreateCommand();

            sqlCmd.CommandType = System.Data.CommandType.StoredProcedure;
            sqlCmd.CommandText = "DownloadFeeRate";
            //
            // MySQL 字符编码为UTF8
            // Encoding.UTF8 represents a UTF-8 encoding of Unicode characters.
            // GetBytes Encoding GetString Decoding
            // 字符(在字库中)-->编码(码表 内存表达)-->字符

            byte [] byUtf8 =  Encoding.UTF8.GetBytes( builder.ToString( ) );
            CreateParameter(sqlCmd, byUtf8, "@feeRate", MySqlDbType.LongText, System.Data.ParameterDirection.Input);

            sqlConn.Open();
            //MySqlDataReader reader = 
            MySqlTransaction trans = sqlConn.BeginTransaction();
            Exception exRethrow = null;
            try
            {
                sqlCmd.Transaction = trans;
                sqlCmd.ExecuteNonQuery();
                trans.Commit();
            }
            catch (Exception ex)
            {
                trans.Rollback();
                exRethrow = ex;
            }

            trans.Dispose();
            sqlCmd.Dispose();
            sqlConn.Close();
            sqlConn.Dispose();

            if (null != exRethrow)
            {
                throw exRethrow;
            }
        }
    }
}
