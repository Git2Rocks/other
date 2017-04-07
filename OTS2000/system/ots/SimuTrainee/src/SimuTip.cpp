#include "SimuTip.h"

CSimuTipDlg *dlgSimuTip=NULL;
CSimuTipDlg *dlgSimuTipExample=NULL;
CSetSimuTip *pSetSimuTip=NULL;
QColor tipColor("white");
QColor curTipColor("red");
QColor backgroundColor("black");
QFont tipFont(QString::fromLocal8Bit("����"), 20, QFont::Normal);
//int mode(TIP_MODE_SINGLE);
int mode(TIP_MODE_SINGLE);
QPoint position(0,0);
QSize sizeW(800,20);
bool isAutoSize(false);
int alpha(255);
CSimuTipDlg::CSimuTipDlg(QWidget *parent,int task_id,int send_task_id)
: QWidget(parent,Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint)
{
	m_task_id = task_id;
	m_send_task_id = send_task_id;
	isLocked = FALSE;
	layout = new QGridLayout();
	//this->setAttribute(Qt::WA_DeleteOnClose);
	this->setAttribute(Qt::WA_TranslucentBackground, true);//͸������
	this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	if (ConnectHDB(db_tip,"dbTIPDLG")!=int(TRUE))
	{
		return;
	}
	ReadSimuTipConfig();
	updateTaskTipMap();
	lab = new QLabel(this);
	lab->setMaximumWidth(50);

	setupUi();
// 	setupUi();
// 	ReadSimuTipConfig();
// 	updateTaskTipMap();


 	updateAttrib();
	setCurStepShow(0);
////////////DZY REMOVED FOR DEBUG 20140728////////////////////////////
// 	if (task_id != -1)
// 	{
// 		simuTipThread = new SimuTipThread(m_task_id,m_send_task_id,getStepNum(),this);
// 		connect(simuTipThread, SIGNAL(sigStepFinished(int,int)), this, SLOT(setCurStepShow(int,int)));
// 		connect(simuTipThread, SIGNAL(sigStepFinished(int,int)), this, SLOT(setCurStepShow(int,int)));
// 	}
	connect(pSetSimuTip,SIGNAL(sigUpdateAttrib()),this,SLOT(updateAttrib()));
}
CSimuTipDlg::~CSimuTipDlg()
{
	CloseHDB(db_tip);
}
void CSimuTipDlg::showEvent(QShowEvent *event)
{
////////////DZY REMOVED FOR DEBUG 20140728////////////////////////////
// 	if (m_task_id != -1)
// 	{
//  		if (!simuTipThread->isRunning())
//  			simuTipThread->start();
// 	}
	this->move(position);
	event->accept();
}
void CSimuTipDlg::hideEvent(QHideEvent *event)
{
	event->accept();
}
void CSimuTipDlg::closeEvent(QCloseEvent *event)
{
	WriteSimuTipConfig();
////////////DZY REMOVED FOR DEBUG 20140728////////////////////////////
// 	if (m_task_id != -1)
// 	{
// 		if (simuTipThread->isRunning())
// 		{
// 			simuTipThread->stop();
// 			//simuTipThread->exit();
// 			//simuTipThread->terminate();
// 			simuTipThread->wait();
// 			delete simuTipThread;
// 		}
// 	}
	event->accept();
}
void CSimuTipDlg::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) //���������
	{
		dragPosition = event->globalPos() - frameGeometry().topLeft();
		//globalPos()��ȡ�����ڵ����·����frameGeometry().topLeft()��ȡ���������Ͻǵ�λ��
		event->accept();   //����¼���ϵͳ����
	}
	if (event->button() == Qt::RightButton) 
	{
		QMenu* popMenu = new QMenu(this);
		QAction *actionSetSimuTip = new QAction(QString::fromLocal8Bit("������ʾ����"),popMenu);
		QAction *actionLock = new QAction(QString::fromLocal8Bit("������ʾ����"),popMenu);
		QAction *actionUnLock = new QAction(QString::fromLocal8Bit("������ʾ����"),popMenu);
		QAction *actionHide = new QAction(QString::fromLocal8Bit("������ʾ����"),popMenu);
		popMenu->addAction(actionSetSimuTip);
		popMenu->addAction(actionLock);
		popMenu->addAction(actionUnLock);
		popMenu->addAction(actionHide);
		connect(actionSetSimuTip,SIGNAL(triggered()),this,SLOT(openSetSimuTip()));
		connect(actionLock,SIGNAL(triggered()),this,SLOT(lock()));
		connect(actionUnLock,SIGNAL(triggered()),this,SLOT(unLock()));
		connect(actionHide,SIGNAL(triggered()),this,SLOT(hide()));
		popMenu->exec(QCursor::pos()); // �˵����ֵ�λ��Ϊ��ǰ����λ��
	}
}

