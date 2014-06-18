using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Data.SqlClient;
using System.Data;

namespace WcfCommonLib
{
    public class SQLServerAccessor
    {
#if false
        CREATE TABLE #MyTempTable current session(删除表定义)
        Oracle临时表分为会话级临时表和事务级临时表(不删除表定义)

        CREATE TABLE ##MyTempTable Global( All Sessions)
        Oracle 采用永久表，在表内采用会话标识来加以区分，会话结束时清除数据
        SQL Server / Oracle Instance
        Each installation is called an instance
        computerName\instanceName

        USE [ParkDb]
GO
/****** 对象:  Table [dbo].[FeeRateResult]    脚本日期: 11/06/2013 16:15:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[FeeRateResult](
	[FeeRate] [text] COLLATE Chinese_PRC_CI_AS NULL CONSTRAINT [DF_FeeRateResult_FeeRate]  DEFAULT (''),
	[ID] [int] NOT NULL CONSTRAINT [DF_FeeRateResult_Key]  DEFAULT ((1))
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

        -- READTEXT UPDATETEXT WRITETEXT
        ALTER PROCEDURE [dbo].[GetFeeRate]
	@ParkID varchar(45),
	@FeeData varchar(max) output
AS
BEGIN
	declare ResultData CURSOR for select '("' +  convert( varchar(128 ), ID ) + '","' + ccbh + '")' from parkdb.dbo.jccxx;-- where ID < 23289;
	declare @RowData varchar(1024);
	--DECLARE @ptrval binary(16);
	declare @ByteLen int;
	declare @TmpLen int;
	declare @First tinyint;

	SET NOCOUNT ON;

	CREATE TABLE #FeeRateResult(
	[FeeRate] varchar(max) COLLATE Chinese_PRC_CI_AS NULL CONSTRAINT [DF_FeeRateResult_FeeRate]  DEFAULT (''),
	[ID] [int] NOT NULL CONSTRAINT [DF_FeeRateResult_Key]  DEFAULT ((1))
	) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY];

	insert #FeeRateResult( ID, FeeRate ) Values( 1, '' );

	--select @ptrval = TEXTPTR( FeeRate ) from #FeeRateResult;
	select @ByteLen = 0;
	select @TmpLen = 0;
	set @First = 1;

	open ResultData;
	fetch next from ResultData into @RowData;
	
	while 0 = @@fetch_status
	begin
		if ( 0 = @First ) set @RowData = ',' + @RowData;--SELECT STUFF(@RowData, 1, 0, ',');
		--updatetext #FeeRateResult.FeeRate @ptrval @ByteLen 0 @RowData;
		UPDATE #FeeRateResult set FeeRate .write( @RowData, @ByteLen, 0 ) where ID = 1;
		--select @TmpLen = Len( @RowData );
		select @TmpLen = DATALENGTH( @RowData );
		fetch next from ResultData into @RowData;
		select @ByteLen = @ByteLen + @TmpLen;
		set @First = 0;
	end

	close ResultData;
	Deallocate ResultData;

	select @FeeData = FeeRate from #FeeRateResult;
	--select FeeRate from #FeeRateResult;
END

        ALTER PROCEDURE [dbo].[InOutXML]
	@RecordXML xml
AS
BEGIN
	DECLARE 
    @nItem INT, 
    @nTotal INT,
	--@RecordXML xml,
	@Row XML,

	@RecordID varchar(64),
	@LocationID varchar(64),
	@EnterTime varchar(64),
	@LeaveTime varchar(64),
	@EnterPlate varchar(64),
	@LeavePlate varchar(64),
	@State varchar(64);

	--select @RecordXML = '<TestUpload><TestUpload><RecordID>39</RecordID><LocationID>5101070001001006</LocationID><EnterTime>2013-11-01 17:00:53</EnterTime><LeaveTime>2013-11-01 17:00:56</LeaveTime><EnterPlate>1123</EnterPlate><LeavePlate>川A12456</LeavePlate><State>1</State></TestUpload><TestUpload><RecordID>40</RecordID><LocationID>5101070001001006</LocationID><EnterTime>2013-11-01 17:00:53</EnterTime><LeaveTime>2013-11-01 17:00:56</LeaveTime><EnterPlate>1123</EnterPlate><LeavePlate>川A12456</LeavePlate><State>1</State></TestUpload></TestUpload>';
 
	SELECT @nItem = 1, @nTotal = @RecordXML.value( 'count(/TestUpload/TestUpload)','INT' );

	WHILE @nItem <= @nTotal BEGIN
		SELECT @Row = @RecordXML.query('/TestUpload/TestUpload[position()=sql:variable("@nItem")]');

		select  @RecordID = CAST( T.C.query('/TestUpload/RecordID/text( )') as VARCHAR(64) ),
			    @LocationID = CAST( T.C.query('/TestUpload/LocationID/text( )') as VARCHAR(64) ),
				@EnterTime = CAST( T.C.query('/TestUpload/EnterTime/text( )') as VARCHAR(64) ),
				@LeaveTime = CAST( T.C.query('/TestUpload/LeaveTime/text( )') as VARCHAR(64) ),
				@EnterPlate = CAST( T.C.query('/TestUpload/EnterPlate/text( )') as VARCHAR(64) ),
				@LeavePlate = CAST( T.C.query('/TestUpload/LeavePlate/text( )') as VARCHAR(64) ),
				@State = CAST( T.C.query('/TestUpload/State/text( )') as VARCHAR(64) ) from @Row.nodes('.') as T(C);
/*
		PRINT 'RecordID: ' + @RecordID;
		PRINT 'LocationID: ' + @LocationID;
		PRINT 'EnterTime: ' + @EnterTime;
		PRINT 'LeaveTime: ' + @LeaveTime;
		PRINT 'EnterPlate: ' + @EnterPlate;
		PRINT 'LeavePlate: ' + @LeavePlate;
		PRINT 'State: ' + @State;
		PRINT '';
*/
		if '' = @LeaveTime select @LeaveTime = null;
		if '' = @EnterPlate select @EnterPlate = null;
		if '' = @LeavePlate select @LeavePlate = null;

