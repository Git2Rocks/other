#include "settask.h"

CSetTaskTable::CSetTaskTable(QWidget* parent)
	:QWidget(parent)
{
	setupUi(this);
	dlg_created_flag[SETTASKDLG] = true;
	this->setAttribute(Qt::WA_DeleteOnClose);
	if (flag_langueage == 0)
	{
		loadChinese();
	}
	else if (flag_langueage == 1)
	{
		loadEnglish();
	}	
	sortbyusertype = false;
	examonly = false ;
	usertype = -1;
//	this->setModal(true);
	connect(buttonSend,SIGNAL(clicked()),this,SLOT(sendTask()));
	connect(radioSingle,SIGNAL(toggled(bool)),this,SLOT(singleMode(bool)));
	connect(radioMulti,SIGNAL(toggled(bool)),this,SLOT(multiMode(bool)));
	connect(comboStn,SIGNAL(currentIndexChanged(int)),this,SLOT(displayDev(int)));
	connect(comboTaskFilterType,SIGNAL(currentIndexChanged(int)),this,SLOT(taskFilterTypeChanged(int)));
	connect(comboSceneFilterType,SIGNAL(currentIndexChanged(int)),this,SLOT(sceneFilterTypeChanged(int)));
	connect(comboFaultFilterType,SIGNAL(currentIndexChanged(int)),this,SLOT(faultFilterTypeChanged(int)));
	connect(comboTaskFilterName,SIGNAL(currentIndexChanged(int)),this,SLOT(setTaskModel()));
	connect(comboSceneFilterName,SIGNAL(currentIndexChanged(int)),this,SLOT(setSceneModel()));
	connect(comboFaultFilterName,SIGNAL(currentIndexChanged(int)),this,SLOT(setFaultModel()));
	connect(comboDev,SIGNAL(currentIndexChanged(int)),this,SLOT(setTaskModel()));
	connect(comboDev,SIGNAL(currentIndexChanged(int)),this,SLOT(setSceneModel()));
	connect(comboDev,SIGNAL(currentIndexChanged(int)),this,SLOT(setFaultModel()));
	connect(buttonTaskFilter,SIGNAL(clicked()),this,SLOT(setTaskFilter()));
	connect(buttonTaskShowAll,SIGNAL(clicked()),this,SLOT(setTaskFilter()));
	connect(buttonSceneFilter,SIGNAL(clicked()),this,SLOT(setSceneFilter()));
	connect(buttonSceneShowAll,SIGNAL(clicked()),this,SLOT(setSceneFilter()));
	connect(buttonFaultFilter,SIGNAL(clicked()),this,SLOT(setFaultFilter()));
	connect(buttonFaultShowAll,SIGNAL(clicked()),this,SLOT(setFaultFilter()));
	//dzy 2014
	connect(checkBoxusertype,SIGNAL(toggled(bool)),this,SLOT(setSortbyusertype(bool)));
	connect(checkBox_examonly,SIGNAL(toggled(bool)),this,SLOT(setExamOnly(bool)));
	groupBoxFault->setEnabled(false);
	setControlAtt();
}
CSetTaskTable::~CSetTaskTable()
{
	dlg_created_flag[SETTASKDLG] = false;
}
void CSetTaskTable::setControlAtt()
{
	taskModel = new QStandardItemModel;
	sceneModel = new QStandardItemModel;
	faultModel = new QStandardItemModel;
	taskFilterModel = new QSortFilterProxyModel;
	sceneFilterModel = new QSortFilterProxyModel;
	faultFilterModel = new QSortFilterProxyModel;
	listTask->setSelectionBehavior(QAbstractItemView::SelectRows);
	listTask->setSelectionMode(QAbstractItemView::SingleSelection); 
	listTask->setEditTriggers(QTableWidget::NoEditTriggers);
	listScene->setSelectionBehavior(QAbstractItemView::SelectRows);
	listScene->setSelectionMode(QAbstractItemView::SingleSelection); 
	listScene->setEditTriggers(QTableWidget::NoEditTriggers);
	listFault->setSelectionBehavior(QAbstractItemView::SelectRows);
	listFault->setSelectionMode(QAbstractItemView::SingleSelection); 
	listFault->setEditTriggers(QTableWidget::NoEditTriggers);
	listUserAndGroups->setSelectionMode(QAbstractItemView::SingleSelection); 
	listUserAndGroups->setEditTriggers(QTableWidget::NoEditTriggers);
	radioSingle->setChecked(true);
	radioMulti->setChecked(false);
	selectionModel = listUserAndGroups->selectionModel();
	comboTaskFilterType->addItem(QString::fromLocal8Bit("��ѡ��"));
	comboTaskFilterType->addItem(QString::fromLocal8Bit("�������"));
	comboTaskFilterType->addItem(QString::fromLocal8Bit("����"));
	comboSceneFilterType->addItem(QString::fromLocal8Bit("��ѡ��"));
	comboSceneFilterType->addItem(QString::fromLocal8Bit("��Դ����"));
	comboFaultFilterType->addItem(QString::fromLocal8Bit("��ѡ��"));
	comboFaultFilterType->addItem(QString::fromLocal8Bit("����"));
	groupBoxScene->setChecked(false);
	groupBoxFault->setChecked(false);
	taskFilterModel->setSourceModel(taskModel);
	taskFilterModel->setDynamicSortFilter(true);
	taskFilterModel->setFilterKeyColumn(0);
	listTask->setModel(taskFilterModel);
	taskSelectionModel = listTask->selectionModel();
	sceneFilterModel->setSourceModel(sceneModel);
	sceneFilterModel->setDynamicSortFilter(true);
	sceneFilterModel->setFilterKeyColumn(0);
	listScene->setModel(sceneFilterModel);
	sceneSelectionModel = listScene->selectionModel();
	faultFilterModel->setSourceModel(faultModel);
	faultFilterModel->setDynamicSortFilter(true);
	faultFilterModel->setFilterKeyColumn(0);
	listFault->setModel(faultFilterModel);
	faultSelectionModel = listFault->selectionModel();
	current_task_id = -1;
	current_scene_id = -1;
	current_fault_id = -1;
	readConfig();
	spinTimeLimit->setValue(defaultTimeLimit);
}
void CSetTaskTable::readConfig()
{
	QString myfile = SimuTutorConfigPath;
	QSettings mySetting(myfile,QSettings::IniFormat);
	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
	defaultTimeLimit = mySetting.value("task/timeLimit",60).toInt();
}
void CSetTaskTable::showEvent(QShowEvent *event)
{
// 	if (flag_langueage == 0)
// 	{
// 		loadChinese();
// 	}
// 	else if (flag_langueage == 1)
// 	{
// 		loadEnglish();
// 	}
	displayStn();
	updateUsersAndGroups();
	setTaskModel();
	setSceneModel();
	setFaultModel();
	if (flag_simutrainee)
	{
		for (int i=0;i<listUserAndGroups->count();i++)
		{
			int user_id = listUserAndGroups->item(i)->data(3).toInt();
			if (user_id == login_user_id)
			{
				listUserAndGroups->setCurrentItem(listUserAndGroups->item(i));
				break;
			}
		}
	}
	event->accept();
}
void  CSetTaskTable::setLanguage(int language)
{	
	QTranslator translator;
	if(flag_simutrainee)
	{
		if (language == 0)
		{
			translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_CN");
		}
		else if (language == 1)
		{
			translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_en");
		}
	}
	else
	{
		if (language == 0)
		{
			translator.load("SimuTutor_zh_CN");
		}
		else if (language == 1)
		{
			translator.load("SimuTutor_en");
		}
	}	
	qApp->installTranslator(&translator);
	retranslateUi(this);
	displayStn();
	updateUsersAndGroups();
	setTaskModel();
	setSceneModel();
	setFaultModel();
	if (flag_simutrainee)
	{
		for (int i=0;i<listUserAndGroups->count();i++)
		{
			int user_id = listUserAndGroups->item(i)->data(3).toInt();
			if (user_id == login_user_id)
			{
				listUserAndGroups->setCurrentItem(listUserAndGroups->item(i));
				break;
			}
		}
	}
}
void CSetTaskTable::loadChinese()
{
	QTranslator translator;
	if (flag_simutrainee)
	{
		 translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_CN");
	}
	else
		translator.load("SimuTutor_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetTaskTable::loadEnglish()
{
	QTranslator translator;
	if (flag_simutrainee)
	{
		 translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_en");
	}
	else
		translator.load("SimuTutor_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetTaskTable::singleMode(bool status)
{
	if (status==true)
	{ 
		listUserAndGroups->setSelectionMode(QAbstractItemView::SingleSelection); 
	}
}
void CSetTaskTable::multiMode(bool status)
{
	if (status==true)
	{
		listUserAndGroups->setSelectionMode(QAbstractItemView::MultiSelection); 
	}	
}
void CSetTaskTable::updateUsersAndGroups()
{
	listUserAndGroups->clear();
	DB_FMT data;
	InitDbData(&data,TABLE_TRAIN_INFO);
	data.cond_flag.flag_train_info.login_status = TRUE;
	data.cond_seg.seg_train_info.login_status = 1;
	strcpy(data.addon_str,"order by simu_mode"); 
	if( SelectRecs(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_TRAIN_INFO);
		return;
	}
	for(int i=0;i<data.rownum;i++)	
	{
		//DZY ADDED FOR STUDENT'S STUDYMODE  ignore group
		if(mode == 1)//ѧԱ����ѧϰ
		{
			QListWidgetItem *userItem = new QListWidgetItem;
			QString name;
			name = QString::fromLocal8Bit("ѧԱ:")+QString::fromLocal8Bit(data_train_info[i].userinfo_longname);
			userItem->setText(name);
			//userItem->setCheckState(Qt::Unchecked);
			userItem->setData(3,QVariant(data_train_info[i].user_id));
			userItem->setData(4,QVariant(data_train_info[i].host_id));
			//DZY 2014
			DB_FMT data2;
			InitDbData(&data2,TABLE_USERINFO);
			data2.cond_flag.flag_userinfo.user_id = TRUE;
			data2.cond_seg.seg_userinfo.user_id = data_train_info[i].user_id;
			SelectRecs(&data2);
			usertype =data_userinfo[0].user_type_id;
			userItem->setData(5,QVariant(data_userinfo[0].user_type_id));
			// END DZY
			listUserAndGroups->addItem(userItem);
		}
		else if (JudgeUserRole(data_train_info[i].user_id,ROLE_STUDENT) == TRUE&&data_train_info[i].simu_mode!=2)//����ģʽ�������
		{
			int groups_id = GetUserGroupsId(data_train_info[i].user_id);
			if (data_train_info[i].simu_mode==1) //dzy edited 14 0509
			{
				QListWidgetItem *userItem = new QListWidgetItem;
				QString name;
				name = QString::fromLocal8Bit("����ѧԱ:")+QString::fromLocal8Bit(data_train_info[i].userinfo_longname);
				userItem->setText(name);
				//userItem->setCheckState(Qt::Unchecked);
				userItem->setData(3,QVariant(data_train_info[i].user_id));
				userItem->setData(4,QVariant(data_train_info[i].host_id));
				//DZY 2014
				DB_FMT data2;
				InitDbData(&data2,TABLE_USERINFO);
				data2.cond_flag.flag_userinfo.user_id = TRUE;
				data2.cond_seg.seg_userinfo.user_id = data_train_info[i].user_id;
				SelectRecs(&data2);
				usertype =data_userinfo[0].user_type_id;
				userItem->setData(5,QVariant(data_userinfo[0].user_type_id));
				// END DZY
				listUserAndGroups->addItem(userItem);
			}
			else 	if (data_train_info[i].simu_mode==0) 
			{
				QListWidgetItem *userItem = new QListWidgetItem;
				QString name;
				name =QString::fromLocal8Bit("��ѵѧԱ:")+ QString::fromLocal8Bit(data_train_info[i].userinfo_longname);
				userItem->setText(name);
				//userItem->setCheckState(Qt::Unchecked);
				userItem->setData(3,QVariant(data_train_info[i].user_id));
				userItem->setData(4,QVariant(data_train_info[i].host_id));
				//DZY 2014
				DB_FMT data2;
				InitDbData(&data2,TABLE_USERINFO);
				data2.cond_flag.flag_userinfo.user_id = TRUE;
				data2.cond_seg.seg_userinfo.user_id = data_train_info[i].user_id;
				SelectRecs(&data2);
				usertype =data_userinfo[0].user_type_id;
				userItem->setData(5,QVariant(data_userinfo[0].user_type_id));
				// END DZY
				listUserAndGroups->addItem(userItem);
			}
		}
		//����ģʽREMOVED
		else
		{
			int groups_id = GetUserGroupsId(data_train_info[i].user_id);
			if (JudgeUserGroupsRole(data_train_info[i].user_id,GROUPS_ROLE_LEADER) == TRUE)
			{
				DB_FMT data;
				InitDbData(&data,TABLE_GROUPS);
				data.cond_flag.flag_groups.groups_id = TRUE;
				data.cond_seg.seg_groups.groups_id = groups_id;
				if( SelectRecs(&data) != TRUE)
				{
					HdbLogWrite(data.sql_str,data.sql_error);
					FreeDbData(&data,TABLE_GROUPS);
					return;
				}
				QListWidgetItem *groupsItem = new QListWidgetItem;
				QString name;
				name = QString::fromLocal8Bit(data_groups[0].name)+QString::fromLocal8Bit("����,�鳤:")+QString::fromLocal8Bit(data_train_info[i].userinfo_longname);
				groupsItem->setText(name);
				//groupsItem->setCheckState(Qt::Unchecked);
				groupsItem->setData(3,QVariant(data_train_info[i].user_id));
				groupsItem->setData(4,QVariant(data_train_info[i].host_id));
				//DZY
				checkBoxusertype->setChecked(false);
				sortbyusertype = false;
				checkBox_examonly->setChecked(false);
				examonly = false;
				//
				listUserAndGroups->addItem(groupsItem);
				FreeDbData(&data,TABLE_GROUPS);
			}

		}
	}
	FreeDbData(&data,TABLE_TRAIN_INFO);
}
void CSetTaskTable::taskFilterTypeChanged(int index)
{
	comboTaskFilterName->clear();
	switch(index)
	{
		case 0:
			comboTaskFilterName->addItem(QString::fromLocal8Bit("��ѡ�����"));
			break;
		case 1:
			DB_FMT data;
			InitDbData(&data,TABLE_TASK_GRP);
			if( SelectRecs(&data) != TRUE)
			{		
				HdbLogWrite(data.sql_str,data.sql_error);
				FreeDbData(&data,TABLE_TASK_GRP);
				return;
			}
			for (int i=0;i<data.rownum;i++)
				comboTaskFilterName->addItem(QString::fromLocal8Bit(data_task_grp[i].name),QVariant(data_task_grp[i].task_grp_id));
			FreeDbData(&data,TABLE_TASK_GRP);
			break;
		case 2:
			comboTaskFilterName->addItem(QString::fromLocal8Bit("��������"),QVariant(1));
			comboTaskFilterName->addItem(QString::fromLocal8Bit("���ϴ���"),QVariant(2));
			break;
		default:
			break;
	}
}
void CSetTaskTable::sceneFilterTypeChanged(int index)
{
	comboSceneFilterName->clear();
	switch(index)
	{
		case 0:
			comboSceneFilterName->addItem(QString::fromLocal8Bit("��ѡ�����"));
			break;
		case 1:
			comboSceneFilterName->addItem(QString::fromLocal8Bit("�û��ֶ����"),QVariant(0));
			comboSceneFilterName->addItem(QString::fromLocal8Bit("����ʵʱϵͳ�������豸"),QVariant(1));
			comboSceneFilterName->addItem(QString::fromLocal8Bit("����ʵʱϵͳ����һ�豸"),QVariant(2));
			comboSceneFilterName->addItem(QString::fromLocal8Bit("������ʷ���ݿ⣬�����豸"),QVariant(3));
			comboSceneFilterName->addItem(QString::fromLocal8Bit("������ʷ���ݿ⣬��һ�豸"),QVariant(4));
			break;
		default:
			break;
	}
}
void CSetTaskTable::faultFilterTypeChanged(int index)
{
	comboFaultFilterName->clear();
	switch(index)
	{
		case 0:
			comboFaultFilterName->addItem(QString::fromLocal8Bit("��ѡ�����"));
			break;
		case 1:
			comboFaultFilterName->addItem(QString::fromLocal8Bit("ϵͳ�¹�"),QVariant(0));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("��·�豸�¹�"),QVariant(1));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("�����豸�¹�"),QVariant(2));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("�����豸�¹�"),QVariant(3));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("���õ��¹�"),QVariant(4));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("ֱ���¹�"),QVariant(5));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("�����豸�¹�"),QVariant(6));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("��е�豸�¹�"),QVariant(7));
			comboFaultFilterName->addItem(QString::fromLocal8Bit("�����豸�¹�"),QVariant(8));
			break;
		default:
			break;
	}
}
void CSetTaskTable::setTaskModel()
{
	DB_FMT data;
	InitDbData(&data,TABLE_TASK);
	if (comboStn->currentIndex() != 0)
	{
		data.cond_flag.flag_task.station_id = TRUE;
		data.cond_seg.seg_task.station_id = comboStn->itemData(comboStn->currentIndex()).toInt();
	}
	if (comboDev->currentIndex() != 0)
	{
		data.cond_flag.flag_task.dev_id = TRUE;
		data.cond_seg.seg_task.dev_id = comboDev->itemData(comboDev->currentIndex()).toInt();
	}
	if (comboTaskFilterType->currentIndex()!=0)
	{
		switch(comboTaskFilterType->currentIndex())
		{
			case 1:
				data.cond_flag.flag_task.task_grp_id = TRUE;
				data.cond_seg.seg_task.task_grp_id = comboTaskFilterName->itemData(comboTaskFilterName->currentIndex()).toInt();
				break;
			case 2:
				data.cond_flag.flag_task.type = TRUE;
				data.cond_seg.seg_task.type = comboTaskFilterName->itemData(comboTaskFilterName->currentIndex()).toInt();
				break;
			default:
				break;
		}
	}
	if (mode == 1)//�����ѧϰ
	{
		data.cond_flag.flag_task.task_userange = TRUE;
		data.cond_seg.seg_task.task_userange = 1;
	}
	else if (examonly)
	{
		data.cond_flag.flag_task.task_userange = TRUE;
		data.cond_seg.seg_task.task_userange = 0;
	}
	if (sortbyusertype)
	{
		data.cond_flag.flag_task.user_type_id = TRUE;
		data.cond_seg.seg_task.user_type_id = usertype;
	}

	if( SelectRecs(&data) != TRUE)
	{		
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_TASK);
		return;
	}
	taskModel->clear();
	taskModel->setColumnCount(1);  
	for (int i=0;i<data.rownum;i++)
	{
		QStandardItem* item = new QStandardItem(QString::fromLocal8Bit(data_task[i].name)); 
		item->setData(QVariant(data_task[i].task_id));
		taskModel->appendRow(item); 
	}
	listTask->clearSelection();
	FreeDbData(&data,TABLE_TASK);
}
void CSetTaskTable::setSceneModel()
{
	DB_FMT data;
	InitDbData(&data,TABLE_SCENE);
	if (comboStn->currentIndex() != 0)
	{
		data.cond_flag.flag_scene.station_id = TRUE;
		data.cond_seg.seg_scene.station_id = comboStn->itemData(comboStn->currentIndex()).toInt();
	}
	if (comboDev->currentIndex() != 0)
	{
		data.cond_flag.flag_scene.dev_id = TRUE;
		data.cond_seg.seg_scene.dev_id = comboDev->itemData(comboDev->currentIndex()).toInt();
	}
	if (comboSceneFilterType->currentIndex()!=0)
	{
		switch(comboSceneFilterType->currentIndex())
		{
			case 1:
				data.cond_flag.flag_scene.src = TRUE;
				data.cond_seg.seg_scene.src = comboSceneFilterName->itemData(comboSceneFilterName->currentIndex()).toInt();
				break;
			default:
				break;
		}
	}
	if( SelectRecs(&data) != TRUE)
	{		
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SCENE);
		return;
	}
	sceneModel->clear();
	sceneModel->setColumnCount(1);  
	for (int i=0;i<data.rownum;i++)
	{
		QStandardItem* item = new QStandardItem(QString::fromLocal8Bit(data_scene[i].name)); 
		item->setData(QVariant(data_scene[i].scene_id));
		sceneModel->appendRow(item); 
	}
	listScene->clearSelection();
	FreeDbData(&data,TABLE_SCENE);
}
void CSetTaskTable::setFaultModel()
{
	DB_FMT data;
	InitDbData(&data,TABLE_FAULT);
	if (comboStn->currentIndex() != 0)
	{
		data.cond_flag.flag_fault.station_id = TRUE;
		data.cond_seg.seg_fault.station_id = comboStn->itemData(comboStn->currentIndex()).toInt();
	}
	if (comboDev->currentIndex() != 0)
	{
		data.cond_flag.flag_fault.dev_id = TRUE;
		data.cond_seg.seg_fault.dev_id = comboDev->itemData(comboDev->currentIndex()).toInt();
	}
	if (comboFaultFilterType->currentIndex()!=0)
	{
		switch(comboFaultFilterType->currentIndex())
		{
			case 1:
				data.cond_flag.flag_fault.type = TRUE;
				data.cond_seg.seg_fault.type = comboFaultFilterName->itemData(comboFaultFilterName->currentIndex()).toInt();
				break;
			default:
				break;
		}
	}
	if( SelectRecs(&data) != TRUE)
	{		
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_FAULT);
		return;
	}
	faultModel->clear();
	faultModel->setColumnCount(1);  
	for (int i=0;i<data.rownum;i++)
	{
		QStandardItem* item = new QStandardItem(QString::fromLocal8Bit(data_fault[i].name)); 
		item->setData(QVariant(data_fault[i].fault_id));
		faultModel->appendRow(item); 
	}
	listFault->clearSelection();
	FreeDbData(&data,TABLE_FAULT);
}
void CSetTaskTable::displayStn()
{
	comboStn->clear();
	if (comboStn->count() == 0)
	{
		comboStn->insertItem(0,QString::fromLocal8Bit("���г�վ"));
	}
	for(int i=1;i<=g_stn_num;i++)
	{
		UCHAR	stnid;
		if(-1==GetStnIdByIndex(i, &stnid))
			continue;
		comboStn->addItem(QString(data_station[stnid].station_longname),QVariant(data_station[stnid].station_id));	
	}
}
void CSetTaskTable::displayDev(int index)
{
	comboDev->clear();
	comboDev->insertItem(0,QString::fromLocal8Bit("���豸"));
	UCHAR stnid = comboStn->itemData(index).toInt();
	for (int j=1;j<=data_station[stnid].dev_num;j++)
	{
		comboDev->insertItem(j,QString::fromLocal8Bit(data_dev[stnid][j].dev_longname),QVariant(data_dev[stnid][j].dev_id));
	}
	setTaskModel();
	setSceneModel();
	setFaultModel();
}
void CSetTaskTable::setTaskFilter()
{
	QPushButton *button = qobject_cast<QPushButton*>(sender());
	if (button == buttonTaskFilter)
	{
		QString str = editTaskFilter->text();
		taskFilterModel->setFilterRegExp(QRegExp(str));
	}
	else
	{
		comboTaskFilterType->setCurrentIndex(0);
		editTaskFilter->clear();
		taskFilterModel->setFilterRegExp(QRegExp("/*"));
	}
}
void CSetTaskTable::setSceneFilter()
{
	QPushButton *button = qobject_cast<QPushButton*>(sender());
	if (button == buttonSceneFilter)
	{
		QString str = editSceneFilter->text();
		sceneFilterModel->setFilterRegExp(QRegExp(str));
	}
	else
	{
		comboSceneFilterType->setCurrentIndex(0);
		editSceneFilter->clear();
		sceneFilterModel->setFilterRegExp(QRegExp("/*"));
	}
}
void CSetTaskTable::setFaultFilter()
{
	QPushButton *button = qobject_cast<QPushButton*>(sender());
	if (button == buttonFaultFilter)
	{
		QString str = editFaultFilter->text();
		faultFilterModel->setFilterRegExp(QRegExp(str));
	}
	else
	{
		comboFaultFilterType->setCurrentIndex(0);
		editFaultFilter->clear();
		faultFilterModel->setFilterRegExp(QRegExp("/*"));
	}
}
void CSetTaskTable::sendTask()
{
	if (selectionModel->hasSelection()==false||taskSelectionModel->hasSelection()==false)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ�з���������û���û��ѡ������!"),QMessageBox::Ok);
	}
	else
	{
		isRevertTable = new QDialog(this);
		buttonEnter = new QPushButton(isRevertTable);
		buttonExit = new QPushButton(isRevertTable);
		noSave = new QRadioButton(isRevertTable);
		saveDbin = new QRadioButton(isRevertTable);
		saveDev = new QRadioButton(isRevertTable);
		info = new QLabel(isRevertTable);
		isRevertTable->setModal(true);
		isRevertTable->setWindowTitle(QString::fromLocal8Bit("��ʾ"));
		QGridLayout *layout = new QGridLayout(isRevertTable);
		layout->setSizeConstraint(QLayout::SetFixedSize);
		info->setText(QString::fromLocal8Bit("�Ƿ񱣴�Ϊ�������ְ���?"));
		buttonEnter->setText(QString::fromLocal8Bit("ȷ��"));
		buttonExit->setText(QString::fromLocal8Bit("ȡ��"));
		noSave->setText(QString::fromLocal8Bit("������"));
		saveDbin->setText(QString::fromLocal8Bit("���滭����ʷ����"));
		saveDev->setText(QString::fromLocal8Bit("�����豸��ʷ����"));
		layout->addWidget(info,0,0,Qt::AlignCenter);
		layout->addWidget(noSave,1,0);
		layout->addWidget(saveDbin,2,0);
		layout->addWidget(saveDev,3,0);
		layout->addWidget(buttonEnter,4,1);
		layout->addWidget(buttonExit,4,2);
		isRevertTable->setLayout(layout);	 
		noSave->setChecked(TRUE);
		connect(buttonEnter,SIGNAL(clicked()),isRevertTable,SLOT(close()));
		connect(buttonEnter,SIGNAL(clicked()),this,SLOT(setTask()));
		connect(buttonExit,SIGNAL(clicked()),isRevertTable,SLOT(close()));
		isRevertTable->show();
	}
}
void CSetTaskTable::setTask()
{
	QList<QListWidgetItem *> userlist = listUserAndGroups->selectedItems();
	if (taskSelectionModel->hasSelection()==true)
	{
		QModelIndexList indexes = taskSelectionModel->selectedRows();
		QStandardItem *item = taskModel->itemFromIndex(taskFilterModel->mapToSource(taskFilterModel->index(indexes.at(0).row(),0)));
		current_task_id = item->data().toInt();
	}
	if (sceneSelectionModel->hasSelection()==true)
	{
		QModelIndexList indexes = sceneSelectionModel->selectedRows();
		QStandardItem *item = sceneModel->itemFromIndex(sceneFilterModel->mapToSource(sceneFilterModel->index(indexes.at(0).row(),0)));
		current_scene_id = item->data().toInt();
	}
	if (faultSelectionModel->hasSelection()==true)
	{
		QModelIndexList indexes = faultSelectionModel->selectedRows();
		QStandardItem *item = faultModel->itemFromIndex(faultFilterModel->mapToSource(faultFilterModel->index(indexes.at(0).row(),0)));
		current_fault_id = item->data().toInt();
	}	
	for (int i=0;i<userlist.size();i++)
	{
		current_user_id = userlist.at(i)->data(3).toInt();
		current_host_id = userlist.at(i)->data(4).toInt();
		DB_FMT data;
		int id = GetMaxIdInHdb(TABLE_SEND_TASK)+1;
		InitDbData(&data,TABLE_SEND_TASK);
		data.flag.flag_send_task.send_task_id =TRUE;
		data.flag.flag_send_task.task_id =TRUE;
		data.flag.flag_send_task.send_time =TRUE;
		data.flag.flag_send_task.user_id =TRUE;
		data.flag.flag_send_task.status =TRUE;
		data.flag.flag_send_task.time_len =TRUE;
		data.seg.seg_send_task.send_task_id = id;
		data.seg.seg_send_task.task_id = current_task_id;
		GetCurTimeStr(data.seg.seg_send_task.send_time);
		data.seg.seg_send_task.user_id = current_user_id;
		data.seg.seg_send_task.status =0;
		data.seg.seg_send_task.time_len = spinTimeLimit->value()*60;
		if( InsertOneRec(&data) != TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��%1��������ʧ��!").arg(userlist.at(i)->text()),QMessageBox::Ok);
			FreeDbData(&data,TABLE_SEND_TASK);
			continue;
		}
		FreeDbData(&data,TABLE_SEND_TASK);
		InitDbData(&data,TABLE_TRAIN_INFO);
		data.flag.flag_train_info.send_task_id = TRUE;
		data.flag.flag_train_info.task_id = TRUE;
		if (groupBoxScene->isChecked() == true)
		{
			data.flag.flag_train_info.scene_id = TRUE;
			data.flag.flag_train_info.scene_status = TRUE;
			data.seg.seg_train_info.scene_id = current_scene_id;
			data.seg.seg_train_info.scene_status = 1;
		}
		else
		{
// 			data.flag.flag_train_info.scene_id = TRUE;
// 			data.flag.flag_train_info.scene_status = TRUE;
// 			data.seg.seg_train_info.scene_id = CONST_NEG;
// 			data.seg.seg_train_info.scene_status = 0;
		}
		if (groupBoxFault->isChecked() == true)
		{
			data.flag.flag_train_info.fault_id = TRUE;
			data.flag.flag_train_info.fault_status = TRUE;
			data.seg.seg_train_info.fault_id = current_fault_id;
			data.seg.seg_train_info.fault_status = 1;
		}
		else
		{
// 			data.flag.flag_train_info.fault_id = TRUE;
// 			data.flag.flag_train_info.fault_status = TRUE;
// 			data.seg.seg_train_info.fault_id = CONST_NEG;
// 			data.seg.seg_train_info.fault_status = 0;
		}
		data.flag.flag_train_info.task_status = TRUE;
		data.flag.flag_train_info.is_record = TRUE;
		data.flag.flag_train_info.status = TRUE;
		data.seg.seg_train_info.status = 0;
		data.seg.seg_train_info.send_task_id = id;
		data.seg.seg_train_info.task_id = current_task_id;	
		data.seg.seg_train_info.task_status = 1;
		if (noSave->isChecked())
		{
			data.seg.seg_train_info.is_record = 0;
		}
		else if (saveDbin->isChecked())
		{
			data.seg.seg_train_info.is_record = 1;
		}
		else if (saveDev->isChecked())
		{
			data.seg.seg_train_info.is_record = 2;
		}
		data.cond_flag.flag_train_info.user_id =TRUE;
		data.cond_seg.seg_train_info.user_id = current_user_id;
		data.cond_flag.flag_train_info.host_id = TRUE;
		data.cond_seg.seg_train_info.host_id = current_host_id;
		//dzy
		data.flag.flag_train_info.task_startable = TRUE;
		if (flag_simutrainee||shm_ots_addr->data_task.task_startable == 1)
		{
			data.seg.seg_train_info.task_startable = 1;
		}
		else
			data.seg.seg_train_info.task_startable = 0;

		if( UpdateOneRec(&data) != TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��%1��������ʧ��!").arg(userlist.at(i)->text()),QMessageBox::Ok);
			FreeDbData(&data,TABLE_TRAIN_INFO);
			continue;
		}
		else
		{
			//shm_ots_addr->data_task.flag_new_send_task = 1;
			MySleep(500);
			emit sig_tasksetted();
		}
		UpdateTrainInfoModel();

		FreeDbData(&data,TABLE_TRAIN_INFO);
	}
	this->close();
	/*int ret = QMessageBox().information(this,QString::fromLocal8Bit("��Ϣ!"),QString::fromLocal8Bit("��������ɹ�!"),QMessageBox::Ok);
	if (ret == QMessageBox::Ok)
	{
		this->close();
	}*/
}
void CSetTaskTable::setSortbyusertype(bool checked)
{
	sortbyusertype = checked;
	setTaskModel();
}

