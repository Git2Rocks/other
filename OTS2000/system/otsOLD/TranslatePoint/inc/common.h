#ifndef _COMMON_H
#define _COMMON_H

#include <QtCore/QCoreApplication>
#include <QRegExp>
#include <windows.h>
#include "/home/ems/system/ots/ots_hdb/inc/ots.h"
#pragma warning( disable : 4996 )

enum    POINT_INFO_TYPE  
{ 
	TYPE_ID = 0,			//���
	TYPE_NAME = 1,			//���߼���
	TYPE_LONGNAME = 2,		//��������
	TYPE_VALUE = 3,			//��ֵ
	TYPE_STATE = 4			//��״̬
};

bool CheckPointName(QString &text);
bool CheckPointId(QString &text);
void DelBlank(QString &strs);
void GetPointInfo(DMS_COMMON *db_cmm,char *info,int info_type);
static BOOL enumUserWindowsCB(HWND hwnd,LPARAM lParam);
HWND findDesktopIconWnd();

#endif