		IF EXISTS ( SELECT RecordID, LocationID FROM TestUpload WHERE RecordID = @RecordID and LocationID = @LocationID )
			update TestUpload set LeaveTime = @LeaveTime, LeavePlate = @LeavePlate, State = @State where  RecordID = @RecordID and LocationID = @LocationID;
		else
			Insert into TestUpload( RecordID, LocationID, EnterTime, LeaveTime, EnterPlate, LeavePlate, State ) 
                        values( @RecordID, @LocationID, @EnterTime, @LeaveTime, @EnterPlate, @LeavePlate, @State );
		SELECT @nItem = @nItem + 1;
	END
END
#endif
        // RowType TableType 行变量 表变量
        //UI<-->DataRowView(DataRow)<-->DataView(DataRowView)
        //(各种操作功能-插入 删除 编辑 排序 多视图模式 部分浏览等等)
        //<-->DataTable(DataRow DataColumn)
        //<-->DataSet(MemoryDatabase)<-->DataAdapter(SqlCommandBuilder 自动产生动作查询命令)
        //<-->SqlCommand(Select Update Insert Delete)
        //<-->SqlConnect<-->Database
        private string strConnString = null;

        public SQLServerAccessor()
        {
            strConnString = ConfigurationManager.ConnectionStrings["SQLServer"].ConnectionString;
        }

        private void CreateParameter(SqlCommand sqlCmd, object parmaValue, string strName, SqlDbType dbType, int nSize, System.Data.ParameterDirection paramDirect)
        {
            SqlParameter param = null;
            if (!sqlCmd.Parameters.Contains(strName))
            {
                param = new SqlParameter(strName, dbType, nSize);
                sqlCmd.Parameters.Add(param);
            }
            else
            {
                param = sqlCmd.Parameters[strName];
            }

            param.Value = parmaValue;
            param.Direction = paramDirect;
        }

        public StringBuilder GetFeeRateData(string strParkID)
        {
            SqlConnection sqlConn = new SqlConnection(strConnString);
            SqlCommand sqlCmd = sqlConn.CreateCommand( );
            sqlCmd.Connection = sqlConn;

            sqlCmd.CommandType = CommandType.StoredProcedure;
            sqlCmd.CommandText = "GetFeeRate";

            //http://msdn.microsoft.com/en-us/library/bb399384(v=vs.110).aspx
            //varchar(max), nvarchar(max), or varbinary(max)
            CreateParameter(sqlCmd, strParkID, "@ParkID", SqlDbType.VarChar, 45, ParameterDirection.Input);
            CreateParameter(sqlCmd, null, "@FeeData", SqlDbType.VarChar, -1, ParameterDirection.Output);

            sqlConn.Open();

            SqlTransaction trans = sqlConn.BeginTransaction();
            sqlCmd.Transaction = trans;
            Exception exRethrow = null;
            try
            {
                sqlCmd.ExecuteNonQuery();
                trans.Commit();
            }
            catch (Exception ex)
            {
                trans.Rollback();
                exRethrow = ex;
            }

            StringBuilder builder = new StringBuilder();
            object objRecord = sqlCmd.Parameters["@FeeData"].Value;
            if (null != objRecord && DBNull.Value != objRecord)
            {
                builder.Append(objRecord.ToString( ));
            }
            
            trans.Dispose();
            sqlCmd.Dispose();
            sqlConn.Close();
            sqlConn.Dispose();

            if (null != exRethrow)
            {
                throw exRethrow;
            }

            return builder;
        }

        public void WriteRecordData(DataTable table)
        {
            if (null == table || 0 == table.Rows.Count)
            {
                return;
            }
            // Inset Value( )
            // Insert Values( )
            // BulkCopy
            // Table Value Parameters 2008
            // Create Table IGNORE_DUP_KEY = { ON | OFF } set ON 忽略主键重复问题
            SqlBulkCopy sqlBulk = new SqlBulkCopy(strConnString, SqlBulkCopyOptions.KeepIdentity);
            sqlBulk.BulkCopyTimeout = 60;
            sqlBulk.DestinationTableName = table.TableName;
            sqlBulk.BatchSize = table.Rows.Count;
            sqlBulk.WriteToServer(table);
            sqlBulk.Close();
        }

        public void WriteRecordData(string strXml)
        {
            if (null == strXml || string.Empty == strXml)
            {
                return;
            }

            SqlConnection sqlConn = new SqlConnection(strConnString);
            SqlCommand sqlCmd = sqlConn.CreateCommand();
            sqlCmd.Connection = sqlConn;

            sqlCmd.CommandType = CommandType.StoredProcedure;
            sqlCmd.CommandText = "InOutXML";


            CreateParameter(sqlCmd, strXml, "@RecordXML", SqlDbType.Xml, -1, ParameterDirection.Input);

            sqlConn.Open();

            SqlTransaction trans = sqlConn.BeginTransaction();
            sqlCmd.Transaction = trans;
            Exception exRethrow = null;
            try
            {
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