void CSetTaskTable::setExamOnly(bool checked)
{
	 examonly = checked;
	setTaskModel();
}
/***************************************************set scene fault**************************************************************/

CSetSceneFaultTable::CSetSceneFaultTable(QWidget* parent)
:QWidget(parent)
{
	setupUi(this);
	dlg_created_flag[SETSCENEFAULTDLG] = true;
	this->setAttribute(Qt::WA_DeleteOnClose);
//	this->setModal(true);
	if (flag_langueage == 0)
	{
		loadChinese();
	}
	else if (flag_langueage == 1)
	{
		loadEnglish();
	}	
	sceneModel = new QStandardItemModel;
	faultModel = new QStandardItemModel;
	sceneFilterModel = new QSortFilterProxyModel;
	faultFilterModel = new QSortFilterProxyModel;
	sceneFilterModel->setSourceModel(sceneModel);
	sceneFilterModel->setDynamicSortFilter(true);
	faultFilterModel->setSourceModel(faultModel);
	faultFilterModel->setDynamicSortFilter(true);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection); 
	tableView->setEditTriggers(QTableView::NoEditTriggers);
	tableView->setSortingEnabled(true);
	tableView->verticalHeader()->setVisible(false);
	connect(buttonRefresh,SIGNAL(clicked()), this, SLOT(refreshList()));
	connect(buttonSearch,SIGNAL(clicked()),this,SLOT(setFilter()));
	connect(buttonShowAll,SIGNAL(clicked()),this,SLOT(setFilter()));
	connect(buttonCancel,SIGNAL(clicked()), this, SLOT(onclose()));
}
CSetSceneFaultTable::~CSetSceneFaultTable()
{
	dlg_created_flag[SETSCENEFAULTDLG] = false;
}
void CSetSceneFaultTable::initScene()
{
	this->setWindowTitle(QString::fromLocal8Bit("���ù���"));
	tableView->setModel(sceneFilterModel);
	sceneFilterModel->setFilterKeyColumn(0);
	sceneFilterModel->setFilterRegExp(QRegExp("/*"));
	buttonEnter->disconnect();
	connect(buttonEnter,SIGNAL(clicked()), this, SLOT(setScene()));
	updateUsersAndGroups();
}
void CSetSceneFaultTable::loadChinese()
{
	QTranslator translator;
	if (flag_simutrainee)
	{
		 translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_CN");
	}
	else
		translator.load("SimuTutor_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetSceneFaultTable::loadEnglish()
{
	QTranslator translator;
	if (flag_simutrainee)
	{
		 translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_en");
	}
	else
		translator.load("SimuTutor_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void  CSetSceneFaultTable::setLanguage(int language)
{	
	QTranslator translator;
	if(flag_simutrainee)
	{
		if (language == 0)
		{
			translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_CN");
		}
		else if (language == 1)
		{
			translator.load("/home/ems/system/ots/SimuTrainee/SimuTrainee_zh_en");
		}
	}
	else
	{
		if (language == 0)
		{
			translator.load("SimuTutor_zh_CN");
		}
		else if (language == 1)
		{
			translator.load("SimuTutor_en");
		}
	}	
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetSceneFaultTable::showEvent(QShowEvent *event)
{
// 	if (flag_langueage == 0)
// 	{
// 		loadChinese();
// 	}
// 	else if (flag_langueage == 1)
// 	{
// 		loadEnglish();
// 	}
	event->accept();
}
void CSetSceneFaultTable::initFault()
{
	this->setWindowTitle(QString::fromLocal8Bit("���ù���"));
	tableView->setModel(faultFilterModel);
	faultFilterModel->setFilterKeyColumn(0);
	faultFilterModel->setFilterRegExp(QRegExp("/*"));
	buttonEnter->disconnect();
	connect(buttonEnter,SIGNAL(clicked()), this, SLOT(setFault()));
	updateUsersAndGroups();
}
void CSetSceneFaultTable::setFilter()
{
	QPushButton *button = qobject_cast<QPushButton*>(sender());
	if (button == buttonSearch)
	{
		QString str = editSearchName->text();
		sceneFilterModel->setFilterRegExp(QRegExp(str));
		faultFilterModel->setFilterRegExp(QRegExp(str));
	}
	else
	{
		sceneFilterModel->setFilterRegExp(QRegExp("/*"));
		faultFilterModel->setFilterRegExp(QRegExp("/*"));
	}
}
void CSetSceneFaultTable::updateUsersAndGroups()
{	
	listUserAndGroups->clear();
	mapGroups.clear();
	DB_FMT data;
	InitDbData(&data,TABLE_TRAIN_INFO);
	data.cond_flag.flag_train_info.login_status = TRUE;
	data.cond_seg.seg_train_info.login_status = 1;
	if( SelectRecs(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_TRAIN_INFO);
		return;
	}
	for(int i=0;i<data.rownum;i++)	
	{
		if (JudgeUserRole(data_train_info[i].user_id,ROLE_STUDENT) == TRUE)
		{
			int groups_id = GetUserGroupsId(data_train_info[i].user_id);
			if (groups_id == -1||groups_id ==0 )
			{
				QListWidgetItem *userItem = new QListWidgetItem;
				QString name;
				name = QString::fromLocal8Bit(data_train_info[i].userinfo_longname)+QString::fromLocal8Bit("(ѧԱ)");
				userItem->setText(name);
				userItem->setCheckState(Qt::Unchecked);
				userItem->setData(3,QVariant(data_train_info[i].user_id));
				userItem->setData(4,QVariant(data_train_info[i].host_id));

				listUserAndGroups->addItem(userItem);
			}
			else if (groups_id > 0)
			{
				QList<int> listUser;
				listUser.append(data_train_info[i].user_id);
				listUser.append(data_train_info[i].host_id);
				mapGroups.insert(groups_id,listUser);

				listUser.clear();
			}
		}
	}
	FreeDbData(&data,TABLE_TRAIN_INFO);
	QList<int> keys = mapGroups.keys();
	if (keys.size() == 0)
		return;
	QList<int> list_groups_id;
	for (int i=0;i<keys.size();i++)
	{
		if (!list_groups_id.contains(keys.at(i)))
			list_groups_id.append(keys.at(i));
	}
	for (int i=0;i<list_groups_id.size();i++)
	{
		InitDbData(&data,TABLE_GROUPS);
		data.cond_flag.flag_groups.groups_id = TRUE;
		data.cond_seg.seg_groups.groups_id = list_groups_id.at(i);
		if( SelectRecs(&data) != TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			FreeDbData(&data,TABLE_GROUPS);
			return;
		}
		for(int i=0;i<data.rownum;i++)	
		{
			if (data_groups[i].groups_id != -1 && data_groups[i].groups_id != 0)
			{
				QListWidgetItem *groupsItem = new QListWidgetItem;
				QString name;
				name = QString::fromLocal8Bit(data_groups[i].name)+QString::fromLocal8Bit("(����)");
				groupsItem->setText(name);
				groupsItem->setCheckState(Qt::Unchecked);
			//	groupsItem->setData(3,QVariant(data_groups[i].groups_id));
				groupsItem->setData(5,QVariant(data_groups[i].groups_id));
				listUserAndGroups->addItem(groupsItem);
			}
		}
	}
	FreeDbData(&data,TABLE_GROUPS);
}
void CSetSceneFaultTable::setSceneModel()
{
	DB_FMT data;
	unsigned char stn_id,dev_id;
	InitDbData(&data,TABLE_SCENE);
	if( SelectRecs(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SCENE);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	sceneModel->clear();
	sceneModel->setColumnCount(7);  
	sceneModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("��������"));  
	sceneModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("��Դ����")); 
	sceneModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("����ʱ��"));
	sceneModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("Ĭ�ϻ���"));  
	sceneModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("��ע"));
	sceneModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("��վ"));
	sceneModel->setHeaderData(6,Qt::Horizontal,QString::fromLocal8Bit("�豸"));
	for (int i=0;i<data.rownum;i++)
	{
		QStandardItem* item0 = new QStandardItem(QString::fromLocal8Bit(data_scene[i].name)); 
		item0->setData(QVariant(data_scene[i].scene_id));
		QStandardItem* item1;
		if (data_scene[i].src==0)
			item1 = new QStandardItem(QString::fromLocal8Bit("�û��ֶ����")); 
		if (data_scene[i].src==1)
			item1 = new QStandardItem(QString::fromLocal8Bit("����ʵʱϵͳ�������豸")); 
		if (data_scene[i].src==2)
			item1 = new QStandardItem(QString::fromLocal8Bit("����ʵʱϵͳ����һ�豸")); 
		if (data_scene[i].src==3)
			item1 = new QStandardItem(QString::fromLocal8Bit("������ʷ���ݿ⣬�����豸")); 
		if (data_scene[i].src==4)
			item1 = new QStandardItem(QString::fromLocal8Bit("������ʷ���ݿ⣬��һ�豸")); 
 
		QStandardItem* item2 = new QStandardItem(QString::fromLocal8Bit(data_scene[i].datetime));  
		QStandardItem* item3 = new QStandardItem(QString::fromLocal8Bit(data_scene[i].filename));  
		QStandardItem* item4 = new QStandardItem(QString::fromLocal8Bit(data_scene[i].remark)); 
		stn_id = data_scene[i].station_id;
		dev_id = data_scene[i].dev_id;
		QStandardItem* item5 = new QStandardItem(QString::fromLocal8Bit(data_station[stn_id].station_name)); 
		QStandardItem* item6 = new QStandardItem(QString::fromLocal8Bit(data_dev[stn_id][dev_id].dev_name)); 
		
		item0->setTextAlignment(Qt::AlignCenter);
		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);
		item3->setTextAlignment(Qt::AlignCenter);
		//item4->setTextAlignment(Qt::AlignCenter);
		item5->setTextAlignment(Qt::AlignCenter);
		item6->setTextAlignment(Qt::AlignCenter);
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3 << item4 << item5 << item6; 
		sceneModel->appendRow(items); 
	}
	tableView->resizeColumnsToContents();
