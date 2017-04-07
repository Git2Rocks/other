#ifndef SimuComm_H
#define SimuComm_H
#include <QtCore/QCoreApplication>
#include <QtCore/QObject>
#include <QMetaType>
#include <QDebug>
#include <QMutex>
#include "/home/ems/system/ots/ots_hdb/inc/ots.h"

#define FINIT	1e-6
#define PORT	10001	

typedef enum{
	MSG_TYPE_INDCHG = 1,	//�źű�λ���������ݣ���̨��>��ά��
	MSG_TYPE_ANACHG,		//����ֵ�仯���������ݣ���̨��>��ά��
	MSG_TYPE_DEVCTL,		//�豸���ƣ��������ݣ���ά��>��̨��
	MSG_TYPE_DEVMAP,		//�豸�������������ݣ���̨��>��ά��
	MSG_TYPE_DEVTAG,		//�豸���ƣ�˫�����ݣ�
	MSG_TYPE_DEVCHK,		//�豸��飨�������ݣ���ά��>��̨��
	MSG_TYPE_GRDWIR,		//�ҽӵ��ߣ��������ݣ���ά��>��̨��
	MSG_TYPE_MSG,			//�ַ�����Ϣ��˫�����ݣ�//���ݿ����޹����㶼�ô���
	MSG_TYPE_SETEVT,		//�����쳣��˫�����ݣ�
}MSG_TYPE;

typedef struct{
	MSG_TYPE	msg_type;					//������������
	char		logicname[POINT_NAME_SIZE];		//���߼���
	int			state;							//״̬
	int			cmd_type;						//��������
	int			tag_type;						//��������
	float			_value;					
	char		opr_msg[POINT_LONGNAME_SIZE];			
}COMM_MSG;
Q_DECLARE_METATYPE(COMM_MSG);

typedef struct  _point_info
{
	POINTER	point;
	int		state;
	float		_value;
	float		step;
	int		tag_state;
}POINT_INFO;
Q_DECLARE_METATYPE(POINT_INFO);

int		BdCmdByNameStr(char *ptNameStr, unsigned char type_id, USHORT cmd_stat); //, float);

#endif