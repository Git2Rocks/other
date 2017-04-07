#include "scorerec.h"

CScoreRec::CScoreRec(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	recSourceModel = new QStandardItemModel;
	recModel = new QSortFilterProxyModel;
	recModel->setSourceModel(recSourceModel);
	listScoreRec->setSelectionBehavior(QAbstractItemView::SelectRows);
	listScoreRec->setEditTriggers(QTableView::NoEditTriggers);
	listScoreRec->setSelectionMode(QAbstractItemView::ExtendedSelection);
	listScoreRec->verticalHeader()->setVisible(false);
	connect(comboMode,SIGNAL(currentIndexChanged(int)),this,SLOT(modeChanged(int)));
	connect(comboContent,SIGNAL(currentTextChanged(const QString &)),this,SLOT(filterChanged(const QString &)));
	connect(comboContent,SIGNAL(editTextChanged(const QString &)),this,SLOT(filterChanged(const QString &)));
	connect(buttonSearch,SIGNAL(clicked()),this,SLOT(displayScoreRec()));
	connect(buttonSearchTaday,SIGNAL(clicked()),this,SLOT(displayTodayRec()));
	connect(buttonExport,SIGNAL(clicked()),this,SLOT(exportToExcel()));
	comboMode->addItem(QString::fromLocal8Bit("ȫ����¼"));
	comboMode->addItem(QString::fromLocal8Bit("�û���"));
	comboMode->addItem(QString::fromLocal8Bit("������"));	
}
void CScoreRec::showEvent(QShowEvent *event)
{
	comboMode->setCurrentIndex(0);
	dateTimeEditStart->setDateTime(QDateTime::currentDateTime());
	dateTimeEditEnd->setDateTime(QDateTime::currentDateTime().addSecs(-3600));
}
void CScoreRec::modeChanged(int index)
{
	DB_FMT data;
	comboContent->clear();
	switch(index)
	{
		case 0:
			comboContent->addItem(QString::fromLocal8Bit("��ѡ��ʽ"));
			comboContent->setEditable(false);
			labelContent->setText(QString::fromLocal8Bit("ȫ����¼:"));
			break;
		case 1:
			InitDbData(&data,TABLE_USERINFO);
			data.cond_flag.flag_userinfo.role = TRUE;
			data.cond_seg.seg_userinfo.role = 0;
			if( SelectRecs(&data) != TRUE)
			{		
				HdbLogWrite(data.sql_str,data.sql_error);
				return;
			}
			for (int i=0;i<data.rownum;i++)
				comboContent->addItem(QString::fromLocal8Bit(data_userinfo[i].longname),QVariant(data_userinfo[i].user_id));
			comboContent->setEditable(true);
			labelContent->setText(QString::fromLocal8Bit("�û���:"));
			break;
		case 2:
			InitDbData(&data,TABLE_TASK);
			if( SelectRecs(&data) != TRUE)
			{		
				HdbLogWrite(data.sql_str,data.sql_error);
				return;
			}
			for (int i=0;i<data.rownum;i++)
				comboContent->addItem(QString::fromLocal8Bit(data_task[i].name),QVariant(data_task[i].task_id));
			comboContent->setEditable(true);
			labelContent->setText(QString::fromLocal8Bit("������:"));
			break;
		default:
			break;
	}
}
void CScoreRec::filterChanged(const QString &text)
{
	if (comboMode->currentText() == QString::fromLocal8Bit("�û���"))
	{
		recModel->setFilterKeyColumn(0);
		recModel->setFilterRegExp(QRegExp(text));
	}
	else if (comboMode->currentText() == QString::fromLocal8Bit("������"))
	{
		recModel->setFilterKeyColumn(2);
		recModel->setFilterRegExp(QRegExp(text));
	}
}
void CScoreRec::displayTodayRec()
{
	QDateTime time_start,time_end;
	time_start.setDate(QDate::currentDate());
	time_start.setTime(QTime(0,0,0,0));
	time_end.setDate(QDate::currentDate());
	time_end.setTime(QTime(23,59,59,999));
	dateTimeEditStart->setDateTime(time_start);
	dateTimeEditEnd->setDateTime(time_end);
	displayScoreRec();
}

