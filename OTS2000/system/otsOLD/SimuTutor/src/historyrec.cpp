#include "historyrec.h"

printCond print_cond;
printCond* lpprint_cond;
CHistoryRecTable::CHistoryRecTable(QWidget* parent)
	:QDialog(parent,Qt::WindowMinMaxButtonsHint)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	actionDelRec = new QAction(QString::fromLocal8Bit("ɾ����¼"), this);
	//exceltable = new CExcelTable;
	recPrint = new QProcess(parent);
	recSourceModel = new QStandardItemModel;
	recModelType = new QSortFilterProxyModel;
	recModelName = new QSortFilterProxyModel;
	recModelType->setSourceModel(recSourceModel);
	recModelType->setDynamicSortFilter(true);
	recModelName->setSourceModel(recModelType);
	recModelName->setDynamicSortFilter(true);
	connect(actionDelRec,SIGNAL(triggered()),this,SLOT(delRec()));
	connect(checkCmd,SIGNAL(clicked()),this,SLOT(setFilterType()));
	connect(checkAlarm,SIGNAL(clicked()),this,SLOT(setFilterType()));
	connect(checkOpt,SIGNAL(clicked()),this,SLOT(setFilterType()));
	connect(checkCheck,SIGNAL(clicked()),this,SLOT(setFilterType()));
	connect(checkInfo,SIGNAL(clicked()),this,SLOT(setFilterType()));
	connect(buttonTodayDisplay,SIGNAL(clicked()),this,SLOT(displayTodayRec()));
	connect(buttonPrint,SIGNAL(clicked()),this,SLOT(exportToExcel()));
	connect(buttonSearch,SIGNAL(clicked()),this,SLOT(displayRec()));
	connect(buttonSelectTask,SIGNAL(clicked()),this,SLOT(openSelectTaskTable()));
	connect(buttonRecordDel,SIGNAL(clicked()),this,SLOT(delRecord()));
	//connect(exceltable,SIGNAL(exp()),this,SLOT(exportExcel()));
	connect(comboSearchType,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setFilterSearchType(const QString &)));
	connect(comboSearchName,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setFilterSearchName(const QString &)));
	connect(comboSearchName,SIGNAL(editTextChanged(const QString &)),this,SLOT(setFilterSearchName(const QString &)));
	init();
}
CHistoryRecTable::~CHistoryRecTable()
{
	//excel->dynamicCall("Quit()");
}
void CHistoryRecTable::showEvent(QShowEvent *event)
{
	comboSearchType->setCurrentIndex(0);
	comboSearchName->setCurrentIndex(0);
	timeEnd->setDateTime(QDateTime::currentDateTime());
	timeStart->setDateTime(QDateTime::currentDateTime().addSecs(-300));
	recSourceModel->clear();
	recSourceModel->setColumnCount(5);  
	recSourceModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("�û���"));  
	recSourceModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("ʱ��")); 
	recSourceModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("����"));
	recSourceModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("�¼�����"));  
	recSourceModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("������")); 
	viewRec->setColumnWidth(0,70);
	viewRec->setColumnWidth(1,130);
	viewRec->setColumnWidth(2,40);
	viewRec->setColumnWidth(3,630);
	viewRec->setColumnWidth(4,90);
	viewRec->horizontalHeader()->setStretchLastSection(true);
	//displayUserName();
	//displayGroups();
	event->accept();
}
void CHistoryRecTable::init()
{
	m_user_id = -1;
	m_send_task_id = -1;
	checkCmd->setCheckState(Qt::Checked);
	checkAlarm->setCheckState(Qt::Checked);
	checkOpt->setCheckState(Qt::Checked);
	checkCheck->setCheckState(Qt::Checked);
	checkInfo->setCheckState(Qt::Checked);
	timeStart->setCalendarPopup(true);
	timeEnd->setCalendarPopup(true); 
	viewRec->setSelectionBehavior(QAbstractItemView::SelectRows);
	viewRec->setEditTriggers(QTableView::NoEditTriggers);
	viewRec->verticalHeader()->setVisible(false);
	viewRec->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	recModelName->setFilterRegExp(QRegExp("/*"));
	recModelType->setFilterRegExp(QRegExp("/*"));
	comboSearchType->addItem(QString::fromLocal8Bit("�û���"));
	comboSearchType->addItem(QString::fromLocal8Bit("����"));
	QCompleter *completer = new QCompleter(this);
	completer->setModel(comboSearchName->model());
	comboSearchName->setCompleter(completer);
#ifndef WIN32
	buttonPrint->setEnabled(false);
#endif
	
}

