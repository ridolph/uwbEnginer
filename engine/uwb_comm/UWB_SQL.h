// -------------------------------------------------------------------------------------------------------------------
//
//  File: trilateration.h
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//
// -------------------------------------------------------------------------------------------------------------------
//

#ifndef __UWB_SQL_H__
#define __UWB_SQL_H__

#include <stdint.h>
#include <QtSql>
#include "cJSON.h"

class UWB_SQL
{
public:
    UWB_SQL(const char *host_name, const char *db_name, const char *user, const char *password);
    int32_t SavePrisonerPosition(int32_t tag_id, double x, double y, double z);
    char *GetPrisonerHistoryData(int32_t tag_id, char *start_time, char *end_time);
private:
    bool m_is_open;
    QSqlDatabase m_dbconn;
    QSqlQuery m_query;
};



#endif