void CScoreRec::displayScoreRec()
{
	DB_FMT data;
	InitDbData(&data,TABLE_SEND_TASK);
	data.cond_flag.flag_send_task.end_time_start = TRUE;
	data.cond_flag.flag_send_task.end_time_end = TRUE;
	strcpy(data.cond_seg.seg_send_task.end_time_start,dateTimeEditStart->dateTime().toString(dateTimeEditStart->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_seg.seg_send_task.end_time_end,dateTimeEditEnd->dateTime().toString(dateTimeEditEnd->displayFormat()).toLocal8Bit().data());
	strcpy(data.cond_flag.flag_send_task.end_time_start_opr,">=");
	strcpy(data.cond_flag.flag_send_task.end_time_end_opr,"<=");
	setScoreRecModel(&data);
}
void CScoreRec::setScoreRecModel(DB_FMT *data)
{
	QProgressDialog *progressDlg=new QProgressDialog(this); 
	QFont font("ZYSong18030",12);  
	progressDlg->setFont(font);  
	progressDlg->setWindowModality(Qt::WindowModal);  
	progressDlg->setMinimumDuration(5);  
	progressDlg->setWindowTitle(tr("please wait"));  
	progressDlg->setLabelText(tr("�������ݿ�,���Ժ�......      "));  
	progressDlg->setCancelButtonText(tr("ȡ��"));  
	listScoreRec->setModel(NULL);
	if( SelectRecs(data) != TRUE)
	{
		//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��ѯ���ݿ�ʧ��!"),QMessageBox::Ok);		
		HdbLogWrite(data->sql_str,data->sql_error);
		qDebug("��ѯ���ݿ�ʧ��!");
		return;
	}
	progressDlg->setRange(0,data->rownum-1);
	recSourceModel->clear();
	recSourceModel->setColumnCount(5);  
	recSourceModel->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("�û���"));  
	recSourceModel->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("��������")); 
	recSourceModel->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("��ʼʱ��"));
	recSourceModel->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("����ʱ��")); 
	recSourceModel->setHeaderData(4,Qt::Horizontal,QString::fromLocal8Bit("�ɼ�"));
	for (int i=0;i<data->rownum;i++)
	{
		QStandardItem* item0 = new QStandardItem(QString::fromLocal8Bit(data_send_task[i].userinfo_longname));  
		QStandardItem* item1 = new QStandardItem(QString::fromLocal8Bit(data_send_task[i].task_name));  
		QStandardItem* item2 = new QStandardItem(QString::fromLocal8Bit(data_send_task[i].start_time));  
		QStandardItem* item3 = new QStandardItem(QString::fromLocal8Bit(data_send_task[i].end_time)); 
		QStandardItem* item4 = new QStandardItem(QString::number(data_send_task[i].score)); 
		item0->setTextAlignment(Qt::AlignCenter);
		item1->setTextAlignment(Qt::AlignCenter);
		item2->setTextAlignment(Qt::AlignCenter);
		item3->setTextAlignment(Qt::AlignCenter);
		item4->setTextAlignment(Qt::AlignCenter);
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3 << item4; 
		recSourceModel->insertRow(0,items); 
		progressDlg->setValue(i); 
		if(progressDlg->wasCanceled())  
			break;
	}
	listScoreRec->setModel(recModel);
	selectionModel = listScoreRec->selectionModel();
	listScoreRec->setColumnWidth(0,80);
	listScoreRec->setColumnWidth(1,290);
	listScoreRec->setColumnWidth(2,140);
	listScoreRec->setColumnWidth(3,140);
	listScoreRec->setColumnWidth(4,80);
}
void CScoreRec::exportToExcel()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
		tr("Excel Files (*.xls)"));
	if (fileName.isEmpty())
		return;
	ExcelObjectODBC excel(fileName);
	excel.AddHeader(0, "�û���", "char(10)");
	excel.AddHeader(1, "��������", "char(200)");
	excel.AddHeader(2, "��ʼʱ��", "char(22)");
	excel.AddHeader(3, "����ʱ��", "char(22)");
	excel.AddHeader(4, "�ɼ�", "char(6)");
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
		progressDlg->setRange(0,listScoreRec->model()->rowCount());  
		connect(&excel, SIGNAL(exportedRowCount(int)),progressDlg,SLOT(setValue(int)));
		connect(progressDlg, SIGNAL(canceled()),&excel,SLOT(cancel()));
		int retVal = excel.ExportTableViewToExcel(listScoreRec);
		if( retVal > 0)
		{
			progressDlg->cancel();
			QMessageBox::information(this, QString::fromLocal8Bit("���"),
				QString(QString::fromLocal8Bit("������%1����¼")).arg(retVal));
		}
	}
}