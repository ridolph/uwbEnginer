// -------------------------------------------------------------------------------------------------------------------
//
//  File: main.cpp
//
//  Copyright 2016 (c) Decawave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author:
//
// -------------------------------------------------------------------------------------------------------------------

#include "RTLSDisplayApplication.h"
#include "mainwindow.h"
#include <QApplication>
#include <qdir.h>

#include "verify/verify.h"
#include "mylog/Mylog.h"


/**
* @brief this is the application main entry point
*
*/

#include <QMessageBox>




int main(int argc, char *argv[])
{
    int time = 0;
    int ret = -1;


    qInstallMessageHandler(Mylog::outputMessage);

#if 1
    //updateRemainTime(60*24*60);

    ret = verifyDate();
    if(1 == ret)
    {
        time = getRemainTime();
    }
    else
    {
        time = 0;
    }
#endif
    RTLSDisplayApplication app(argc, argv, time);
    if(time <= 0)
    {
         app.mainWindow()->close();
         QMessageBox::critical(NULL, "critical", "Trail period is expired.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
         return -1;
    }
    else
    {
         app.mainWindow()->show();
    }

    return app.QApplication::exec();
}



