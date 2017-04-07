#include "scene.h"

CSceneTable::CSceneTable(QWidget* parent)
	:QDialog(parent,Qt::WindowMinMaxButtonsHint)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	select_status = false;
	select_stn = false;
	select_stndev = false;
	actionSceneData = new QAction(QString::fromLocal8Bit("��������"), this);
	actionAddScene = new QAction(QString::fromLocal8Bit("��ӹ���"), this);
	actionModifyScene = new QAction(QString::fromLocal8Bit("�޸Ĺ���"), this);
	actionDelScene = new QAction(QString::fromLocal8Bit("ɾ������"), this);
	actionCopyScene = new QAction(QString::fromLocal8Bit("���ƹ���"), this);
	actionAddToMergerList = new QAction(QString::fromLocal8Bit("��ӵ��ϲ��б�"), this);
	actionDelMergerScene = new QAction(QString::fromLocal8Bit("ɾ������"), this);
	stndev = new CStnDevTable(this);
	setControlAtt();
	//rownums=displayScene();
	connect(buttonRefresh,SIGNAL(clicked()),this,SLOT(displayScene()));
	connect(listScene,SIGNAL(cellClicked(int,int)),this,SLOT(selectCell(int,int)));
	connect(listScene,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(addSceneToMergerList(int,int)));
	connect(buttonSceneDel,SIGNAL(clicked()),this,SLOT(delScene()));
	connect(buttonSceneData,SIGNAL(clicked()),this,SLOT(openSceneData()));
	connect(buttonSceneAdd,SIGNAL(clicked()),this,SLOT(openSceneAdd()));
	connect(buttonSceneModify,SIGNAL(clicked()),this,SLOT(openSceneModify()));
	connect(actionSceneData,SIGNAL(triggered()),this,SLOT(openSceneData()));
	connect(actionAddScene,SIGNAL(triggered()),this,SLOT(openSceneAdd()));
	connect(actionModifyScene,SIGNAL(triggered()),this,SLOT(openSceneModify()));
	connect(actionDelScene,SIGNAL(triggered()),this,SLOT(delScene()));
	connect(actionCopyScene,SIGNAL(triggered()),this,SLOT(copyScene()));
	connect(actionAddToMergerList,SIGNAL(triggered()),this,SLOT(addSceneToMergerList()));
	connect(actionDelMergerScene,SIGNAL(triggered()),this,SLOT(delFromMergerList()));
	connect(buttonSceneInto,SIGNAL(clicked()),this,SLOT(intoScene()));
	connect(buttonStnDev,SIGNAL(clicked()),this,SLOT(openStnDev()));
	connect(buttonExit,SIGNAL(clicked()),stndev,SLOT(close()));
	connect(stndev,SIGNAL(update(int)),this,SLOT(displayUpdate(int)));
	connect(stndev,SIGNAL(update(int,int)),this,SLOT(displayUpdate(int,int)));
	connect(listScene,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(menuListScene(const QPoint &)));
	connect(listSceneMerger,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(menuListSceneMerger(const QPoint &)));
	connect(buttonClearMerger,SIGNAL(clicked()),this,SLOT(clearMerger()));
	connect(buttonRunSceneMerger,SIGNAL(clicked()),this,SLOT(runSceneMerger()));
}
void CSceneTable::loadChinese()
{
	QTranslator translator;
	translator.load("Teachermanage_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
	sceneadd->loadChinese();
	scenemodify->loadChinese();
	scenedata->loadChinese();
}
void CSceneTable::loadEnglish()
{
	QTranslator translator;
	translator.load("Teachermanage_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
	sceneadd->loadEnglish();
	scenemodify->loadEnglish();
	scenedata->loadEnglish();
}
void CSceneTable::menuListScene(const QPoint &pos)
{
	QMenu* popMenu = new QMenu(this);
	popMenu->addAction(actionSceneData);
	popMenu->addAction(actionAddScene);
	popMenu->addAction(actionModifyScene);
	popMenu->addAction(actionDelScene);
	popMenu->addAction(actionCopyScene);
	popMenu->addAction(actionAddToMergerList);
	popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}
void CSceneTable::menuListSceneMerger(const QPoint &pos)
{
	QMenu* popMenu = new QMenu(this);
	popMenu->addAction(actionDelMergerScene);
	popMenu->exec(QCursor::pos());
}

void CSceneTable::moveEvent ( QMoveEvent * event )
{
	if (stndev != NULL )
	{
		stndev->mvwith = true;
		stndev->newpt= event->pos();
		this->pos() = event->pos();
		stndev->moveEvent(event);
	}	
}
void CSceneTable::closeEvent(QCloseEvent *event)
{
	this->close();
	stndev->close();
}
void CSceneTable::setControlAtt()
{
	listScene->setSelectionBehavior(QAbstractItemView::SelectRows);
	listScene->setSelectionMode(QAbstractItemView::SingleSelection); 
	listScene->setEditTriggers(QTableWidget::NoEditTriggers);
	listScene->setContextMenuPolicy(Qt::CustomContextMenu);
	listSceneMerger->horizontalHeader()->setVisible(false);
	listSceneMerger->setContextMenuPolicy(Qt::CustomContextMenu);
	listSceneMerger->setSelectionBehavior(QAbstractItemView::SelectRows);
	listSceneMerger->setSelectionMode(QAbstractItemView::SingleSelection); 
	listSceneMerger->setEditTriggers(QTableWidget::NoEditTriggers);
	listSceneMerger->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	listSceneMerger->setColumnWidth(0,420);
	listScene->setSortingEnabled(true);
}
void CSceneTable::openStnDev()
{
	if (stndev == NULL||stndev->isHidden())
	{
		QPoint pt=this->pos();
		int x = pt.x()+this->width();
		stndev->xP = this->width();
		stndev->move(x+7,pt.y());
		stndev->show();
	}
	else
	{
		select_stn = false;
		select_stndev = false;
		stndev->hide();
		displayScene();
	}
}
void CSceneTable::addSceneToMergerList()
{
	QTableWidgetItem* item_id = listScene->item(curRow,0);
	QTableWidgetItem* item_name = listScene->item(curRow,1);
	int scene_id = item_id->text().toInt();
	QString name = item_name->text();
	for (int i=0;i<listSceneMerger->rowCount();i++)
	{
		if (scene_id == listSceneMerger->item(i,0)->data(3).toInt())
			return;
	}
	QTableWidgetItem* item = new QTableWidgetItem(name);
	item->setData(3,QVariant(scene_id));
	int row_id = listSceneMerger->rowCount();
	listSceneMerger->insertRow(row_id);
	listSceneMerger->setItem(row_id,0,item);
	comboSceneName->addItem(name);
}
void CSceneTable::addSceneToMergerList(int row, int column)
{
	QTableWidgetItem* item_id = listScene->item(curRow,0);
	QTableWidgetItem* item_name = listScene->item(curRow,1);
	int scene_id = item_id->text().toInt();
	QString name = item_name->text();
	for (int i=0;i<listSceneMerger->rowCount();i++)
	{
		if (scene_id == listSceneMerger->item(i,0)->data(3).toInt())
			return;
	}
	QTableWidgetItem* item = new QTableWidgetItem(name);
	item->setData(3,QVariant(scene_id));
	int row_id = listSceneMerger->rowCount();
	listSceneMerger->insertRow(row_id);
	listSceneMerger->setItem(row_id,0,item);
	comboSceneName->addItem(name);
}
void CSceneTable::delFromMergerList()
{
	listSceneMerger->removeRow(listSceneMerger->currentRow());
	comboSceneName->clear();
	for (int i=0;i<listSceneMerger->rowCount();i++)
	{
		QTableWidgetItem* item_name = listScene->item(i,1);
		comboSceneName->addItem(item_name->text());
	}
}
void CSceneTable::clearMerger()
{
	listSceneMerger->clearContents();
	listSceneMerger->setRowCount(0);
	comboSceneName->clear();
}
void CSceneTable::runSceneMerger()
{
	if (listSceneMerger->rowCount() == 0)
		return;
	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle (QString::fromLocal8Bit("��ʾ"));
	msgBox.setInformativeText(QString::fromLocal8Bit("�Ƿ�ȷ�Ϻϲ��������ϲ��󲻿ɻָ�"));
	msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Cancel) 
	{
		return;
	}
	if (listSceneMerger->rowCount() > 1)
	{
		int scene_id = listSceneMerger->item(0,0)->data(3).toInt();//�õ�һ��������id��Ϊ�ϲ��󹤿���id
		for (int i=1;i<listSceneMerger->rowCount();i++)
		{
			DB_FMT data;
			InitDbData(&data,TABLE_SCENE_DATA);
			data.flag.flag_scene_data.scene_id = TRUE;
			data.seg.seg_scene_data.scene_id = scene_id;

			data.cond_flag.flag_scene_data.scene_id = TRUE;
			data.cond_seg.seg_scene_data.scene_id = listSceneMerger->item(i,0)->data(3).toInt();
			if( UpdateOneRec(&data) != TRUE)
			{
				HdbLogWrite(data.sql_str,data.sql_error);
				continue;
			} 
			InitDbData(&data,TABLE_SCENE);
			data.cond_flag.flag_scene.scene_id=TRUE;
			data.cond_seg.seg_scene.scene_id = listSceneMerger->item(i,0)->data(3).toInt();
			if( DeleteOneRec(&data) != TRUE)
			{
				HdbLogWrite(data.sql_str,data.sql_error);
				continue;
			}
		}
		DB_FMT data;
		InitDbData(&data,TABLE_SCENE);
		data.flag.flag_scene.name=TRUE;
		data.flag.flag_scene.user_id =TRUE;
		data.flag.flag_scene.datetime=TRUE;

		strcpy(data.seg.seg_scene.name,comboSceneName->currentText().toLocal8Bit().data());
		GetCurTimeStr(data.seg.seg_scene.datetime);
		data.seg.seg_scene.user_id = loginUser->login_user_id;

		data.cond_flag.flag_scene.scene_id=TRUE;
		data.cond_seg.seg_scene.scene_id = scene_id;
		if( UpdateOneRec(&data) != TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
	}
	clearMerger();
	QMessageBox().information(this,QString::fromLocal8Bit("��ʾ!"),QString::fromLocal8Bit("�ϲ������ɹ�!"),QMessageBox::Ok);	
	displayScene();
}
void CSceneTable::openSceneData()
{
	int scene_id;
	if (select_status==false)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ����Ҫ�鿴���ݵĹ���!"),QMessageBox::Ok);
	}
	else
	{
		scenedata = new CSceneDataTable(this);
		QTableWidgetItem* item_id = listScene->item(curRow,0);
		scene_id = item_id->text().toInt();
		scenedata->curSceneId=scene_id;
//		scenedata->displaySceneData();
		scenedata->show();
	}
}
void CSceneTable::displayUpdate(int stn_id)
{
	select_stn = true;
	stnId = stn_id;
	displayScene();
}
void CSceneTable::displayUpdate(int stn_id,int dev_id)
{
	select_stndev = true;
	stnId = stn_id;
	devId = dev_id;
	displayScene();
}
int CSceneTable::displayScene()
{
	DB_FMT data;
	unsigned char stn_id,dev_id;
	InitDbData(&data,TABLE_SCENE);
	if (select_stn)
	{
		data.cond_flag.flag_scene.station_id = TRUE;
		data.cond_seg.seg_scene.station_id = stnId;
	}
	if (select_stndev)
	{
		data.cond_flag.flag_scene.station_id = TRUE;
		data.cond_seg.seg_scene.station_id = stnId;
		data.cond_flag.flag_scene.dev_id = TRUE;
		data.cond_seg.seg_scene.dev_id = devId;
	}
	if( SelectRecs(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data.sql_str,data.sql_error);
		return -1;
	}
	listScene->setRowCount(data.rownum);
	for(int i=0;i<data.rownum;i++)
	{	
		listScene->setItem(i,0,new QTableWidgetItem(QString::number(data_scene[i].scene_id)));
		listScene->setItem(i,1,new QTableWidgetItem(QString::fromLocal8Bit(data_scene[i].name)));
		listScene->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(data_scene[i].userinfo_longname)));
		if (data_scene[i].src==0)
		{
			listScene->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("�û��ֶ����")));
		}
		else if (data_scene[i].src==1)
		{
			listScene->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("����ʵʱϵͳ�������豸")));
		}
		else if (data_scene[i].src==2)
		{
			listScene->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("����ʵʱϵͳ����һ�豸")));
		}	
		else if (data_scene[i].src==3)
		{
			listScene->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("������ʷ���ݿ⣬�����豸")));
		}	
		else if (data_scene[i].src==4)
		{
			listScene->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit("������ʷ���ݿ⣬��һ�豸")));
		}	
		listScene->setItem(i,4,new QTableWidgetItem(QString::fromLocal8Bit(data_scene[i].datetime)));
		listScene->setItem(i,5,new QTableWidgetItem(QString::fromLocal8Bit(data_scene[i].remark)));
		stn_id = data_scene[i].station_id;
		dev_id = data_scene[i].dev_id;
		listScene->setItem(i,6,new QTableWidgetItem(QString::fromLocal8Bit(data_station[stn_id].station_longname )));
		listScene->setItem(i,7,new QTableWidgetItem(QString::fromLocal8Bit(data_dev[stn_id][dev_id].dev_longname)));
		listScene->setItem(i,8,new QTableWidgetItem(QString::fromLocal8Bit(data_scene[i].filename)));
	}
	listScene->clearSelection();
	select_stn = false;
	select_stndev = false;
	select_status = false;
	if (data.rownum != 0)
	{
		listScene->resizeColumnsToContents();
	}
	return data.rownum;
}
void CSceneTable::selectCell(int row, int column)
{
	select_status = true;
	curRow = row;
	curColumn = column;
}
void CSceneTable::delScene()
{
	if (select_status==false)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ����Ҫɾ���Ĺ���!"),QMessageBox::Ok);
	}
	else
	{
		QMessageBox msgBox(this);
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setWindowTitle (QString::fromLocal8Bit("��ʾ"));
		msgBox.setInformativeText(QString::fromLocal8Bit("�Ƿ�ȷ��ɾ��"));
		msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) 
		{
			return;
		}

		DB_FMT data;
		InitDbData(&data,TABLE_SCENE_DATA);
		QTableWidgetItem* flag_scene_id = listScene->item(curRow,0);
		data.cond_flag.flag_scene_data.scene_id=TRUE;
		data.cond_seg.seg_scene_data.scene_id = flag_scene_id->text().toInt();
		if( DeleteOneRec(&data) != TRUE)
		{
			//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("ɾ������ʧ��!"),QMessageBox::Ok);		
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
		InitDbData(&data,TABLE_SCENE);
		data.cond_flag.flag_scene.scene_id=TRUE;
		data.cond_seg.seg_scene.scene_id = flag_scene_id->text().toInt();
		if( DeleteOneRec(&data) != TRUE)
		{
			//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("ɾ������ʧ��!"),QMessageBox::Ok);		
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
	}
	rownums = displayScene();
}
void CSceneTable::openSceneAdd()
{
	sceneadd = new CSceneAddTable(this);
	sceneadd->flag_add=true;
	sceneadd->buttonApply->setVisible(false);
	sceneadd->show();
	connect(sceneadd,SIGNAL(insertRecord()),this,SLOT(addScene()));
}
void CSceneTable::openSceneModify()
{
	int scene_id;
	if (select_status==false)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ����Ҫ�޸ĵĹ���!"),QMessageBox::Ok);
		return;
	}
	else
	{
		scenemodify = new CSceneAddTable(this);
		scenemodify->flag_modify=true;
		QTableWidgetItem* item_id = listScene->item(curRow,0);
		scene_id = item_id->text().toInt();
		curSceneId=scene_id;
		QTableWidgetItem* name = listScene->item(curRow,1);
		scenemodify->editName->setText(name->text());
		QTableWidgetItem* station = listScene->item(curRow,6);
		if (station->text() == QString(""))
		{
			scenemodify->editStation->setCurrentIndex(0);
		}
		else
		{
			scenemodify->editStation->setCurrentIndex(scenemodify->editStation->findText(station->text(),Qt::MatchContains));
		}
		QTableWidgetItem* dev = listScene->item(curRow,7);
		if (dev->text() == QString(""))
		{
			scenemodify->editDev->setCurrentIndex(0);
		}
		else
		{
			scenemodify->editDev->setCurrentIndex(scenemodify->editDev->findText(dev->text(),Qt::MatchContains));
		}
		QTableWidgetItem* filename = listScene->item(curRow,8);
		scenemodify->editFileName->setText(filename->text());
		QTableWidgetItem* remark = listScene->item(curRow,5);
		scenemodify->editRemark->setText(remark->text());
		scenemodify->setWindowTitle(QString::fromLocal8Bit("�޸Ĺ���"));		
		scenemodify->show();
		connect(scenemodify,SIGNAL(modifyRecord()),this,SLOT(modifyScene()));
	}
}
void CSceneTable::addScene()
{
	DB_FMT data;
	InitDbData(&data,TABLE_SCENE);

	//���ñ���ÿ���ֶε�flag
	data.flag.flag_scene.scene_id =TRUE;
	data.flag.flag_scene.user_id =TRUE;
	data.flag.flag_scene.name=TRUE;
	data.flag.flag_scene.src=TRUE;
	data.flag.flag_scene.datetime=TRUE;
	data.flag.flag_scene.remark=TRUE;
	data.flag.flag_scene.dev_id=TRUE;
	data.flag.flag_scene.station_id=TRUE;
	data.flag.flag_scene.filename=TRUE;

	//������ÿ���ֶε�ֵ

	sceneadd->seg.scene_id = GetInexistenceIdInHdb(TABLE_SCENE);
	sceneadd->seg.src = 0;
	sceneadd->seg.user_id = loginUser->login_user_id;
	GetCurTimeStr( sceneadd->seg.datetime);	
	data.seg.seg_scene = sceneadd->seg;

	//���ýӿں���������ΪDB_FMT�ṹ��
	if( InsertOneRec(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��������ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}

	rownums=displayScene();
}
void CSceneTable::modifyScene()
{

	DB_FMT data;
	InitDbData(&data,TABLE_SCENE);

	//���ñ���ÿ���ֶε�flag
	data.flag.flag_scene.name=TRUE;
	data.flag.flag_scene.user_id =TRUE;
	data.flag.flag_scene.datetime=TRUE;
	data.flag.flag_scene.remark=TRUE;
	data.flag.flag_scene.dev_id=TRUE;
	data.flag.flag_scene.station_id=TRUE;
	data.flag.flag_scene.filename=TRUE;


	//������ÿ���ֶε�ֵ
	GetCurTimeStr( scenemodify->seg.datetime);
	scenemodify->seg.user_id = loginUser->login_user_id;
	data.seg.seg_scene = scenemodify->seg;

	//���ò�ѯ����
	data.cond_flag.flag_scene.scene_id=TRUE;
	data.cond_seg.seg_scene.scene_id = curSceneId;
	if( UpdateOneRec(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("�޸����ݿ�ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}
	rownums = displayScene();
}
void CSceneTable::copyScene()
{
	if (select_status==false)
	{
		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("û��ѡ����Ҫ���ƵĹ���!"),QMessageBox::Ok);
		return;
	}
	int scene_id = listScene->item(curRow,0)->text().toInt();
	int new_scene_id = GetInexistenceIdInHdb(TABLE_SCENE);
	DB_FMT data,data_copy;
	InitDbData(&data,TABLE_SCENE);
	data.cond_flag.flag_scene.scene_id=TRUE;
	data.cond_seg.seg_scene.scene_id = scene_id;
	if( SelectRecs(&data) != TRUE)
	{	
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}
	for (int i=0;i<data.rownum;i++)
	{
		InitDbData(&data_copy,TABLE_SCENE);
		data_copy.flag.flag_scene.scene_id =TRUE;
		data_copy.flag.flag_scene.user_id =TRUE;
		data_copy.flag.flag_scene.name=TRUE;
		data_copy.flag.flag_scene.src=TRUE;
		data_copy.flag.flag_scene.datetime=TRUE;
		data_copy.flag.flag_scene.remark=TRUE;
		data_copy.flag.flag_scene.dev_id=TRUE;
		data_copy.flag.flag_scene.station_id=TRUE;
		data_copy.flag.flag_scene.filename=TRUE;

		//������ÿ���ֶε�ֵ
		data_copy.seg.seg_scene.scene_id = new_scene_id;
		data_copy.seg.seg_scene.user_id = data_scene[i].user_id;
		strcpy(data_copy.seg.seg_scene.name,data_scene[i].name);
		data_copy.seg.seg_scene.src=data_scene[i].src;
		GetCurTimeStr(data_copy.seg.seg_scene.datetime);
		strcpy(data_copy.seg.seg_scene.remark,data_scene[i].remark);
		data_copy.seg.seg_scene.dev_id = data_scene[i].dev_id;
		data_copy.seg.seg_scene.station_id = data_scene[i].station_id;
		strcpy(data_copy.seg.seg_scene.filename,data_scene[i].filename);
		if( InsertOneRec(&data_copy) != TRUE)
		{
			HdbLogWrite(data_copy.sql_str,data_copy.sql_error);
			return;
		}
	}
	/**********************************************copy scene_data*******************************************/
	InitDbData(&data,TABLE_SCENE_DATA);
	data.cond_flag.flag_scene_data.scene_id = TRUE;
	data.cond_seg.seg_scene_data.scene_id = scene_id;
	QProgressDialog *progressDlg=new QProgressDialog(this); 
	QFont font("ZYSong18030",12);  
	progressDlg->setFont(font);  
	progressDlg->setWindowModality(Qt::WindowModal); 
	progressDlg->setMinimumDuration(5);  
	progressDlg->setWindowTitle(tr("please wait"));  
	progressDlg->setLabelText(tr("����������,���Ժ�......      "));  
	progressDlg->setCancelButtonText(tr("ȡ��"));  
	if( SelectRecs(&data) != TRUE)
	{	
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}
	progressDlg->setRange(0,data.rownum-1);
	for (int i=0;i<data.rownum;i++)
	{
		InitDbData(&data_copy,TABLE_SCENE_DATA);
		data_copy.flag.flag_scene_data.scene_id = TRUE;
		data_copy.flag.flag_scene_data.logicalname = TRUE;
		data_copy.flag.flag_scene_data.status = TRUE;
		data_copy.flag.flag_scene_data.data = TRUE;

		//������ÿ���ֶε�ֵ
		data_copy.seg.seg_scene_data.scene_id = new_scene_id;
		strcpy(data_copy.seg.seg_scene_data.logicalname,data_scene_data[i].logicalname);
		data_copy.seg.seg_scene_data.status = data_scene_data[i].status;
		data_copy.seg.seg_scene_data.data = data_scene_data[i].data;
		if( InsertOneRec(&data_copy) != TRUE)
		{	
			HdbLogWrite(data.sql_str,data.sql_error);
			continue;
		}
		progressDlg->setValue(i); 
		if(progressDlg->wasCanceled())  
			break;
	}
	displayScene();
}
void CSceneTable::intoScene()
{
	//ͳһ��������������
	DB_FMT data,cdata;
	DMS_COMMON	dms_rec;
	int	data_type;
	char timestr[22];
	char curid;
	int i,j;
	bool flag_repeat=false;
	GetCurTimeStr(timestr);
	if ( SimulogDataLoad () == -1 )
	{
		printf ( "simulog.dat error!\n" );
	}

	data.table_id=TABLE_SCENE;
	cdata.table_id = TABLE_SCENE_DATA;
	InitDbData(&data,data.table_id);
	InitDbData(&cdata,cdata.table_id);	

	//����Ҫscene���ʵ��ֶ�flag��Ϊ
	data.flag.flag_scene.datetime =TRUE;
	data.flag.flag_scene.dev_id =TRUE;
	data.flag.flag_scene.name =TRUE;
	data.flag.flag_scene.remark =TRUE;
	data.flag.flag_scene.scene_id =TRUE;
	data.flag.flag_scene.src =TRUE;
	data.flag.flag_scene.station_id =TRUE;
	data.flag.flag_scene.user_id =TRUE;

	//����Ҫscene_data���ʵ��ֶ�flag��Ϊ
	cdata.flag.flag_scene_data.data =TRUE;
	cdata.flag.flag_scene_data.logicalname =TRUE;
	cdata.flag.flag_scene_data.scene_id =TRUE;

	//���scene����ÿ���ֶε�ֵ
	strcpy(data.seg.seg_scene.datetime,timestr);
	data.seg.seg_scene.dev_id =1;

	data.seg.seg_scene.src =0;
	data.seg.seg_scene.station_id =1;
	data.seg.seg_scene.user_id = 0;

	for(i=0;i<n_scene;i++)
	{
		curid = GetInexistenceIdInHdb(TABLE_SCENE);
		flag_repeat=false;
		data.seg.seg_scene.scene_id = curid;
		strcpy(data.seg.seg_scene.name,scenedb[i].scene_name);
		strcpy(data.seg.seg_scene.remark,scenedb[i].scene_name);
		for (int k=0;k<rownums;k++)
		{
			QTableWidgetItem* remark= listScene->item(k,5);
			if (remark->text()==QString::fromLocal8Bit(scenedb[i].scene_name))
			{
				flag_repeat = true;
				break;
			}
		}
		if (flag_repeat==true)
		{
			continue;
		}
		//���ýӿں���������ΪDB_FMT�ṹ��
		if( InsertOneRec(&data) != TRUE)
		{
			//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("���빤��ʧ��!"),QMessageBox::Ok);
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
		cdata.seg.seg_scene_data.scene_id = curid;

		for( j=scenedb[i].head; j<scenedb[i].head+scenedb[i].num; j++ )
		{
			strcpy(cdata.seg.seg_scene_data.logicalname,scenesegdb[j].name);
			if ( ReadEntryByNameStr ( scenesegdb[j].name, &dms_rec ) == -1 )
			{
				printf ("in Scene: id=%d name= %s is not found in database.\n",i,scenesegdb[i].name );
				continue;
			}
			else
			{
				data_type	= dms_rec.point.data_type;	//wdk 2008.3.22
				//yyp 2009.2.11
				MySleep(20);

				switch	( data_type )
				{
				case	ANA_TYPE:
				case	PARAM_TYPE:
					cdata.seg.seg_scene_data.data =  scenesegdb[j].data.value ;
					break;
				case	POL_TYPE:
				case	SOE_TYPE:
				case	SYSMSG_TYPE:
				case	DEVOBJ_TYPE:
					cdata.seg.seg_scene_data.status =  scenesegdb[j].data.status ;
					break;
				default:
					break;
				}
			}
			//���ýӿں���������ΪDB_FMT�ṹ��
			if( InsertOneRec(&cdata) != TRUE)
			{
				HdbLogWrite(cdata.sql_str,cdata.sql_error);
				printf("����scenedata����%s ʧ��\n", scenesegdb[j].name);
				continue;
			}						
		}
		rownums = displayScene();
	}
}
/*****************************************************CSceneAddTable*********************************************************/
CSceneAddTable::CSceneAddTable(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	flag_add=false;
	flag_modify=false;
	displayStation();
	setControlAtt();
	connect(buttonApply,SIGNAL(clicked()),this,SLOT(apply()));
	connect(buttonEnter,SIGNAL(clicked()),this,SLOT(enter()));
	connect(editStation,SIGNAL(currentIndexChanged(int)),this,SLOT(displayDev(int)));
}
void CSceneAddTable::setControlAtt()
{
	editStation->setCurrentIndex(-1);
	editDev->setCurrentIndex(-1);
}
void CSceneAddTable::loadChinese()
{
	QTranslator translator;
	translator.load("Teachermanage_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSceneAddTable::loadEnglish()
{
	QTranslator translator;
	translator.load("Teachermanage_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSceneAddTable::displayStation()
{
	editStation->insertItem(0,QString::fromLocal8Bit("�޳�վ"));
	for(int i=1;i<=g_stn_num;i++)
	{
		UCHAR	stnid;
		if(-1==GetStnIdByIndex(i, &stnid))
			continue;
		editStation->insertItem(i,QString(data_station[stnid].station_longname),QVariant(data_station[stnid].station_id));	
	}
}
void CSceneAddTable::displayDev(int index)
{
	editDev->clear();
	editDev->insertItem(0,QString::fromLocal8Bit("���豸"));
	UCHAR stnid = editStation->itemData(index).toInt();
	for (int j=1;j<=data_station[stnid].dev_num;j++)
	{
		editDev->insertItem(j,QString::fromLocal8Bit(data_dev[stnid][j].dev_longname),QVariant(data_dev[stnid][j].dev_id));
	}
}
void CSceneAddTable::apply()
{		
	strcpy(seg.name,editName->text().toLocal8Bit().data());	
	seg.station_id = editStation->itemData(editStation->currentIndex()).toInt();
	seg.dev_id = editDev->itemData(editDev->currentIndex()).toInt();
	strcpy(seg.remark,editRemark->toPlainText().toLocal8Bit().data());
	strcpy(seg.filename,editFileName->text().toLocal8Bit().data());	
	if (flag_add)
	{
		emit insertRecord();
	}
	if (flag_modify)
	{
		emit modifyRecord();
	}
}
void CSceneAddTable::enter()
{
	apply();
	editName->clear();
	editStation->setCurrentIndex(-1);
	editDev->setCurrentIndex(-1);
	editRemark->clear();
	editFileName->clear();
	this->close();
	flag_add=false;
	flag_modify=false;
}