void CSimuTipDlg::mouseMoveEvent(QMouseEvent * event)
{
	if (isLocked)
	{
		event->ignore();
	}
	else
	{
		if (event->buttons() == Qt::LeftButton) //�����������������ʱ��
		{
			move(event->globalPos() - dragPosition);//�ƶ�����
			event->accept();
		}
	}
	position = this->pos();
	WriteSimuTipConfig();
}
void CSimuTipDlg::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	backgroundColor.setAlpha(alpha);
	painter.fillRect(0, 0, rect().width(), rect().height(),backgroundColor);
}
void CSimuTipDlg::enterEvent(QEvent *event)
{
	m_alpha = alpha;
	if (alpha == 0)
	{
		alpha = 5;
		repaint();
	}
	event->accept();
}
void CSimuTipDlg::leaveEvent(QEvent *event)
{
	alpha = m_alpha;
	repaint();
	event->accept();
}
void CSimuTipDlg::lock()
{
	isLocked = TRUE;
}
void CSimuTipDlg::unLock()
{
	isLocked = FALSE;
}
void CSimuTipDlg::updateTaskTipMap()
{
	mapTaskTip.clear();
	if (m_task_id == -1)
	{
		mapTaskTip.insert(0,new QLabel);
		for (int i=1;i<=5;i++)
		{
			QLabel *label = new QLabel(QString::fromLocal8Bit("ʾ����ʾ��%1��").arg(i));
			label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
			mapTaskTip.insert(i,label);
		}
		int jj = mapTaskTip.count();
		QLabel *label = new QLabel(QString::fromLocal8Bit("�����Ѿ����"));
		label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
		mapTaskTip.insert(mapTaskTip.count(),label);
	}
	else
	{
		DB_FMT data;
		InitDbData(&data,TABLE_SUBJECT);
		data.cond_flag.flag_subject.task_id=TRUE;
		data.cond_seg.seg_subject.task_id=m_task_id;
		if (SelectRecs(&data,db_tip)!=(int)TRUE)
		{
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
		else if (data.rownum>0)
		{
			mapTaskTip.insert(0,new QLabel);
			for (int i=0;i<data.rownum;i++)
			{
				QString tipStr = QString::fromLocal8Bit(data_subject[i].subject_tip).trimmed();
				QString 	str = QString::fromLocal8Bit("��")+QString::number(data_subject[i].step)+QString::fromLocal8Bit("����");
				tipStr =str+  tipStr;
				if (tipStr.size())
				{
					QLabel *label = new QLabel(tipStr);
					label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
					mapTaskTip.insert(data_subject[i].step,label);
				}
			}
			QLabel *label = new QLabel(QString::fromLocal8Bit("�����Ѿ����"));
			label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
			mapTaskTip.insert(mapTaskTip.count(),label);
		}		
	}
	if (mapTaskTip.size() == 0)
	{
		mapTaskTip.insert(0,new QLabel);
		QLabel *label = new QLabel(QString::fromLocal8Bit("��ǰ��������ʾ��Ϣ"));
		label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
		mapTaskTip.insert(1,label);
	}
}
void CSimuTipDlg::setupUi()
{
	labelTip = new QLabel(this);
	labelTip->setText(QString::fromLocal8Bit(" �� �� �� ʾ:"));
	labelTip->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	layout->setContentsMargins(2,2,2,2);
// 	if (mode == TIP_MODE_SINGLE)
// 	{
// 		QSpacerItem *spacer= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
// 		//lab->setText(QString::fromLocal8Bit(""));
// 		layout->addWidget(labelTip,0,0,Qt::AlignLeft);
// 		layout->addWidget(lab,0,1,Qt::AlignRight);//dzy
// 		layout->addWidget(mapTaskTip.value(0),0,2,Qt::AlignCenter);
// 		layout->addItem(spacer,0,3,Qt::AlignLeft);
// 	}
// 	else if (mode == TIP_MODE_MULTI)
// 	{		
// 		layout->addWidget(labelTip,0,0,Qt::AlignLeft);
// 		QMap<short,QLabel *>::const_iterator i = mapTaskTip.constBegin();
// // 		while (i != mapTaskTip.constEnd())
// // 		{
// // 			QSpacerItem *spacer= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
// // 			layout->addWidget(i.value(),i.key(),0,Qt::AlignLeft);
// // 			layout->addItem(spacer,i.key(),1);
// // 			i++;
// // 		}
// 		while (i != mapTaskTip.constEnd())
// 		{
// 			QSpacerItem *spacer= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
// 		//DZY �Ӳ����
// 				QString str;
// 				str = QString::fromLocal8Bit("��")+QString::number(i.key())+QString::fromLocal8Bit("����");
// 				QLabel *lab2 = new QLabel;	
// 				lab2->setText(str);
// 				lab2->setStyleSheet(QString::fromLocal8Bit("QLabel{color: rgb(160, 0, 50);font: 16pt ����;}"));
// 				if (i.key()>=1&&i.key()< mapTaskTip.constEnd().key()-1)
// 				{
// 					layout->addWidget(lab2,i.key(),0);//dzy
// 
// 					layout->addWidget(i.value(),i.key(),1,Qt::AlignLeft);
// 				//	layout->addItem(spacer,i.key(),2);
// 				}
// 				else if (i.key()==0)
// 				{
// 					i++;
// 					continue;
// 				}
// 				else if(i.key() == mapTaskTip.constEnd().key()-1) 
// 				{
// 					lab2->setText("");
// 					layout->addWidget(lab2,i.key(),0,Qt::AlignLeft);//dzy
// 					layout->addWidget(i.value(),i.key(),1,Qt::AlignLeft);
// 					layout->addItem(spacer,i.key(),2);
// 				}
// 			i++;
// 		}
//	}
	if (mode == TIP_MODE_SINGLE)
	{
		QSpacerItem *spacer= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
		layout->addWidget(labelTip,0,0);
		layout->addWidget(mapTaskTip.value(0),0,1,Qt::AlignLeft);
		layout->addItem(spacer,0,2);
	}
	if (mode == TIP_MODE_MULTI)
	{
		layout->addWidget(labelTip,0,0,Qt::AlignLeft);
		QMap<short,QLabel *>::const_iterator i = mapTaskTip.constBegin();
		while (i != mapTaskTip.constEnd())
		{
			QSpacerItem *spacer= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
			layout->addWidget(i.value(),i.key(),0,Qt::AlignLeft);
			layout->addItem(spacer,i.key(),1);
			i++;
		}
	}
	this->setLayout(layout);
}
void CSimuTipDlg::setCurStepShow(int step,int m_mode)//dzy new added int mode = 0
{
	curTaskTipStep = step+1;
	if (m_mode == 0)
	{
		if (mode == TIP_MODE_SINGLE)
		{
			QString str;
			str = QString::fromLocal8Bit("��")+QString::number(curTaskTipStep)+ QString::fromLocal8Bit("����");//dzy
			lab->setText(str);
			mapTaskTip.value(0)->setText(mapTaskTip.value(curTaskTipStep)->text());
		}
		else if (mode == TIP_MODE_MULTI)
		{
			setTipColor(tipColor);
			//setCurTipColor(curTipColor);
		}
	}
	else if (m_mode == 1)//dzy added ���賬ʱ
	{		
		if (mode == TIP_MODE_SINGLE)
		{
			QString str;
			str = QString::fromLocal8Bit("��")+QString::number(curTaskTipStep)+ QString::fromLocal8Bit("����");//dzy
			lab->setText(str);
			mapTaskTip.value(0)->setText(mapTaskTip.value(curTaskTipStep)->text());
		}
		else if (mode == TIP_MODE_MULTI)
		{
			QColor overtimecolor(255,0,255);
			setTipColor(overtimecolor);
			QPalette pat;
			pat.setColor(QPalette::WindowText,overtimecolor);
			if(curTaskTipStep>=1)
				mapTaskTip.value(curTaskTipStep-1)->setPalette(pat);
			//setCurTipColor(curTipColor);
		}
	}
	
}

void CSimuTipDlg::updateAttrib()
{
	//setupUi();
	setAutoSize(isAutoSize);
	setSize(sizeW);
	setFont(tipFont);
	setTipColor(tipColor);
	//setCurTipColor(curTipColor);
	//setBackgroundColor(backgroundColor);
	//setOpacity(level);
	//setTransparent(isTransparent);
	repaint();
}
void CSimuTipDlg::setAutoSize(bool flag)
{
	if (flag)
	{
		layout->setSizeConstraint(QLayout::SetFixedSize);
	}
	else
	{
		layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	}
}
void CSimuTipDlg::setSize(QSize size)
{
	resize(size);
}
void CSimuTipDlg::setTransparent(bool flag)
{
	if (flag)
	{
		setWindowOpacity(1);
		setAttribute(Qt::WA_TranslucentBackground,true);//����͸��-�����������͸��,����͸��  
	}
	else
	{
		setAttribute(Qt::WA_NoSystemBackground,false);
		setAttribute(Qt::WA_TranslucentBackground,false);
		setBackgroundColor(backgroundColor);
	}
}
void CSimuTipDlg::setText(const QString &text)
{
	
}

void CSimuTipDlg::setTipColor(QColor color)
{
	QPalette pat;
	pat.setColor(QPalette::WindowText,color);
	labelTip->setPalette(pat);
	lab->setPalette(pat);//dzy
	for (int i=0;i<mapTaskTip.size();i++)
	{
		mapTaskTip.value(i)->setPalette(pat);
	}
}
void CSimuTipDlg::setBackgroundColor(QColor color)
{
	QPalette pat;
	pat.setColor(QPalette::Background,color);
	pat.setBrush(QPalette::Background,QBrush(color));
	setPalette(pat);
}
void CSimuTipDlg::setFont(QFont font)
{
	labelTip->setFont(font);
	lab->setFont(font);
	int k = mapTaskTip.size();
	if (k<=0)
	{
		return;
	}
	for (int i=0;i<mapTaskTip.size();i++)
	{
		mapTaskTip.value(i)->setFont(font);
	}
}
void CSimuTipDlg::setOpacity(int level)
{
	qreal real = level*0.1;
	setWindowOpacity(real);
}
void CSimuTipDlg::setCurTipColor(QColor color)
{
	QPalette pat;
	pat.setColor(QPalette::WindowText,color);
	if (mode == TIP_MODE_SINGLE)
		mapTaskTip.value(0)->setPalette(pat);
	if (mode == TIP_MODE_MULTI)
		mapTaskTip.value(curTaskTipStep)->setPalette(pat);
}
void CSimuTipDlg::openSetSimuTip()
{
	pSetSimuTip->init();
	pSetSimuTip->show();
}
/************************************************************SimuTipThread************************************************************************/
void SimuTipThread::run()
{
	//QMutexLocker locker(&mutex);
	db_simutip = new QSqlDatabase;//dzy new modified from db_simutip to *db_simutip 0706
	if (ConnectHDB(*db_simutip,"simutip"))
		calc = new CTaskCalculation(m_task_id,m_send_task_id,*db_simutip); 
	else
		return;
	calc->updateTaskSubjectToMap();
	int step = 1;
	while(!stop_flag)
	{
		//mutex.lock();
		calc->curstep_timeout = false;
		calc->stop_flag = stop_flag;
		calc->judgeStepTimeout(step);
		int step_old;
		step_old = step;
		while(step_old == step&&!stop_flag)
		{
			if (step_old!= step)
			{
				break;
			}
			while(!calc->curstep_timeout&&!stop_flag)
			{		
				calc->updateTaskRecordToHash();
				if (calc->judgeStepFinished(step,1))
				{
					emit sigStepFinished(step,0);
					step++;
					calc->timer_overtime->stop();
					break;
				}
				MySleep(1000);
			}
			///DZY ADDED  FOR STEP TIME OUT 140723
			if (calc->curstep_timeout)
			{
				emit sigStepOvertime(step,1);
				step++;
				calc->curstep_timeout = false;
			}
		}		
		//mutex.unlock();
		if (step>m_step_num)
			break;
	}
// 	if (stop_flag)//dzy
// 	{
// 		CloseHDB(db_simutip);
// 		calc->~CTaskCalculation();
// 	}
}   
/***************************************  ***********************setSimuTip*********************************************************/
CSetSimuTip::CSetSimuTip(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);
	populateList();
	comboMode->addItem(QString::fromLocal8Bit("��ʾ��ǰ��ʾģʽ"),QVariant(TIP_MODE_SINGLE));
	comboMode->addItem(QString::fromLocal8Bit("��ʾ������ʾģʽ"),QVariant(TIP_MODE_MULTI));
	connect(buttonColor,SIGNAL(clicked()),this,SLOT(openSetColor()));
	connect(buttonBackgroundColor,SIGNAL(clicked()),this,SLOT(openSetBackgroundColor()));
	connect(buttonCurTipColor,SIGNAL(clicked()),this,SLOT(openSetCurTipColor()));
	connect(buttonFont,SIGNAL(clicked()),this,SLOT(openSetFont()));
	connect(sliderAlpha,SIGNAL(valueChanged(int)),spinAlpha,SLOT(setValue(int)));
	connect(spinAlpha,SIGNAL(valueChanged(int)),sliderAlpha,SLOT(setValue(int)));
	connect(spinAlpha,SIGNAL(valueChanged(int)),this,SLOT(changeOpacity(int)));
	connect(checkIsAutoSize,SIGNAL(stateChanged(int)),this,SLOT(setAutoSize(int)));
	connect(comboMode,SIGNAL(currentIndexChanged(int)),this,SLOT(setDialogMode(int)));
	connect(spinWidth,SIGNAL(valueChanged(int)),this,SLOT(setDialogSize(int)));
	connect(spinHeight,SIGNAL(valueChanged(int)),this,SLOT(setDialogSize(int)));
	connect(buttonOpenSimuTip,SIGNAL(toggled(bool)),this,SLOT(openSimuTip(bool)));
	connect(buttonEnter,SIGNAL(clicked()),this,SLOT(buttonEnterClicked()));
	connect(buttonApply,SIGNAL(clicked()),this,SLOT(buttonApplyClicked()));
}
void CSetSimuTip::loadChinese()
{
	QTranslator translator;
	translator.load("SimuTrainee_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetSimuTip::loadEnglish()
{
	QTranslator translator;
	translator.load("SimuTrainee_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void CSetSimuTip::showEvent(QShowEvent *event)
{
	if (flag_langueage == 0)
	{
		loadChinese();
	}
	else if (flag_langueage == 1)
	{
		loadEnglish();
	}
	buttonOpenSimuTip->setChecked(false);
	event->ignore();
}
void CSetSimuTip::closeEvent(QCloseEvent *event)
{
	openSimuTip(false);
	event->accept();
}
void CSetSimuTip::init()
{
	ReadSimuTipConfig();
	int index;
	comboColor->disconnect();
	comboCurTipColor->disconnect();
	comboBackgroundColor->disconnect();
	t_tipColor = tipColor;
	t_curTipColor = curTipColor;
	t_backgroundColor = backgroundColor;
	t_tipFont = tipFont;
	t_mode = mode;
	t_isAutoSize = isAutoSize;
	t_size = sizeW;
	t_alpha = alpha;
	sliderAlpha->setValue(t_alpha);
	comboMode->setCurrentIndex(comboMode->findData(QVariant(t_mode)));
	setFontShow();
	if (t_isAutoSize)
		checkIsAutoSize->setCheckState(Qt::Checked);
	else
		checkIsAutoSize->setCheckState(Qt::Unchecked);
	index=comboColor->findData(t_tipColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboColor->setCurrentIndex(index);
	}
	else
	{
		comboColor->setCurrentIndex(comboColor->count()-1);
	}
	index=comboBackgroundColor->findData(t_backgroundColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboBackgroundColor->setCurrentIndex(index);
	}
	else
	{
		comboBackgroundColor->setCurrentIndex(comboBackgroundColor->count()-1);
	}
	index=comboCurTipColor->findData(t_curTipColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboCurTipColor->setCurrentIndex(index);
	}
	else
	{
		comboCurTipColor->setCurrentIndex(comboCurTipColor->count()-1);
	}
	if (t_isAutoSize)
		checkIsAutoSize->setCheckState(Qt::Checked);
	else
		checkIsAutoSize->setCheckState(Qt::Unchecked);
	
	spinWidth->setValue(sizeW.width());
	spinHeight->setValue(sizeW.height());
	connect(comboColor,SIGNAL(currentIndexChanged(int)),this,SLOT(tipColorChanged(int)));
	connect(comboCurTipColor,SIGNAL(currentIndexChanged(int)),this,SLOT(curTipColorChanged(int)));
	connect(comboBackgroundColor,SIGNAL(currentIndexChanged(int)),this,SLOT(backgroundColorChanged(int)));
}
void CSetSimuTip::buttonApplyClicked()
{
	tipColor = t_tipColor;
	curTipColor = t_curTipColor;
	backgroundColor = t_backgroundColor;
	tipFont = t_tipFont;
	sizeW = t_size;
	isAutoSize = t_isAutoSize;
	alpha = t_alpha;
	if (mode != t_mode)
	{
		mode = t_mode;
		if (dlgSimuTipExample != NULL)
		{
			if (dlgSimuTipExample->getTaskId() == -1)
			{
				dlgSimuTipExample->close();
				dlgSimuTipExample->deleteLater();
				dlgSimuTipExample = NULL;
				dlgSimuTipExample = new CSimuTipDlg();
				dlgSimuTipExample->show();
			}
		}	
		if (dlgSimuTip != NULL)
		{
			int task_id = dlgSimuTip->getTaskId();
			int send_task_id = dlgSimuTip->getSendTaskId();
			dlgSimuTip->close();
			dlgSimuTip->deleteLater();
			dlgSimuTip = NULL;
			dlgSimuTip = new CSimuTipDlg(NULL,task_id,send_task_id);
			dlgSimuTip->show();
		}	
	}
	emit sigUpdateAttrib();
	WriteSimuTipConfig();
}
void CSetSimuTip::buttonEnterClicked()
{
	buttonApplyClicked();
	emit sig_taskaccepted();
	this->close();
}

void CSetSimuTip::populateList()
{
	QStringList colorNames = QColor::colorNames();
	for (int i = 0; i < colorNames.size(); ++i) 
	{
		QColor color(colorNames[i]);
		comboColor->insertItem(i, colorNames[i]);
		comboColor->setItemData(i, color, Qt::DecorationRole);
		comboBackgroundColor->insertItem(i, colorNames[i]);
		comboBackgroundColor->setItemData(i, color, Qt::DecorationRole);
		comboCurTipColor->insertItem(i, colorNames[i]);
		comboCurTipColor->setItemData(i, color, Qt::DecorationRole);
	}
	int num = comboColor->count();
	comboColor->insertItem(num,QString::fromLocal8Bit("�Զ���"));
	comboColor->setItemData(num,QColor("white"), Qt::DecorationRole);
	comboBackgroundColor->insertItem(num,QString::fromLocal8Bit("�Զ���"));
	comboBackgroundColor->setItemData(num,QColor("white"), Qt::DecorationRole);
	comboCurTipColor->insertItem(num,QString::fromLocal8Bit("�Զ���"));
	comboCurTipColor->setItemData(num,QColor("white"), Qt::DecorationRole);
}
void CSetSimuTip::tipColorChanged(int index)
{
	t_tipColor = qVariantValue<QColor>(comboColor->itemData(comboColor->currentIndex(), Qt::DecorationRole));
}
void CSetSimuTip::curTipColorChanged(int index)
{
	t_curTipColor = qVariantValue<QColor>(comboCurTipColor->itemData(comboCurTipColor->currentIndex(), Qt::DecorationRole));
}
void CSetSimuTip::backgroundColorChanged(int index)
{
	t_backgroundColor = qVariantValue<QColor>(comboBackgroundColor->itemData(comboBackgroundColor->currentIndex(), Qt::DecorationRole));
}
void CSetSimuTip::setText(const QString &text)
{
	
}
void CSetSimuTip::openSetColor()
{
	QPalette pat;
	QColor col = QColorDialog::getColor(t_tipColor, this,"",QColorDialog::ShowAlphaChannel);
	if (!col.isValid())
		return;
	t_tipColor = col;
	pat.setColor(QPalette::Button,t_tipColor);
	comboColor->setPalette(pat);
	comboColor->setAutoFillBackground(true);
	int index=comboColor->findData(t_tipColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboColor->setCurrentIndex(index);
	}
	else
	{
		comboColor->setItemData(comboColor->count()-1, t_tipColor, Qt::DecorationRole);
		comboColor->setCurrentIndex(comboColor->count()-1);
	}
}
void CSetSimuTip::openSetBackgroundColor()
{
	QPalette pat;
	QColor col = QColorDialog::getColor(t_backgroundColor, this,"",QColorDialog::ShowAlphaChannel);
	if (!col.isValid())
		return;
	t_backgroundColor = col;
	pat.setColor(QPalette::Button,t_backgroundColor);
	comboBackgroundColor->setPalette(pat);
	comboBackgroundColor->setAutoFillBackground(true);
	int index=comboBackgroundColor->findData(t_backgroundColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboBackgroundColor->setCurrentIndex(index);
	}
	else
	{
		comboBackgroundColor->setItemData(comboBackgroundColor->count()-1, t_backgroundColor, Qt::DecorationRole);
		comboBackgroundColor->setCurrentIndex(comboBackgroundColor->count()-1);
	}
}
void CSetSimuTip::openSetCurTipColor()
{
	QPalette pat;
	QColor col = QColorDialog::getColor(t_curTipColor, this,"",QColorDialog::ShowAlphaChannel);
	if (!col.isValid())
		return;
	t_curTipColor = col;
	pat.setColor(QPalette::Button,t_curTipColor);
	comboCurTipColor->setPalette(pat);
	comboCurTipColor->setAutoFillBackground(true);
	int index=comboCurTipColor->findData(t_curTipColor, int(Qt::DecorationRole));
	if(index != -1)
	{
		comboCurTipColor->setCurrentIndex(index);
	}
	else
	{
		comboCurTipColor->setItemData(comboCurTipColor->count()-1, t_curTipColor, Qt::DecorationRole);
		comboCurTipColor->setCurrentIndex(comboCurTipColor->count()-1);
	}
}
void CSetSimuTip::changeOpacity(int alpha)
{
	t_alpha = alpha;
}
void CSetSimuTip::openSetFont()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok,t_tipFont,this);
	if (!ok)
		return;
	t_tipFont = font;
	setFontShow();
}
void CSetSimuTip::setFontShow()
{
	editFont->setText(QString::fromLocal8Bit("���� AaZz"));
	editFont->setFont(t_tipFont);
}
void CSetSimuTip::setDialogMode(int index)
{
	t_mode = comboMode->itemData(index).toInt();
}
void CSetSimuTip::setDialogSize(int value)
{
	t_size.setWidth(spinWidth->value());
	t_size.setHeight(spinHeight->value());
}
void CSetSimuTip::setAutoSize(int state)
{
	t_isAutoSize = (bool)state;
	if (state)
	{
		spinWidth->setEnabled(false);
		spinHeight->setEnabled(false);
	}
	else
	{
		spinWidth->setEnabled(true);
		spinHeight->setEnabled(true);
	}
}
void CSetSimuTip::openSimuTip(bool checked)
{
	if (checked)
	{
		dlgSimuTipExample = new CSimuTipDlg();
		dlgSimuTipExample->show();
	}
	else
	{
		if (dlgSimuTipExample != NULL)
		{
			if (dlgSimuTipExample->getTaskId() == -1)
			{
				dlgSimuTipExample->close();
				dlgSimuTipExample->deleteLater();
				dlgSimuTipExample = NULL;
			}
		}	
	}
}
/************************************************************************************************************/
void WriteSimuTipConfig()
{
	QString myfile = SimuTraineeConfigPath;
	QSettings mySetting(myfile,QSettings::IniFormat);
	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
	mySetting.setValue("simutip/mode",QVariant(mode));
	mySetting.setValue("simutip/tipColor",QVariant(tipColor.name()));
	mySetting.setValue("simutip/curTipColor",QVariant(curTipColor.name()));
	mySetting.setValue("simutip/backgroundColor",QVariant(backgroundColor.name()));
	mySetting.setValue("simutip/tipFont",QVariant(tipFont.toString()));
	mySetting.setValue("simutip/alpha",QVariant(alpha));

	if (position.x()>200||position.x()<=10)
	{
		position.setX(100);
	}
	if (position.y()>200||position.y()<=10)
	{
		position.setY(100);
	}
	mySetting.setValue("simutip/position",QVariant(position));
	mySetting.setValue("simutip/isAutoSize",QVariant(isAutoSize));
	mySetting.setValue("simutip/size",QVariant(sizeW));
}
void ReadSimuTipConfig()
{
	QString myfile = SimuTraineeConfigPath;
	QSettings mySetting(myfile,QSettings::IniFormat);
	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
	mode = mySetting.value("simutip/mode").toInt();
	tipColor.setNamedColor(mySetting.value("simutip/tipColor").toString());
	curTipColor.setNamedColor(mySetting.value("simutip/curTipColor").toString());
	backgroundColor.setNamedColor(mySetting.value("simutip/backgroundColor").toString());
	tipFont.fromString(mySetting.value("simutip/tipFont").toString());
	alpha = mySetting.value("simutip/alpha").toInt();
	position = mySetting.value("simutip/position").toPoint();
	if (position.x()>200||position.x()<=10)
	{
		position.setX(100);
	}
	if (position.y()>200||position.y()<=10)
	{
		position.setY(100);
	}
	sizeW = mySetting.value("simutip/size").toSize();
	isAutoSize = mySetting.value("simutip/isAutoSize").toBool();
}