// 	tableVie->setColumnWidth(2,80);
// 	tableView->setColumnWidth(3,60);
// 	tableView->setColumnWidth(4,60);
	FreeDbData(&data,TABLE_SCENE);
}

void CSetSceneFaultTable::setFaultModel()
{
	DB_FMT data;
	unsigned char stn_id,dev_id;
	InitDbData(&data,TABLE_FAULT);
	if( SelectRecs(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_FAULT);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	faultModel->clear();
	faultModel->setColumnCount(6);  
	faultModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("��������"));  
	faultModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("����")); 
	faultModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("ʱ��"));
	faultModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("��ע"));
	faultModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("��վ"));
	faultModel->setHeaderData(5,Qt::Horizontal,QString::fromLocal8Bit("�豸"));
	for (int i=0;i<data.rownum;i++)
	{
		QStandardItem* item0 = new QStandardItem(QString::fromLocal8Bit(data_fault[i].name)); 
		item0->setData(QVariant(data_fault[i].fault_id));
		QStandardItem* item1;
		if (data_fault[i].type==0)
			item1 = new QStandardItem(QString::fromLocal8Bit("ϵͳ�¹�")); 
		if (data_fault[i].type==1)
			item1 = new QStandardItem(QString::fromLocal8Bit("��·�豸�¹�")); 
		if (data_fault[i].type==2)
			item1 = new QStandardItem(QString::fromLocal8Bit("�����豸�¹�")); 
		if (data_fault[i].type==3)
			item1 = new QStandardItem(QString::fromLocal8Bit("�����豸�¹�")); 
		if (data_fault[i].type==4)
			item1 = new QStandardItem(QString::fromLocal8Bit("���õ��¹�")); 
		if (data_fault[i].type==5)
			item1 = new QStandardItem(QString::fromLocal8Bit("ֱ���¹�"));
		if (data_fault[i].type==6)
			item1 = new QStandardItem(QString::fromLocal8Bit("�����豸�¹�"));
		if (data_fault[i].type==7)
			item1 = new QStandardItem(QString::fromLocal8Bit("��е�豸�¹�"));
		if (data_fault[i].type==8)
			item1 = new QStandardItem(QString::fromLocal8Bit("�����豸�¹�"));

		QStandardItem* item2 = new QStandardItem(QString::fromLocal8Bit(data_fault[i].datetime));    
		QStandardItem* item3 = new QStandardItem(QString::fromLocal8Bit(data_fault[i].remark)); 
		stn_id = data_fault[i].station_id;
		dev_id = data_fault[i].dev_id;
		QStandardItem* item4= new QStandardItem(QString::fromLocal8Bit(data_station[stn_id].station_name)); 
		QStandardItem* item5 = new QStandardItem(QString::fromLocal8Bit(data_dev[stn_id][dev_id].dev_name));

		item0->setTextAlignment(Qt::AlignCenter);
		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);
		//item3->setTextAlignment(Qt::AlignCenter);
		item4->setTextAlignment(Qt::AlignCenter);
		item5->setTextAlignment(Qt::AlignCenter);
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3 << item4 << item5; 
		faultModel->appendRow(items); 
	}
    tableView->resizeColumnsToContents();