void CHistoryRecTable::loadChinese()
{
	QTranslator translator;
	translator.load("Teachermanage_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
	selecttasktable->loadChinese();
	//exceltable->loadChinese();
}
void CHistoryRecTable::loadEnglish()
{
	QTranslator translator;
	translator.load("Teachermanage_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
	selecttasktable->loadEnglish();
	//exceltable->loadEnglish();
}

void CHistoryRecTable::contextMenuEvent(QContextMenuEvent * event)
{
	event->ignore();
	QMenu* popMenu = new QMenu(this);
	QPoint p(20,23);
	//QTableWidgetItem* pTableWidgetItem=listFault->itemAt(listFault->mapFromGlobal(QCursor::pos()-p));
	//if(pTableWidgetItem != NULL)
	//{
	//	popMenu->addAction(actionDelRec);
	//}
	popMenu->addAction(actionDelRec);
	popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}//�����Ҽ������˵�

void CHistoryRecTable::openSelectTaskTable()
{
	selecttasktable = new CSelectTaskTable(this);
	selecttasktable->show();
	selecttasktable->setUserId(m_user_id);
	connect(selecttasktable->buttonEnter,SIGNAL(clicked()),this,SLOT(selectTask()));
}
void CHistoryRecTable::displayUserName()
{
	DB_FMT data;
	InitDbData(&data,TABLE_USERINFO);
	comboSearchName->clear();
	comboSearchName->insertItem(0,QString::fromLocal8Bit("ȫ���û�"));
	if( SelectRecs(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);	
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_USERINFO);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	for(int i=0;i<data.rownum;i++)
	{
		comboSearchName->insertItem(i+1,QString::fromLocal8Bit(data_userinfo[i].longname),QVariant(data_userinfo[i].user_id));
	}
	FreeDbData(&data,TABLE_USERINFO);
}

void CHistoryRecTable::displayGroups()
{
	DB_FMT data;
	InitDbData(&data,TABLE_GROUPS);
	comboSearchName->clear();
	comboSearchName->insertItem(0,QString::fromLocal8Bit("�޷���"),QVariant(-1));
	if( SelectRecs(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);	
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_GROUPS);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	for(int i=0;i<data.rownum;i++)
	{
		if (data_groups[i].groups_id == -1 || data_groups[i].groups_id == 0)
			continue;
		comboSearchName->insertItem(i+1,QString::fromLocal8Bit(data_groups[i].name),QVariant(data_groups[i].groups_id));
	}
	FreeDbData(&data,TABLE_GROUPS);
}
void CHistoryRecTable::displayTodayRec()
{
	QDateTime time_start,time_end;
	time_start.setDate(QDate::currentDate());
	time_start.setTime(QTime(0,0,0,0));
	time_end.setDate(QDate::currentDate());
	time_end.setTime(QTime(23,59,59,999));
	timeStart->setDateTime(time_start);
	timeEnd->setDateTime(time_end);
	displayRec();
}

void CHistoryRecTable::displayRec()
{
	DB_FMT data;
	InitDbData(&data,TABLE_RECORD);
	data.cond_flag.flag_record.datetime = TRUE;
	data.cond_flag.flag_record.datetime_end = TRUE;
	strcpy(data.cond_seg.seg_record.datetime,timeStart->dateTime().toString(timeStart->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_seg.seg_record.datetime_end,timeEnd->dateTime().toString(timeEnd->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_flag.flag_record.datetime_opr,">=");
	strcpy(data.cond_flag.flag_record.datetime_end_opr,"<=");
	if (m_send_task_id != -1)
	{
		data.cond_flag.flag_record.send_task_id = TRUE;
		data.cond_seg.seg_record.send_task_id = m_send_task_id;
	}
	if (comboSearchType->currentText() == QString::fromLocal8Bit("�û���"))
	{
		if (comboSearchName->currentText() != QString::fromLocal8Bit("ȫ���û�"))
		{
			data.cond_flag.flag_record.user_id = TRUE;
			int index = comboSearchName->findText(comboSearchName->currentText());
			if (index == -1)
				data.cond_seg.seg_record.user_id = index;
			else
				data.cond_seg.seg_record.user_id = comboSearchName->itemData(index).toInt();
		}
	}
	else if (comboSearchType->currentText() == QString::fromLocal8Bit("����"))
	{
		data.cond_flag.flag_record.groups_id = TRUE;
		int index = comboSearchName->findText(comboSearchName->currentText());
		if (index == -1)
			data.cond_seg.seg_record.groups_id = index;
		else
			data.cond_seg.seg_record.groups_id = comboSearchName->itemData(index).toInt();	
	}
	setRecSourceModel(&data);
	m_send_task_id = -1;
}

void CHistoryRecTable::setRecSourceModel(DB_FMT *data)
{
	QProgressDialog *progressDlg=new QProgressDialog(this); 
	QFont font("ZYSong18030",12);  
	progressDlg->setFont(font);  
	progressDlg->setWindowModality(Qt::WindowModal);  
	progressDlg->setMinimumDuration(5);  
	progressDlg->setWindowTitle(tr("please wait"));  
	progressDlg->setLabelText(tr("�������ݿ�,���Ժ�......      "));  
	progressDlg->setCancelButtonText(tr("ȡ��"));  
	viewRec->setModel(NULL);
	if( SelectRecs(data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data->sql_str,data->sql_error);
		FreeDbData(data,TABLE_RECORD);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	if (data->rec_num > MAX_ROW_NUM_LARGE)
	{
		QMessageBox().information(this,QString::fromLocal8Bit("��Ϣ!"),QString::fromLocal8Bit("�Բ���������ѯ�ļ�¼���Ѵ��������ʾ������\n���ܻ���ɼ�¼��ʾ��ȫ�������������ѯ����!"),QMessageBox::Ok);
	}
	progressDlg->setRange(0,data->rownum-1);
	recSourceModel->clear();
	recSourceModel->setColumnCount(5);  
	recSourceModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("�û���"));  
	recSourceModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("ʱ��")); 
	recSourceModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("����"));
	recSourceModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("�¼�����")); 
	recSourceModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("������"));
	for (int i=0;i<data->rownum;i++)
	{
		QStandardItem* item0 = new QStandardItem(QString::fromLocal8Bit(data_record[i].userinfo_longname));  
		QStandardItem* item1 = new QStandardItem(QString::fromLocal8Bit(data_record[i].datetime));  
		QStandardItem* item2 = new QStandardItem(QString::number(data_record[i].ms));  
		QStandardItem* item3 = new QStandardItem(QString::fromLocal8Bit(data_record[i].content)); 
		QStandardItem* item4 = new QStandardItem(QString::fromLocal8Bit(data_record[i].host_name)); 
		QStandardItem* item5 = new QStandardItem(QString::fromLocal8Bit(data_record[i].logicalname));
		QStandardItem* item6 = new QStandardItem(QString::number(data_record[i].type)); 
		QStandardItem* item7 = new QStandardItem(QString::fromLocal8Bit(data_record[i].groups_name));  
		item0->setTextAlignment(Qt::AlignCenter);
		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);
		item4->setTextAlignment(Qt::AlignCenter);
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3 << item4 << item5 << item6 << item7; 
		recSourceModel->insertRow(0,items); 
		progressDlg->setValue(i); 
		if(progressDlg->wasCanceled())  
			break;
	}
	viewRec->setModel(recModelName);
	selectionModel = viewRec->selectionModel();
	viewRec->hideColumn(5);
	viewRec->hideColumn(6);
	viewRec->hideColumn(7);
	viewRec->setColumnWidth(0,70);
	viewRec->setColumnWidth(1,130);
	viewRec->setColumnWidth(2,40);
	viewRec->setColumnWidth(3,630);
	viewRec->setColumnWidth(4,90);
	FreeDbData(data,TABLE_RECORD);
}
void CHistoryRecTable::setFilterSearchType(const QString &text)
{
	labelName->setText(text+QString::fromLocal8Bit("��"));
	if (text == QString::fromLocal8Bit("�û���"))
	{
		displayUserName();
	}
	else if (text == QString::fromLocal8Bit("����"))
	{
		displayGroups();
	}
}
void CHistoryRecTable::setFilterSearchName(const QString &text)
{
	if (comboSearchType->currentText() == QString::fromLocal8Bit("�û���"))
	{
		recModelName->setFilterKeyColumn(0);
		if (comboSearchName->currentText() != QString::fromLocal8Bit("ȫ���û�"))
		{
			recModelName->setFilterRegExp(QRegExp(text));
		}
		else
		{
			recModelName->setFilterRegExp(QRegExp("/*"));
		}
	}
	else if (comboSearchType->currentText() == QString::fromLocal8Bit("����"))
	{
		recModelName->setFilterKeyColumn(7);
		recModelName->setFilterRegExp(QRegExp(text));
	}
}

