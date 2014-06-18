#include <QCoreApplication>

#include <stddef.h>
#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WIN__)
#include <winsock.h>
#endif

#include "mysql.h"
#include "errmsg.h"

#include <QtDebug>
#include <QDateTime>

static void test_error(MYSQL *mysql, int status)
{
  if (status)
  {
    fprintf(stderr, "Error: %s (errno: %d)\n",
            mysql_error(mysql), mysql_errno(mysql));
    exit(1);
  }
}

static void test_stmt_error(MYSQL_STMT *stmt, int status)
{
  if (status)
  {
    fprintf(stderr, "Error: %s (errno: %d)\n",
            mysql_stmt_error(stmt), mysql_stmt_errno(stmt));
    exit(1);
  }
}

#if true
int main(int argc, char *argv[])
{
    QDateTime dt = QDateTime::fromMSecsSinceEpoch( 1364131723 );
    qDebug( ) << dt.toString( ) << dt.toMSecsSinceEpoch( ) << endl;

    QCoreApplication a(argc, argv);
    MYSQL* mysql = mysql_init( 0 );
    mysql_real_connect( mysql, "127.0.0.1",
                                       "root", "root",
                                       "StreetRoadPark",
                                       3306, 0, CLIENT_MULTI_STATEMENTS );

    MYSQL_STMT *stmt;
    MYSQL_BIND ps_params[2];  /* input parameter buffers */
    int        status;
    ulong lRealLength = 0;


    stmt = mysql_stmt_init(mysql);

    char nInFlag = 25;
    char nOutFlag = 0;
    char cInBlob[ 1024 ];
    char cOutBlob[ 1024 ];
    strcpy( cInBlob, "jadfhai;fjsdfhnkcjk;oafjksdfklj;fdjkl;sfk;ff;skl;nvldfklfdkldflmfdlmvklnfvdnklljk;dskldsn" );

    status = mysql_stmt_prepare(stmt, "CALL TabletRecord(?, ?)", 23);
    int nCount = 1000;

    while( nCount-- ) {
        /* initialize parameters: p_in, p_out, p_inout (all INT) */
        memset(ps_params, 0, sizeof (ps_params));
        lRealLength = 0;

        ps_params[0].buffer_type = MYSQL_TYPE_LONG_BLOB;
        ps_params[0].buffer = cInBlob;
        ps_params[0].length = 0;
        ps_params[0].is_null = 0;

        ps_params[1].buffer_type = MYSQL_TYPE_TINY;
        ps_params[1].buffer = &nInFlag;
        ps_params[1].length = 0;
        ps_params[1].is_null = 0;

        status = mysql_stmt_bind_param(stmt, ps_params);

        status = mysql_stmt_send_long_data( stmt, 0, cInBlob, strlen( cInBlob ) );

        status = mysql_stmt_execute(stmt);

        do {
            if ( mysql_stmt_field_count(stmt) > 0 ) {
            memset(ps_params, 0, sizeof (ps_params));
            memset( cOutBlob, 0, sizeof ( cOutBlob ) );
            nOutFlag = 0;

            ps_params[0].buffer_type = MYSQL_TYPE_LONG_BLOB;
            ps_params[0].buffer = cOutBlob;
            ps_params[0].length = &lRealLength;
            ps_params[0].buffer_length = sizeof( cOutBlob );
            ps_params[0].is_null = 0;

            ps_params[1].buffer_type = MYSQL_TYPE_TINY;
            ps_params[1].buffer = &nOutFlag;
            ps_params[1].length = 0;
            ps_params[1].buffer_length = sizeof( nOutFlag );
            ps_params[1].is_null = 0;

            status = mysql_stmt_bind_result(stmt, ps_params);
            test_stmt_error(stmt, status);

            while (1)
            {
              status = mysql_stmt_fetch(stmt);

              if (status == 1 || status == MYSQL_NO_DATA)
                break;

              printf( "Blob:%s Flag:%d\n", cOutBlob, nOutFlag );
            }
            } else {
                printf( "End of procedure output\n" );
            }

          status = mysql_stmt_next_result(stmt);
        } while (status == 0);   
    }

    mysql_stmt_close(stmt);
    
    return a.exec();
}
#else

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MYSQL* mysql = mysql_init( 0 );
    mysql_real_connect( mysql, "127.0.0.1",
                                       "root", "root",
                                       "StreetRoadPark",
                                       3306, 0, CLIENT_MULTI_STATEMENTS );

    MYSQL_STMT *stmt;
    MYSQL_BIND ps_params[2];  /* input parameter buffers */
    int        status;

    /* set up stored procedure */
    status = mysql_query(mysql, "DROP PROCEDURE IF EXISTS p1");
    test_error(mysql, status);

    status = mysql_query(mysql,
      "CREATE PROCEDURE p1("
      "  inout p_blob LONGTEXT, "
      "  INOUT p_inout TINYINT ) "
      "BEGIN "
      "  SELECT p_blob, p_inout; "
      "  SET p_blob = 'Test', p_inout = 30; "
      "  SELECT p_blob, p_inout; "
      "  SET p_blob = 'Test1', p_inout = 31; "
      "END");
    test_error(mysql, status);

    /* initialize and prepare CALL statement with parameter placeholders */
    stmt = mysql_stmt_init(mysql);
    if (!stmt)
    {
      printf("Could not initialize statement\n");
      exit(1);
    }

    char cBlob[ 1024 ];
    char nFlag = 25;
    strcpy( cBlob, "jadfhai;fjsdfhnkcjk;oafjksdfklj;fdjkl;sfk;ff;skl;nvldfklfdkldflmfdlmvklnfvdnklljk;dskldsn" );

    status = mysql_stmt_prepare(stmt, "CALL p1(?, ?)", 13);
    test_stmt_error(stmt, status);
    int nCount = 1000;

    while( nCount-- ) {
    /* initialize parameters: p_in, p_out, p_inout (all INT) */
    memset(ps_params, 0, sizeof (ps_params));

    ps_params[0].buffer_type = MYSQL_TYPE_LONG_BLOB;
    ps_params[0].buffer = cBlob;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_TINY;
    ps_params[1].buffer = &nFlag;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    /* bind parameters */
    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_send_long_data( stmt, 0, cBlob, strlen( cBlob ) );
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    /* process results until there are no more */
    do {
      int i;
      int num_fields;       /* number of columns in result */
      MYSQL_FIELD *fields;  /* for result set metadata */
      MYSQL_BIND *rs_bind;  /* for output buffers */

      /* the column count is > 0 if there is a result set */
      /* 0 if the result is only the final status packet */
      num_fields = mysql_stmt_field_count(stmt);

      if (num_fields > 0)
      {
        /* there is a result set to fetch */
        printf("Number of columns in result: %d\n", (int) num_fields);

        /* what kind of result set is this? */
        printf("Data: ");
        if(mysql->server_status & SERVER_PS_OUT_PARAMS)
          printf("this result set contains OUT/INOUT parameters\n");
        else
          printf("this result set is produced by the procedure\n");

        MYSQL_RES *rs_metadata = mysql_stmt_result_metadata(stmt);
        test_stmt_error(stmt, rs_metadata == NULL);

        fields = mysql_fetch_fields(rs_metadata);

        rs_bind = (MYSQL_BIND *) malloc(sizeof (MYSQL_BIND) * num_fields);
        if (!rs_bind)
        {
          printf("Cannot allocate output buffers\n");
          exit(1);
        }
        memset(rs_bind, 0, sizeof (MYSQL_BIND) * num_fields);

        /* set up and bind result set output buffers */
        for (i = 0; i < num_fields; ++i)
        {
          rs_bind[i].buffer_type = fields[i].type;
          rs_bind[i].is_null = 0;

          switch (fields[i].type)
          {
            case MYSQL_TYPE_TINY:
              rs_bind[i].buffer = &nFlag;
              rs_bind[i].buffer_length = sizeof (nFlag);
              break;

          case MYSQL_TYPE_BLOB :
              rs_bind[i].buffer = cBlob;
              rs_bind[i].buffer_length = 1024;
              break;

            default:
              fprintf(stderr, "ERROR: unexpected type: %d.\n", fields[i].type);
              exit(1);
          }
        }

        status = mysql_stmt_bind_result(stmt, rs_bind);
        test_stmt_error(stmt, status);

        /* fetch and display result set rows */
        while (1)
        {
          status = mysql_stmt_fetch(stmt);

          if (status == 1 || status == MYSQL_NO_DATA)
            break;

          for (i = 0; i < num_fields; ++i)
          {
            switch (rs_bind[i].buffer_type)
            {
              case MYSQL_TYPE_TINY:
                printf(" nFlag = %d;\n", nFlag);
                break;

            case MYSQL_TYPE_BLOB :
                printf( "Blob : %s\n", cBlob );
                break;

              default:
                printf("  unexpected type (%d)\n",
                  rs_bind[i].buffer_type);
            }
          }
          printf("\n");
        }

        mysql_free_result(rs_metadata); /* free metadata */
        free(rs_bind);                  /* free output buffers */
      }
      else
      {
        /* no columns = final status packet */
        printf("End of procedure output\n");
      }

      /* more results? -1 = no, >0 = error, 0 = yes (keep looking) */
      status = mysql_stmt_next_result(stmt);
      if (status > 0)
        test_stmt_error(stmt, status);
    } while (status == 0);
    }

    mysql_stmt_close(stmt);

    return a.exec();
}
#endif
