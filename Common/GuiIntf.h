
//
//  common type definition
//
typedef unsigned int   HANDLE;
typedef char           CHAR;
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef double         FLOAT;



//
//  char string size definition
//
#define CARD_NO_MAX_SIZE            20              
#define CARD_INTERNEL_NO_MAX_SIZE   20
#define CARD_NOTES_MAX_SIZE         50
#define USER_NAME_MAX_SIZE          40
#define ADDRESS_NAME_MAX_SIZE       200
#define DOOR_MAX_SIZE               20
#define PORT_NAME_MAX_SIZE          20
#define CAR_PLATE_MAX_SIZE          30              
#define PATH_MAX_SIZE               255
#define FILE_NAME_MAX_SIZE          255
#define COUPON_NAME_MAX_SIZE        40
#define COUPTON_NOTES               50
#define LOG_CONTENTS_MAX_SIZE       200
#define PASSWORD_MAX_SIZE           40
#define DRIVING_LICENSE_MAX_SIZE    50
#define ID_MAX_SIZE                 20
#define TELEPHONE_MAX_SIZE          20
#define MOBILE_MAX_SIZE             20

//
// common MACRO definition
//

//#define  TRUE        1
//#define  FALSE       0

#define  P_SUCCESS            (0)
#define  P_ERROR              (-1)
#define  P_ERROR_SAME_ITEM    (-10)
#define  P_ERROR_NO_MORE_DATA (-11)

//
// 进出
//
#define  PORT_ENTRY                0
#define  PORT_EXIT                 1

//
// 卡类型
//
#define  CARD_MONTHLY_RENT         1
#define  CARD_STORED_VALUE         2
#define  CARD_TIMING               3

//
// 优惠类型
//
#define  COUPON_TYPE_NULL          1
#define  COUPON_TYPE_1             2
#define  COUPON_TYPE_2             3
#define  COUPON_TYPE_3             4

//
// 权限类型
//
#define  USER_PRIORITY_SYSTEM_MANAGER     1
#define  USER_PRIORITY_SUPER_USER         2
#define  USER_PRIORITY_HIGH_USER          3
#define  USER_PRIORITY_NORMAL_USER        4

//
// 性别
//
#define  GENDER_UNKNOWN                   0
#define  GENDER_MALE                      1
#define  GENDER_FEMALE                    2

//
// 记录类型
//
#define  RECORD_TYPE_SYSTEM_LOG           1          //system oeperator log
#define  RECORD_TYPE_PHOTO                2          //The photo card
#define  RECORD_TYPE_DEPOSIT              3          //The deposit 
#define  RECORD_TYPE_FLOW                 4          //The entry/exit record

//
// 车辆类型
//
#define  CAR_TYPE_MINI                    1           //mini vehicle volume < 1L
#define  CAR_TYPE_COMPACT                 2           //landaulet vehicle 1.0L < volume < 1.3L
#define  CAR_TYPE_IN_BETWEEN              3           //In-between vehicle
#define  CAR_TYPE_LARGE                   4           //oversize vehicle

//
// 卡状态
//
#define  CARD_STATUS_INVALID              0           //The card is invalid
#define  CARD_STATUS_VALID                1           //The card is valid




/////////////////////////////////////////////////////////////////////////////
//
// Open & close the interface of GUI <--> MAIN
//
HANDLE OpenInterface();

void   CloseInterface(HANDLE);












/////////////////////////////////////////////////////////////////////////////
// 
// Query and create the card information
//

typedef struct 
{
    U32  CardType;
    CHAR CardNo[CARD_NO_MAX_SIZE];
    CHAR CardInternalNo[CARD_INTERNEL_NO_MAX_SIZE];
    CHAR CarPlate[CAR_PLATE_MAX_SIZE];
    U32  CardMaterial;                                      //ID, IC ...
    U32  Status;                                            //if it's a valid card
    CHAR Notes[CARD_NOTES_MAX_SIZE];
    U32  TimeBegin;                                         //For monthly rent card
    U32  TimeEnd;                                           //For monthly rent card
    FLOAT Deposit;                                          //For stored value card
    U32  PayType;                                           //For stored value card How to pay
}t_Card;







//
// Query Card List
// return : 
//           the number of cards with the indicated type
//           0  -  no this type card
//           -1 -  query failed
//           
U32 QueryCardList(HANDLE handle, U32 type);


//
// Fetch one item from the result set of QueryCardList
// return : 
//          0  - success
//          -1 - no more data to fetch
//
U32 FetchCardList(HANDLE handle, t_Card * Card);


//
// Insert a new card or update a exist card into database
//
// parameter
//           force : 
//                  TRUE  - Force to update the item if the same card number exist in the database.
//                  FALSE - Don't update the item if the same card number exist in the database.
// return 
//           P_SUCCESS
//           P_ERROR
//           P_ERROR_SAME_ITEM. (when force == FALSE)
//
U32 InsCard(HANDLE handle, t_Card * Card, U32 force);


//
// Delete a card from database
//
U32 DelCard(HANDLE handle, CHAR * CardNo);





/////////////////////////////////////////////////////////////////////////////
//
//       Other information and operating attached with card
//
//