void CHistoryRecTable::setFilterType()
{
	QString strRegExp = QString("-1");
	if (checkCmd->checkState()==Qt::Checked)
		strRegExp.append("|0");
	if (checkAlarm->checkState()==Qt::Checked)
		strRegExp.append("|1");
	if (checkOpt->checkState()==Qt::Checked)
		strRegExp.append("|3");
	if (checkCheck->checkState()==Qt::Checked)
		strRegExp.append("|4");
	if (checkInfo->checkState()==Qt::Checked)
		strRegExp.append("|2");

	recModelType->setFilterKeyColumn(6);
	recModelType->setFilterRegExp(QRegExp(strRegExp));
}
void CHistoryRecTable::delRec()
{
	if (JudgeUserRole(m_user_id,ROLE_STUDENT) == TRUE)
	{
		QMessageBox().warning(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��û��Ȩ��ɾ����¼!"),QMessageBox::Ok);
		return;
	}
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
	QModelIndexList indexes = selectionModel->selectedRows(0);
	for (int i=indexes.size()-1;i>=0;i--)
	{
		delRecFromHdb(indexes.at(i).row());
		recModelName->removeRow(indexes.at(i).row());
	}
}

void CHistoryRecTable::delRecFromHdb(int row)
{
	QString time,ms;
	DB_FMT data;
	InitDbData(&data,TABLE_RECORD);
	time = recModelName->data(recModelName->index(row,1)).toString();
	ms = recModelName->data(recModelName->index(row,2)).toString();
	data.cond_flag.flag_record.datetime = TRUE;
	data.cond_flag.flag_record.ms = TRUE;
	strcpy(data.cond_seg.seg_record.datetime,time.toLocal8Bit().data());
	data.cond_seg.seg_record.ms = ms.toShort();
	if( DeleteOneRec(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_RECORD);
		return;
	}
	FreeDbData(&data,TABLE_RECORD);
}
void CHistoryRecTable::selectTask()
{
	QModelIndexList indexes = selecttasktable->selectionModel->selectedRows(0);
	if (!selecttasktable->selectionModel->hasSelection())
	{
		QMessageBox().information(this,QString::fromLocal8Bit("��ʾ!"),QString::fromLocal8Bit("��ѡ������!"),QMessageBox::Ok);
		return;
	}
	else if (indexes.size() != 1)
	{
		QMessageBox().information(this,QString::fromLocal8Bit("��ʾ!"),QString::fromLocal8Bit("ֻ��ѡ��һ������!"),QMessageBox::Ok);
		return;
	}
	else
	{
		int curRow = indexes.at(0).row();
		QTableWidgetItem* start_time = selecttasktable->listTask->item(curRow,2);
		QTableWidgetItem* end_time = selecttasktable->listTask->item(curRow,3);
		timeStart->setDateTime(QDateTime::fromString(start_time->text(),QString("yyyy-MM-dd HH:mm:ss")));
		timeEnd->setDateTime(QDateTime::fromString(end_time->text(),QString("yyyy-MM-dd HH:mm:ss")));
		m_send_task_id = selecttasktable->listTask->item(curRow,0)->data(Qt::UserRole).toInt();
		selecttasktable->close();
		displayRec();
	}
}
void CHistoryRecTable::delRecord()
{
	if (JudgeUserRole(m_user_id,ROLE_STUDENT) == TRUE)
	{
		QMessageBox().warning(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��û��Ȩ��ɾ����¼!"),QMessageBox::Ok);
		return;
	}
	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle (QString::fromLocal8Bit("��ʾ"));
	msgBox.setInformativeText(QString::fromLocal8Bit("�Ƿ�ȷ��ɾ��\n%1\n��\n%2\n����ʷ��¼")
								.arg(timeStart->dateTime().toString(timeStart->displayFormat()))
								.arg(timeEnd->dateTime().toString(timeEnd->displayFormat())));
	msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Cancel) 
	{
		return;
	}
	DB_FMT data;
	InitDbData(&data,TABLE_RECORD);
	data.cond_flag.flag_record.datetime = TRUE;
	data.cond_flag.flag_record.datetime_end = TRUE;
	strcpy(data.cond_seg.seg_record.datetime,timeStart->dateTime().toString(timeStart->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_seg.seg_record.datetime_end,timeEnd->dateTime().toString(timeEnd->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_flag.flag_record.datetime_opr,">=");
	strcpy(data.cond_flag.flag_record.datetime_end_opr,"<=");
	if( DeleteOneRec(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		return;
	}
}
void CHistoryRecTable::print()
{
#ifdef   WIN32
	//shmPrintCond();
	//recPrint->start("print.exe");
	//exceltable->show();
#else
	#ifndef QT_NO_PRINTER
	QPrinter printer(QPrinter::ScreenResolution);
	QPrintPreviewDialog dlg(&printer);
	PrintView view;
	view.setModel(listRec->model());
	connect(&dlg, SIGNAL(paintRequested(QPrinter *)),
	&view, SLOT(print(QPrinter *)));
	dlg.exec();
	#endif
#endif 

	QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
		tr("Excel Files (*.xls)"));
	if (fileName.isEmpty())
		return;
	ExportExcelObject obj;
	obj.setOutputFilePath(fileName);
	obj.setOutputSheetTitle("sheet");
	obj.setTableView(viewRec);
	obj.addField(0, "�û���", "char(10)");
	obj.addField(1, "ʱ��", "datetime");
	obj.addField(2, "����", "int");
	obj.addField(3, "�¼�����", "char(200)");
	obj.addField(4, "������", "char(10)");
	obj.addField(5, "����", "char(20)");
	QProgressDialog *progressDlg=new QProgressDialog(this); 
	QFont font("ZYSong18030",12);  
	progressDlg->setFont(font);  
	progressDlg->setWindowModality(Qt::WindowModal);  
	progressDlg->setMinimumDuration(5);  
	progressDlg->setWindowTitle(tr("please wait"));  
	progressDlg->setLabelText(tr("���ڵ���......      "));  
	progressDlg->setCancelButtonText(tr("ȡ��"));  
	progressDlg->setRange(0,viewRec->model()->rowCount());  
	connect(&obj, SIGNAL(exportedRowCount(int)),progressDlg,SLOT(setValue(int)));
	connect(progressDlg, SIGNAL(canceled()),&obj,SLOT(cancel()));
	int retVal = obj.export2Excel();
	if( retVal > 0)
	{
		if (obj.initExcelObject() == TRUE)//���õ�����excel�ļ���ʽ
		{
			//obj.setColumnWidth(1,10);
			//obj.setColumnWidth(2,20);
			//obj.setColumnWidth(3,6);
			//obj.setColumnWidth(4,60);
			//obj.setColumnWidth(5,12);
			//obj.setColumnWidth(6,30);
			obj.resizeColumnsToContents();
			obj.setColumnFormat(2,"yyyy/m/d h:mm:ss");
			obj.setAlignment(0,1,Qt::AlignCenter);
			obj.setAlignment(0,2,Qt::AlignCenter);
			obj.setAlignment(0,3,Qt::AlignCenter);
			obj.setAlignment(0,4,Qt::AlignLeft);
			obj.setAlignment(0,5,Qt::AlignCenter);
			obj.setAlignment(0,6,Qt::AlignCenter);
			obj.setAlignment(1,0,Qt::AlignCenter);
			obj.save();
		}
		progressDlg->cancel();
		QMessageBox::information(this, QString::fromLocal8Bit("���"),
			QString(QString::fromLocal8Bit("������%1����¼")).arg(retVal));
	}
}
void CHistoryRecTable::exportToExcel()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
		tr("Excel Files (*.xls)"));
	if (fileName.isEmpty())
		return;
	ExcelObjectODBC excel(fileName);
	excel.SetSheetName(QString::fromLocal8Bit("sheet"));
	excel.AddHeader(0, "�û���", "char(10)");
	excel.AddHeader(1, "ʱ��", "char(22)");
	excel.AddHeader(2, "����", "int");
	excel.AddHeader(3, "�¼�����", "char(200)");
	excel.AddHeader(4, "������", "char(10)");
	excel.AddHeader(5, "����", "char(20)");
	if (excel.Open())
	{
		QProgressDialog *progressDlg=new QProgressDialog(this); 
		QFont font("ZYSong18030",12);  
		progressDlg->setFont(font);  
		progressDlg->setWindowModality(Qt::WindowModal);  
		progressDlg->setMinimumDuration(5);  
		progressDlg->setWindowTitle(tr("please wait"));  
		progressDlg->setLabelText(tr("���ڵ���......      "));  
		progressDlg->setCancelButtonText(tr("ȡ��"));  
		progressDlg->setRange(0,viewRec->model()->rowCount());  
		connect(&excel, SIGNAL(exportedRowCount(int)),progressDlg,SLOT(setValue(int)));
		connect(progressDlg, SIGNAL(canceled()),&excel,SLOT(cancel()));
		int retVal = excel.ExportTableViewToExcel(viewRec);
		if( retVal > 0)
		{
			progressDlg->cancel();
			QMessageBox::information(this, QString::fromLocal8Bit("���"),
				QString(QString::fromLocal8Bit("������%1����¼")).arg(retVal));
		}
	}
}
//void CHistoryRecTable::exportExcel()
//{
//	QDir excelPath;
//	QDir recPath;
//	QString appPath = qApp->applicationDirPath();
//	QString curDrive = appPath.mid(0,2);
// 	excelPath.setPath(curDrive+QString(ExcelPath));
//	recPath.setPath(curDrive+QString(HistoryPath));
//	QString absExcelPath = excelPath.absoluteFilePath("excel.xls");
//	absExcelPath.replace(QString("/"),QString("\\\\"));
//	QString recName = exceltable->comboProName->currentText();
//	QString date = QDate::currentDate().toString(QString("yyyy.MM.dd"));
//	QString extName(".xls");
//	QString absRecPath = recPath.absoluteFilePath(recName);
//	excel = new QAxObject( "Excel.Application", this ); //��ȡһ��Excel����
//	if (!excel)
//	{
//		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ʼ��Excel���󣬿���û�а�װoffice���!"),QMessageBox::Ok);
//		return;
//	}
//	QAxObject *workbooks = excel->querySubObject( "Workbooks" ); //�õ�Workbooks���ϵ�ָ�� 
//	if (!workbooks)
//	{
//		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ʼ��Excel���󣬿���û�а�װoffice���!"),QMessageBox::Ok);
//		return;
//	}
//	QAxObject *workbook = workbooks->querySubObject( "Open(const QString&)", absExcelPath ); //��Ӳ���ϵ�һ��Excel�ĵ� 
//	if (!workbook)
//	{
//		QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("Excel�ļ��򿪴���!"),QMessageBox::Ok);
//		return;
//	}
//	QAxObject *worksheets = workbook->querySubObject("worksheets");
//	QAxObject *worksheet = workbook->querySubObject("worksheets(int)", 1);
//	QAxObject *usedrange = worksheet->querySubObject("usedrange");//�õ��û���ʹ������
//	/********************************************�ϲ���Ԫ��*********************************************/
//	QAxObject *range = worksheet->querySubObject("Range(const QVariant&)", QVariant(QString("A1:G1")));
//	range->setProperty("HorizontalAlignment", 0xFFFFEFF4);
//	range->setProperty("VerticalAlignment", 0xFFFFEFF4);
//	range->setProperty("WrapText", false);
//	range->setProperty("Orientation", 0);
//	range->setProperty("AddIndent", false);
//	range->setProperty("IndentLevel", 0);
//	range->setProperty("ShrinkToFit", false);
//	range->setProperty("ReadingOrder", 0xFFFFEC76);
//	range->setProperty("MergeCells", true);
//	/****************************************************************************************************/
//	QAxObject* title1 = worksheet->querySubObject( "Cells( int, int )", 2, 1 );
//	title1->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("���") );
//	QAxObject* title2 = worksheet->querySubObject( "Cells( int, int )", 2, 2 );
//	title2->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("�û���") );
//	QAxObject* title3 = worksheet->querySubObject( "Cells( int, int )", 2, 3 );
//	title3->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("ʱ��") );
//	QAxObject* title4 = worksheet->querySubObject( "Cells( int, int )", 2, 4 );
//	title4->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("����") );
//	QAxObject* title5 = worksheet->querySubObject( "Cells( int, int )", 2, 5 );
//	title5->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("�¼�����") );
//	QAxObject* title6 = worksheet->querySubObject( "Cells( int, int )", 2, 6 );
//	title6->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("����") );
//	QAxObject* title7 = worksheet->querySubObject( "Cells( int, int )", 2, 7 );
//	title7->dynamicCall( "SetValue(const QString&)", QString::fromLocal8Bit("������") );
//	for (int i=0;i<recModelType->rowCount();i++)
//	{
//		QAxObject* cell = worksheet->querySubObject( "Cells( int, int )", i+3, 1 );
//		cell->dynamicCall( "SetValue(const QString&)", QString::number(i+1) );
//		for (int j=0;j<6;j++)
//		{
//			QAxObject* cell = worksheet->querySubObject( "Cells( int, int )", i+3, j+2 );
//			cell->dynamicCall( "SetValue(const QString&)", recModelType->data(recModelType->index(i, j)).toString());
//		}
//	}
//	QString cell;
//	cell = QString("A2")+QString(":")+QString("G")+QString::number(recModelType->rowCount()+2);
//	QAxObject* contentrange = worksheet->querySubObject("Range(const QVariant&)",QVariant(cell));
//	contentrange->setProperty( "VerticalAlignment", QVariant(-4108));//����Ϊ��ֱ���ж��뷽ʽ
//	contentrange->setProperty( "HorizontalAlignment", QVariant(-4108));//����Ϊˮƽ���ж��뷽ʽ
//	QAxObject* border = contentrange->querySubObject("Borders");
//	border->setProperty( "LineStyle", QVariant(1));//���ñ��߿���ʽ
//	QAxObject* font = contentrange->querySubObject("Font");
//	font->setProperty( "Name", QVariant(QString::fromLocal8Bit("����")));//��������Ϊ����
//	font->setProperty( "Name", QVariant(QString::fromLocal8Bit("Times New Roman")));//��������ΪTimes New Roman
//	font->setProperty( "Size", QVariant(11));//���������СΪ11
//	QAxObject* title = worksheet->querySubObject( "Cells( int, int )", 1, 1 );
//	title->dynamicCall( "SetValue(const QString&)", recName+QString::fromLocal8Bit("ģ�������ʷ��¼") );
//	title = title->querySubObject("Font");
//	title->setProperty( "Size", QVariant(23));//���ñ���������СΪ23
//	QAxObject *column = worksheet->querySubObject("columns(const QString&)", QString("E:E"));
//	column->setProperty( "HorizontalAlignment", QVariant(-4131));//���õ�F��Ϊˮƽ����뷽ʽ
//	QAxObject* titlerange = worksheet->querySubObject("Range(const QVariant&)",QVariant(QString("A1:G2")));
//	titlerange->setProperty( "HorizontalAlignment", QVariant(-4108));
//	titlerange = titlerange->querySubObject("Font");
//	titlerange->setProperty("Bold" , true);
//	QAxObject *rows = worksheet->querySubObject("rows");
//	rows->setProperty( "RowHeight", QVariant(20));//�����и�Ϊ20
//	QAxObject *titlerow = worksheet->querySubObject("rows(int)", 1);
//	titlerow->dynamicCall( "AutoFit()");//���õ�һ���и�Ϊ�Զ�
//	/********************************************�����п�**********************************************/
//	QAxObject *columnA = worksheet->querySubObject("columns(const QString&)", QString("A:A"));
//	columnA->setProperty( "ColumnWidth", QVariant(5));//���õ�һ���п�Ϊ5
//	QAxObject *columnB = worksheet->querySubObject("columns(const QString&)", QString("B:B"));
//	columnB->setProperty( "ColumnWidth", QVariant(10));
//	QAxObject *columnC = worksheet->querySubObject("columns(const QString&)", QString("C:C"));
//	columnC->setProperty( "ColumnWidth", QVariant(15));
//	QAxObject *columnD = worksheet->querySubObject("columns(const QString&)", QString("D:D"));
//	columnD->setProperty( "ColumnWidth", QVariant(5));
//	QAxObject *columnE = worksheet->querySubObject("columns(const QString&)", QString("E:E"));
//	columnE->setProperty( "ColumnWidth", QVariant(76));
//	QAxObject *columnF = worksheet->querySubObject("columns(const QString&)", QString("F:F"));
//	columnF->setProperty( "ColumnWidth", QVariant(30));
//	QAxObject *columnG = worksheet->querySubObject("columns(const QString&)", QString("G:G"));
//	columnG->setProperty( "ColumnWidth", QVariant(12));
//	/**************************************************************************************************/
//	excel->dynamicCall(" SetScreenUpdating(bool)",true);
//	if (QFile::exists(absRecPath+date+extName))
//	{
//		for(int i=1;i<100;i++)
//		{
//			if (!QFile::exists(absRecPath+date+QString("-")+QString::number(i)+extName))
//			{
//				workbook->querySubObject( "SaveAs(const QString&)",absRecPath+date+QString("-")+QString::number(i)+extName);
//				break;
//			}
//		}
//	}
//	else
//	{
//		workbook->querySubObject( "SaveAs(const QString&)",absRecPath+date+extName); 
//	}
//	
//	excel->dynamicCall( "SetVisible(bool)", TRUE );
//	exceltable->reject();
//}
void CHistoryRecTable::shmPrintCond()
{
	HANDLE hMemShare;
	hMemShare = CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,sizeof(printCond),L"MemShare");
	if(hMemShare == NULL)
	{
		printf("���乲���ڴ�ʧ��");
		return;
	}
	lpprint_cond = (printCond *)MapViewOfFile(hMemShare, FILE_MAP_WRITE,0,0,sizeof(printCond));
	if(lpprint_cond == NULL)
	{
		printf("ӳ�乲���ڴ�ʧ��");
		return;
	}
	*lpprint_cond = print_cond;
	UnmapViewOfFile(lpprint_cond);
}
/*******************************************************CSelectTaskTable*****************************************************************/
CSelectTaskTable::CSelectTaskTable(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	setControlAtt();
	actionDel = new QAction(QString::fromLocal8Bit("ɾ����¼"), this);
	selectionModel = listTask->selectionModel();
	connect(listTask,SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(showSendTaskMenu(const QPoint &)));
	connect(actionDel,SIGNAL(triggered()),this,SLOT(delSendTask()));
}
void CSelectTaskTable::setControlAtt()
{
	listTask->setSelectionBehavior(QAbstractItemView::SelectRows);
	listTask->setSelectionMode(QAbstractItemView::ExtendedSelection); 
	listTask->setEditTriggers(QTableWidget::NoEditTriggers);
	listTask->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	listTask->setSortingEnabled(true);
	listTask->setColumnWidth(0,220);
	listTask->setColumnWidth(1,70);
	listTask->setColumnWidth(2,130);
	listTask->setColumnWidth(3,130);
}
void CSelectTaskTable::contextMenuEvent(QContextMenuEvent *event)
{
	event->ignore();
	QMenu* popMenu = new QMenu(this);
	popMenu->addAction(actionDel);
	popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}
