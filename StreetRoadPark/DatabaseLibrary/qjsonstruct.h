#ifndef QJSONSTRUCT_H
#define QJSONSTRUCT_H

#include <QObject>
#include <Qtcore>
class JsonStruct {
public:
    typedef struct __JsonFomat {
        QString strFormat;
        QString strNumber;
        QString strCommasFormat;
        QString strCommasNumber;
        QString strLeftBracket;
        QString strRightBracket;
        QString strCommas;

        __JsonFomat( )
        {
            strFormat = "'%1'";
            strNumber = "%1";
            strCommasFormat = ",'%1'";
            strCommasNumber = ",%1";
            strLeftBracket = "(";
            strRightBracket = ")";
            strCommas = ",";
        }
    } JsonFomat, *PJsonFomat;

    typedef struct __JsonHead {
        struct __Keys {
            QString strClientID;
            QString strTypeCode;
            QString strData;
            QString strUserID;
            QString strStateCode;

            __Keys( )
            {
                strClientID = "ClientID";
                strTypeCode = "TypeCode";
                strData = "Data";
                strUserID = "UserID";
                strStateCode = "StateCode";
            }
        } sKeys;

        struct __Values {
            QString strClientID;
            QString strTypeCode;
            QString strUserID;
            QString strStateCode;
            QJsonObject jsonData;

            __Values( )
            {
                strClientID = "-1";
                strStateCode = "0";
            }
        } sValues;

        QString strLog;
        char nFlag;
        QString strSpName;
    } JsonHead, *PJsonHead;

    typedef struct __JsonGroup{
        JsonHead sHead;
        struct __JsonData {
            struct __Keys {
               QString strUnitID;
               __Keys( )
               {
                   strUnitID = "UnitID";
               }
            } sKeys;

            struct __Values {
                QString strUnitID;
            } sValues;
        } sData;
    } JsonGroup, *PJsonGroup;

    typedef struct __JsonUser{
        JsonHead sHead;
        struct __JsonData {
            struct __Keys {
                // UserSelect
               QString strGroupID;

               // UserUpdate UserLogin
               // UserLogout UserFee
               QString strUserID;
               QString strUserName;
               QString strUserPwd;
               QString strPwdMD5;
               QString strUserNewPwd;
               QString strPwdNewMD5;

               // UserFee
               QString strStartTime;
               QString strEndTime;

               __Keys( )
               {
                   strGroupID = "GroupID";

                   strUserID = "UserID";
                   strUserName = "UserName";
                   strUserPwd = "UserPwd";
                   strPwdMD5 = "PwdMD5";
                   strUserNewPwd = "UserNewPwd";
                   strPwdNewMD5 = "PwdNewMD5";

                   strStartTime = "StartTime";
                   strEndTime = "EndTime";
               }
            } sKeys;

            struct __Values {
                QString strGroupID;

                QString strUserID;
                QString strUserName;
                QString strUserPwd;
                QString strPwdMD5;
                QString strUserNewPwd;
                QString strPwdNewMD5;

                QString strStartTime;
                QString strEndTime;
            } sValues;
        } sData;
    } JsonUser, *PJsonUser;