typedef struct
{
    CHAR CardNo[CARD_NO_MAX_SIZE];
    CHAR CarPlate[CAR_PLATE_MAX_SIZE];
    CHAR UserName[USER_NAME_MAX_SIZE];
    CHAR ID[ID_MAX_SIZE];                                //User ID Card Number
    U32  Gender;                                         //GENDER_UNKNOWN, GENDER_MALE, GENDER_FEMALE
    CHAR Telephone[TELEPHONE_MAX_SIZE];
    CHAR Mobile[MOBILE_MAX_SIZE];
    CHAR Address[ADDRESS_NAME_MAX_SIZE];
    CHAR Door[DOOR_MAX_SIZE];
    CHAR DrivingLicense[DRIVING_LICENSE_MAX_SIZE];
    U32  CarType;                                        //CAR_TYPE_MINI, CAR_TYPE_COMPACT, CAR_TYPE_IN_BETWEEN, CAR_TYPE_LARGE
    CHAR UserPhoto[FILE_NAME_MAX_SIZE];
}t_Customer;    


//
// Query Customer With Card
//
U32 QueryCustomerWithCard(HANDLE handle, CHAR * CardNo, t_Customer * Customer);


//
// Insert a new Customer or udpate a customer information With Card
//
// parameter
//           force : 
//                  TRUE  - Force to update the item if the same card user exist in the database.
//                  FALSE - Don't update the item if the same card user exist in the database.
// return 
//           P_SUCCESS
//           P_ERROR
//           P_ERROR_SAME_ITEM. (when force == FALSE)
//
U32 InsCustomer(HANDLE handle, t_Customer * Customer, U32 force);


//
// Delete a customer with card number from database
//
U32 DelCustomer(HANDLE handle, CHAR * CardNo);


typedef struct
{
    CHAR   CardNo[CARD_NO_MAX_SIZE];
    CHAR   CarPlate[CAR_PLATE_MAX_SIZE];
    CHAR   CardType;                              //CARD_MONTHLY_RENT,  CARD_STORED_VALUE
    FLOAT  Credit;                                //recharge credit
    U32    ExpiryDays;                            //period of validity [CARD_MONTHLY_RENT]
    U32    RechargeTime;                          //recharge time
    CHAR   Dutyman[USER_NAME_MAX_SIZE];           //dutyman to received the recharge credit
}t_Recharge;

//
// Recharge to the card
//
// return :
//         SUCCESS - Number of items returned
//         P_ERROR
U32 QueryRechargeRecord(HANDLE handle, CHAR * CardNo, U32 MaxItems);


//
// Fetch the result of QueryRechargeRecord()
//
// return :
//          P_SUCCESS
//          P_ERROR
//          P_ERROR_NO_MORE_DATA
//
U32 FetchRechargeRecord(HANDLE handle, t_Recharge * Recharge);



//
// Recharge to the card
//
// return :
//         P_SUCCESS 
//         P_ERROR 
//
U32 Recharge(HANDLE handle, t_Recharge * Recharge);




/////////////////////////////////////////////////////////////////////////////
//
//      payment, coupon config
//
// GUI modify the payment condition and coupon condition saving in the .conf file,
// then notify Main Control to reload the .conf file
// payment file : payment.conf
// coupon file : coupon.conf
//

//
// Notify Main Control module to reload the payment condition
//
U32 UpdatePayment();


// Notify Main Control module to reload the coupon condition
//
U32 UpdateCoupon();






/////////////////////////////////////////////////////////////////////////////
//
//    entry / exit record
//
//


typedef struct 
{
    CHAR CardNo[CARD_NO_MAX_SIZE];
    CHAR CarPlate[CAR_PLATE_MAX_SIZE];
    U32  PortType;                                //PORT_ENTRY or PORT_EXIT
    U32  CardType;                                //CARD_MONTHLY_RENT, CARD_STORED_VALUE, CARD_TIMING
    CHAR PortName[PORT_NAME_MAX_SIZE];
    U32  EntryTime;
    U32  ExitTime;
    FLOAT  Price;
    FLOAT  Payment;
    FLOAT  Coupon;
    U32    CouponType;
    CHAR   Dutyman[USER_NAME_MAX_SIZE];
}t_EntryExitRecord;


// 
// Query Entry and Exit record
// paramters:
//           CardNo    : number of card (It's invalid when it be set NULL)
//           CarPlate  : car plate (It's invalid when it be set NULL)
//           MaxItems  : get the max number of items which is the recently ones
// return :
//          items number when it queried successfully
//          P_ERROR   :  error happened
//
U32 QueryEntryExitRecord(HANDLE handle, CHAR * CardNo, CHAR * CarPlate, U32 MaxItems);



//
// Fetch an item from the result of QueryEntryExitRecord()
//
// return :
//         P_SUCCESS   
//         P_ERROR
//         P_ERROR_NO_MORE_DATA
//
U32 FetchEntryExitRecord(HANDLE handle, t_EntryExitRecord * Record);






/////////////////////////////////////////////////////////////////////////////
//
//  其他信息
//

typedef struct
{
    U32  Total;
    U32  Rest;
    U32  MonthlyCard;
    U32  StoredCard;
    U32  TimingCard;
    U32  Private;                   //user owned
}t_CarPortInfo;

//
//  Query Carport Information
//
U32 QueryCarPortInfo(HANDLE handle, t_CarPortInfo * CarPortInfo);




//
// Send pole command 道闸 开关
//
U32 SendCmdPoleUp(HANDLE handle, U32 Port);
U32 SendCmdPoleDown(HANDLE handle, U32 Port);

//
// Send Card dispenser command 发卡机 开关
//
U32 SendCmdCardDispenserOpen(HANDLE handle, U32 Port);
U32 SendCmdCardDispenserClose(HANDLE handle, U32 Port);