void CSelectTaskTable::showSendTaskMenu(const QPoint &pos)
{
	QMenu* popMenu = new QMenu(this);
	popMenu->addAction(actionDel);
	popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
}
void CSelectTaskTable::loadChinese()
{
	QTranslator translator;
	translator.load("Teachermanage_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}

void CSelectTaskTable::loadEnglish()
{
	QTranslator translator;
	translator.load("Teachermanage_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSelectTaskTable::showEvent ( QShowEvent * event )
{
	displayTask();
}
int CSelectTaskTable::displayTask()
{
	DB_FMT data;
	InitDbData(&data,TABLE_SEND_TASK);
	if( SelectRecs(&data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SEND_TASK);
		qDebug("��ѯ���ݿ�ʧ��!");
		return -1;
	}
	listTask->clearContents();
	listTask->setRowCount(data.rownum);
	int rownum = data.rownum;
	for(int i=0;i<rownum;i++)
	{		
		QTableWidgetItem* itemTaskName = new QTableWidgetItem(QString::fromLocal8Bit(data_send_task[i].task_name));
		itemTaskName->setData(Qt::UserRole,data_send_task[i].send_task_id);
		QTableWidgetItem* itemUserName = new QTableWidgetItem(QString::fromLocal8Bit(data_send_task[i].userinfo_longname));
		itemUserName->setTextAlignment(Qt::AlignCenter);
		listTask->setItem(i,0,itemTaskName);
		listTask->setItem(i,1,itemUserName);
		listTask->setItem(i,2,new QTableWidgetItem(QString::fromLocal8Bit(data_send_task[i].start_time)));
		listTask->setItem(i,3,new QTableWidgetItem(QString::fromLocal8Bit(data_send_task[i].end_time)));
	}
	FreeDbData(&data,TABLE_SEND_TASK);
	return rownum;
}
void CSelectTaskTable::delSendTask()
{
	if (JudgeUserRole(m_user_id,ROLE_STUDENT) == TRUE)
	{
		QMessageBox().warning(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��û��Ȩ��ɾ����¼!"),QMessageBox::Ok);
		return;
	}
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
	if (selectionModel->hasSelection())
	{
		QModelIndexList indexes = selectionModel->selectedRows(0);
		for (int i=indexes.size()-1;i>=0;i--)
		{
			int send_task_id = listTask->item(indexes.at(i).row(),0)->data(Qt::UserRole).toInt();
			delRecordFromHdb(send_task_id);
			delSendTaskFromHdb(send_task_id);
			listTask->removeRow(indexes.at(i).row());
		}
	}
}
void CSelectTaskTable::delSendTaskFromHdb(int send_task_id)
{
	DB_FMT data;
	InitDbData(&data,TABLE_SEND_TASK);
	data.cond_flag.flag_send_task.send_task_id = TRUE;
	data.cond_seg.seg_send_task.send_task_id = send_task_id;
	if( DeleteOneRec(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_SEND_TASK);
		return;
	}
	FreeDbData(&data,TABLE_SEND_TASK);
}
void CSelectTaskTable::delRecordFromHdb(int send_task_id)
{
	DB_FMT data;
	InitDbData(&data,TABLE_RECORD);
	data.cond_flag.flag_record.send_task_id = TRUE;
	data.cond_seg.seg_record.send_task_id = send_task_id;
	if( DeleteOneRec(&data) != TRUE)
	{
		HdbLogWrite(data.sql_str,data.sql_error);
		FreeDbData(&data,TABLE_RECORD);
		return;
	}
}
/***************************************************CExcelTable*****************************************************/
//CExcelTable::CExcelTable(QWidget* parent)
//:QDialog(parent)
//{
//	setupUi(this);
//	this->setAttribute(Qt::WA_DeleteOnClose);
//	this->setModal(true);
//	readConfig();
//	//readTemplateDef();
//	comboProName->setCurrentIndex(-1);
//	comboProName->setEditable(true);
//	connect(buttonExport,SIGNAL(clicked()),this,SLOT(exportExcel()));
//}
//void CExcelTable::loadChinese()
//{
//	QTranslator translator;
//	translator.load("Teachermanage_zh_CN");
//	qApp->installTranslator(&translator);
//	retranslateUi(this);
//}
//
//void CExcelTable::loadEnglish()
//{
//	QTranslator translator;
//	translator.load("Teachermanage_en");
//	qApp->installTranslator(&translator);
//	retranslateUi(this);
//}
//void CExcelTable::exportExcel()
//{
//	if (comboProName->currentText() == QString(""))
//	{
//		QMessageBox().information(this,QString::fromLocal8Bit("��ʾ!"),QString::fromLocal8Bit("��ѡ������빤������!"),QMessageBox::Ok);
//		return;
//	}
//	else
//	{
//		writeConfig();
//		emit exp();
//		readConfig();
//	}	
//}
//void CExcelTable::readConfig()
//{
//	QString myfile = TeacherManageConfigPath;
//	QSettings mySetting(myfile,QSettings::IniFormat);
//	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
//	mySetting.beginGroup("proname");
//	QStringList keys = mySetting.childKeys();
//	comboProName->clear();
//	for (int i=0;i<keys.size();i++)
//	{
//		comboProName->insertItem(i,mySetting.value(keys.at(i)).toString());
//	}
//}
//void CExcelTable::writeConfig()
//{
//	QString myfile = TeacherManageConfigPath;
//	QSettings mySetting(myfile,QSettings::IniFormat);
//	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
//	mySetting.beginGroup("proname");
//	QStringList keys = mySetting.childKeys();
//	for (int i=0;i<keys.size();i++)
//	{
//		if(comboProName->currentText() == mySetting.value(keys.at(i)).toString())
//		{
//			return;
//		}
//	}
//	mySetting.setValue(QString("name")+QString::number(keys.size()+1),comboProName->currentText());
//}
//void CExcelTable::readTemplateDef()
//{
//	char FileName[100]="/home/ems/system/ots/TeacherManage/proname.def";
//	char StrTmp[100];
//	int i=0;
//	FILE *fp;
//	if (( fp = fopen ( FileName,"r"))==NULL)
//	{
//		printf ("==== can't open (w) the file %s! \n",FileName );
//		return;
//	}
//	else
//	{
//		 printf ( "\n==== open (w) %s  success! \n",FileName  ); 
//	}
//	while ( fscanf(fp,"%s",StrTmp)!=EOF )
//	{
//		if(strcmp(StrTmp,"BEGIN")==0) break;
//	}        
//	while ( fscanf(fp,"%s",StrTmp)!=EOF )
//	{
//		if(strcmp(StrTmp,"NAME")==0)
//		{
//			fscanf(fp,"%s",StrTmp);
//			comboProName->insertItem(i++,QString(StrTmp));
//		}
//
//		if(strcmp(StrTmp,"END")==0)
//		{
//			break;
//		}
//	}
//	fclose(fp);
//}
/************************************************PrintView*********************************************************/
PrintView::PrintView()
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PrintView::print(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
	resize(printer->width(), printer->height());
	render(printer);
#endif
}