// 	tableView->setColumnWidth(2,80);
// 	tableView->setColumnWidth(3,60);
// 	tableView->setColumnWidth(4,60);
	FreeDbData(&data,TABLE_FAULT);
}

void CSetSceneFaultTable::refreshList()
{
	setSceneModel();
	setFaultModel();
	updateUsersAndGroups();
}

void CSetSceneFaultTable::setScene()
{
	selectionModel = tableView->selectionModel();
	if (!selectionModel->hasSelection())
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ��Ҫ���õĹ���!"),QMessageBox::Ok);
		return;
	}
	QModelIndexList indexes = selectionModel->selectedRows(0);
	QStandardItem *item = sceneModel->itemFromIndex(sceneFilterModel->mapToSource(sceneFilterModel->index(indexes.at(0).row(),0)));
	int scene_id = item->data().toInt();
	if (flag_simutrainee&&shm_ots_addr->data_task.task_status ==2)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ǰ����ִ���У���������ʼǰ���ù���!"),QMessageBox::Ok);
		return;
	}
	//emit sigSendScene(scene_id);
	for (int i=0;i<listUserAndGroups->count();i++)
	{
		if (listUserAndGroups->item(i)->checkState() == Qt::Checked)
		{
			if (listUserAndGroups->item(i)->text().contains(QString::fromLocal8Bit("(ѧԱ)")))
			{
				DB_FMT data;
				InitDbData(&data,TABLE_TRAIN_INFO);
				data.flag.flag_train_info.user_id = TRUE;
				data.seg.seg_train_info.user_id = listUserAndGroups->item(i)->data(3).toInt();
				data.cond_flag.flag_train_info.host_id = TRUE;
				data.cond_seg.seg_train_info.host_id = listUserAndGroups->item(i)->data(4).toInt();

				data.flag.flag_train_info.scene_id = TRUE;
				data.seg.seg_train_info.scene_id = scene_id;
				data.flag.flag_train_info.scene_status = TRUE;
				data.seg.seg_train_info.scene_status = 1;
				if (UpdateOneRec(&data)!=(int)TRUE)
				{
					HdbLogWrite(data.sql_str,data.sql_error);
					FreeDbData(&data,TABLE_TRAIN_INFO);
					continue;
				}
				FreeDbData(&data,TABLE_TRAIN_INFO);
			}
			else
			{
				int groups_id = listUserAndGroups->item(i)->data(5).toInt();
				QList<QList<int>> values = mapGroups.values(groups_id);
				for (int j=0;j<values.size();j++)
				{
					DB_FMT data;
					InitDbData(&data,TABLE_TRAIN_INFO);
					data.flag.flag_train_info.user_id = TRUE;
					data.seg.seg_train_info.user_id = values.at(j).at(0);
					data.cond_flag.flag_train_info.host_id = TRUE;
					data.cond_seg.seg_train_info.host_id = values.at(j).at(1);

					data.flag.flag_train_info.scene_id = TRUE;
					data.seg.seg_train_info.scene_id = scene_id;
					data.flag.flag_train_info.scene_status = TRUE;
					data.seg.seg_train_info.scene_status = 1;
					if (UpdateOneRec(&data)!=(int)TRUE)
					{
						HdbLogWrite(data.sql_str,data.sql_error);
						FreeDbData(&data,TABLE_TRAIN_INFO);
						continue;
					}
					FreeDbData(&data,TABLE_TRAIN_INFO);
				}
			}
		}
	}
	this->onclose();
}