    typedef struct __JsonInOutRecord {
        JsonHead sHead;
        struct __JsonData {
            struct __Keys {
               QString strRecordID;
               QString strLocationID;
               QString strPlate;
               QString strEnterPlate;
               QString strLeavePlate;
               QString strPayment;
               QString strPrepayment;
               QString strOperator;
               QString strPaymentOperator;
               QString strPrepaymentOperator;
               QString strPaymentTime;
               QString strPrepaymentTime;
               QString strImage;
               QString strEnterImage;
               QString strLeaveImage;
               QString strState;
               QString strEnterTime;
               QString strLeaveTime;
               QString strPrepaymentUserID;
               QString strPaymentUserID;

               QString strEnterStartTime;
               QString strEnterEndTime;
               QString strLeaveStartTime;
               QString strLeaveEndTime;
               QString strLimit;
               QString strIncludedImage;

               QString strPaymentStartTime;
               QString strPaymentEndTime;
               QString strUnitID;
               QString strParkID;

               QString strSrcLocationID;
               QString strDstLocationID;

               QString strFeeReceivable;
               QString strFreeType;
               QString strRecordType;

               QString strList;

               __Keys( )
               {
                   strRecordID = "RecordID";
                   strLocationID = "LocationID";
                   strPlate = "Plate";
                   strEnterPlate = "EnterPlate";
                   strLeavePlate = "LeavePlate";
                   strPayment = "Payment";
                   strPrepayment = "Prepayment";
                   strOperator = "Operator";
                   strOperator = "PrepaymentOperator";
                   strOperator = "PaymentOperator";
                   strPaymentTime = "PaymentTime";
                   strPrepaymentTime = "PrepaymentTime";
                   strImage = "Image";
                   strEnterImage = "EnterImage";
                   strLeaveImage = "LeaveImage";
                   strState = "State";

                   strEnterStartTime = "EnterStartTime";
                   strEnterEndTime = "EnterEndTime";
                   strLeaveStartTime = "LeaveStartTime";
                   strLeaveEndTime = "LeaveEndTime";
                   strLimit = "Limit";
                   strIncludedImage = "IncludedImage";

                   strPaymentStartTime = "PaymentStartTime";
                   strPaymentEndTime = "PaymentEndTime";
                   strUnitID = "UnitID";
                   strParkID = "ParkID";
                   strSrcLocationID = "SrcLocationID";
                   strDstLocationID = "DstLocationID";
                   strList = "List";

                   strEnterTime = "EnterTime";
                   strLeaveTime = "LeaveTime";
                   strPrepaymentUserID = "PrepaymentUserID";
                   strPaymentUserID = "PaymentUserID";

                   strFeeReceivable = "FeeReceivable";
                   strFreeType = "FreeType";
                   strRecordType = "RecordType";
               }
            } sKeys;

            struct __Values {
                QString strRecordID;
                QString strLocationID;
                QString strPlate;
                QString strEnterPlate;
                QString strLeavePlate;
                QString strPayment;
                QString strPrepayment;
                QString strOperator;
                QString strPaymentOperator;
                QString strPrepaymentOperator;
                QString strPaymentTime;
                QString strPrepaymentTime;
                QString strImage;
                QString strEnterImage;
                QString strLeaveImage;
                QString strState;
                QString strEnterTime;
                QString strLeaveTime;
                QString strPrepaymentUserID;
                QString strPaymentUserID;

                QString strEnterStartTime;
                QString strEnterEndTime;
                QString strLeaveStartTime;
                QString strLeaveEndTime;
                QString strLimit;
                QString strIncludedImage;

                QString strPaymentStartTime;
                QString strPaymentEndTime;
                QString strUnitID;
                QString strParkID;

                QString strSrcLocationID;
                QString strDstLocationID;

                QString strFeeReceivable;
                QString strFreeType;
                QString strRecordType;

                QString strList;
            } sValues;
        } sData;
    } JsonInOutRecord, *PJsonInOutRecord;

    typedef struct __JsonDeviceRecord {
        JsonHead sHead;
        struct __JsonData {
            JsonFomat sFormat;
            bool bRegister;
            struct __Keys {
               QString strDeviceID;
               QString strStartTime;
               QString strEndTime;
               QString strOperator;
               QString strComments;
               QString strUnitID;
               QString strSN;
               QString strList;

               __Keys( )
               {
                   strDeviceID = "DeviceID";
                   strStartTime = "StartTime";
                   strEndTime = "EndTime";
                   strOperator = "Operator";
                   strComments = "Comments";
                   strUnitID = "UnitID";
                   strSN = "SN";
                   strList = "List";
               }
            } sKeys;

            QStringList lstValues;
            struct __Values {
                QString strDeviceID;
                QString strStarTime;
                QString strEndTime;
                QString strOperator;
                QString strComments;
                QString strUnitID;
                QString strSN;
            } sValues;
        } sData;
    } JsonDeviceRecord, *PJsonDeviceRecord;

    typedef struct __JsonDataRecord {
        JsonHead sHead;
        struct __JsonData {
            struct __Keys {
               QString strDataType;

               __Keys( )
               {
                   strDataType = "DataType";
               }
            } sKeys;

            struct __Values {
                QString strDataType;
            } sValues;
        } sData;
    } JsonDataRecord, *PJsonDataRecord;

    typedef struct __JsonFeeRecord {
        JsonHead sHead;
        struct __JsonData {
            struct __Keys {
                QString strParkID;

               __Keys( )
               {
                   strParkID = "ParkID";
               }
            } sKeys;

            struct __Values {
                QString strParkID;
            } sValues;
        } sData;
    } JsonFeeRecord, *PJsonFeeRecord;
};

#endif // QJSONSTRUCT_H