void CSetSceneFaultTable::setFault()
{
	selectionModel = tableView->selectionModel();
	if (!selectionModel->hasSelection())
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ��Ҫ���õĹ���!"),QMessageBox::Ok);
		return;
	}

	QModelIndexList indexes = selectionModel->selectedRows(0);
	QStandardItem *item = faultModel->itemFromIndex(faultFilterModel->mapToSource(faultFilterModel->index(indexes.at(0).row(),0)));
	int fault_id = item->data().toInt();
		//emit sigSendFault(fault_id);
	if (flag_simutrainee&&shm_ots_addr->data_task.task_status ==2)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ǰ����ִ���У���������ʼǰ���ù���!"),QMessageBox::Ok);
		return;
	}

	for (int i=0;i<listUserAndGroups->count();i++)
	{
		if (listUserAndGroups->item(i)->checkState() == Qt::Checked)
		{
			if (listUserAndGroups->item(i)->text().contains(QString::fromLocal8Bit("(ѧԱ)")))
			{
				DB_FMT data;
				InitDbData(&data,TABLE_TRAIN_INFO);
				data.flag.flag_train_info.user_id = TRUE;
				data.seg.seg_train_info.user_id = listUserAndGroups->item(i)->data(3).toInt();
				data.cond_flag.flag_train_info.host_id = TRUE;
				data.cond_seg.seg_train_info.host_id = listUserAndGroups->item(i)->data(4).toInt();

				data.flag.flag_train_info.fault_id = TRUE;
				data.seg.seg_train_info.fault_id = fault_id;
				data.flag.flag_train_info.fault_status = TRUE;
				data.seg.seg_train_info.fault_status = 1;
				if (UpdateOneRec(&data)!=(int)TRUE)
				{
					HdbLogWrite(data.sql_str,data.sql_error);
					FreeDbData(&data,TABLE_TRAIN_INFO);
					continue;
				}
				FreeDbData(&data,TABLE_TRAIN_INFO);
			}
			else
			{
				int groups_id = listUserAndGroups->item(i)->data(5).toInt();
				QList<QList<int>> values = mapGroups.values(groups_id);
				for (int j=0;j<values.size();j++)
				{
					DB_FMT data;
					InitDbData(&data,TABLE_TRAIN_INFO);
					data.flag.flag_train_info.user_id = TRUE;
					data.seg.seg_train_info.user_id = values.at(j).at(0);
					data.cond_flag.flag_train_info.host_id = TRUE;
					data.cond_seg.seg_train_info.host_id = values.at(j).at(1);

					data.flag.flag_train_info.fault_id = TRUE;
					data.seg.seg_train_info.fault_id = fault_id;
					data.flag.flag_train_info.fault_status = TRUE;
					data.seg.seg_train_info.fault_status = 1;
					if (UpdateOneRec(&data)!=(int)TRUE)
					{
						HdbLogWrite(data.sql_str,data.sql_error);
						FreeDbData(&data,TABLE_TRAIN_INFO);
						continue;
					}
					FreeDbData(&data,TABLE_TRAIN_INFO);
				}
			}
		}
	}
	this->onclose();
}
void CSetSceneFaultTable::onclose()
{
	emit closedlg();
	this->close();
}