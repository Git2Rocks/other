#include "SimuTutor.h"
CTeacherManage::CTeacherManage(QWidget* parent)
			  :QMainWindow(parent)
{	  
	setupUi(this);
	frame = new QFrame(centralwidget);
	labelName = new QLabel(frame);
	labelLogo = new QLabel(frame);
	labelNameCo = new QLabel(frame);
	frame->resize(1000,650);
	frame->setObjectName(QString::fromUtf8("frame"));
	QVBoxLayout *layout = new QVBoxLayout;
	QVBoxLayout *layoutLogo = new QVBoxLayout(frame);
	layout->addWidget(frame);
	layout->setContentsMargins(0,0,0,0);
	centralwidget->setLayout(layout);
	layoutLogo->addWidget(labelLogo);
	layoutLogo->addWidget(labelName);
	layoutLogo->addWidget(labelNameCo);
	frame->setLayout(layoutLogo);
	writeConfig();
	readConfig();
	ifshowtip = true;
	lang_is_english = false;
	lang_is_chinese = true;
	actionChinese->setCheckable(true);
	actionEnglish->setCheckable(true);
	actionChinese->setChecked(true);
	actionEnglish->setChecked(false);
	buttonSendMsg = new QToolButton(this);
	labelLogoToolBar = new QLabel(this);
	actionHelp->setShortcut(tr("F1"));
	createiTrayIcon();
	loginUser = new CLogin(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),loginUser,SLOT(setLanguage( int )));
	sendmessagetable = new CSendMessageTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),sendmessagetable,SLOT(setLanguage( int )));
	toolBar->addWidget(buttonSendMsg);
	buttonSendMsg->resize(50,40);
	buttonSendMsg->setIcon(QIcon(QString::fromLocal8Bit(":/pic/images/20071224091514244[1].PNG")));
	QWidget* spacer = new QWidget(this);
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->addWidget(spacer);
	toolBar->addWidget(labelLogoToolBar);
	labelLogoToolBar->setStyleSheet(QString::fromUtf8("border-image: url(:pic/images/logo.png);"));
	labelLogoToolBar->setMinimumSize(150,55);
	labelLogoToolBar->setMaximumSize(150,55);
	actionTrainInfo->setVisible(false);//hide train_info menu by dm 2013.04.01
	//menu_language->menuAction()->setVisible(false);//���ز˵��е�QMenu
	actionLoginStatus->setText(QString::fromLocal8Bit("�û���δ��¼"));
// 	actionLoginStatus->setMinimumSize(200,55);
// 	actionLoginStatus->setMaximumSize(200,55);
	m_threadmsgbox = new QMessageBox;
	m_NetstateThreadTutor = new NetstateThreadTutor();
	m_NetstateThreadTutor->start();

	//set stylesheet
	QFile file(":/pic/qss/default.qss");
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
	this->setStyleSheet("");

	createBroadcast();

	connect(m_NetstateThreadTutor, SIGNAL(showtryconeectfail()),this, SLOT(show_tryconnectfail()));
	connect(m_NetstateThreadTutor, SIGNAL(showtryconeect(int,bool)),this, SLOT(show_tryconnec(int,bool)));

	connect(loginUser,SIGNAL(sigUserLogin(int,const QString &)),this,SLOT(userLogin(int,const QString &)));
	connect(actionChinese,SIGNAL(triggered()),this,SLOT(loadChinese()));
	connect(actionEnglish,SIGNAL(triggered()),this,SLOT(loadEnglish()));
	connect(actionLogin, SIGNAL(triggered()), this, SLOT(openLoginTable()));
	connect(actionLogin_menu, SIGNAL(triggered()), this, SLOT(openLoginTable()));
	connect(actionExit,SIGNAL(triggered()),this,SLOT(userLogout()));
	connect(actionExit_menu,SIGNAL(triggered()),this,SLOT(userLogout()));
	connect(actionQuit,SIGNAL(triggered()),this,SLOT(isQuit()));
	connect(iTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	connect(timerButtonChat, SIGNAL(timeout()), this, SLOT(blinkChatButton()));
	connect(sendmessagetable, SIGNAL(sigRecvMsg()), this, SLOT(recvMsg()));
	connect(actionAbout,SIGNAL(triggered()),this,SLOT(about()));
	connect(actionHelp,SIGNAL(triggered()),this,SLOT(help()));
	connect(actionStudentInfo_menu, SIGNAL(triggered()), this, SLOT(openStudentInfoTable()));
	connect(actionLoginRec,SIGNAL(triggered()),this,SLOT(openLoginRecTable()));
	connect(action_user_score,SIGNAL(triggered()),this,SLOT(openDlgScore()));
	connect(actionPrivilege,SIGNAL(triggered()),this,SLOT(openPrivilegeManager()));
	connect(actionSetTask,SIGNAL(triggered()),this,SLOT(openSetTaskTable()));
	connect(actionSetTask_menu,SIGNAL(triggered()),this,SLOT(openSetTaskTable()));
	connect(actionSetScene,SIGNAL(triggered()),this,SLOT(openSetSceneTable()));
	connect(actionSetFault,SIGNAL(triggered()),this,SLOT(openSetFaultTable()));
	connect(actionStudentInfo, SIGNAL(triggered()), this, SLOT(openLoginStudentTable()));
	connect(actionLoginStudent,SIGNAL(triggered()),this,SLOT(openLoginStudentTable()));
	connect(actionTrainInfo,SIGNAL(triggered()),this,SLOT(openTrainInfoTable()));
	connect(buttonSendMsg, SIGNAL(clicked()), this, SLOT(openSendMessageTable()));
	connect(actionSendMessage_menu, SIGNAL(triggered()), this, SLOT(openSendMessageTable()));
	connect(actionModel,SIGNAL(triggered()),this,SLOT(openModelForm()));
	connect(actionModel_menu,SIGNAL(triggered()),this,SLOT(openModelForm()));
	connect(actionSequence,SIGNAL(triggered()),this,SLOT(openSequence()));
	connect(actionFault, SIGNAL(triggered()), this, SLOT(openFaultTable()));
	connect(actionTask,SIGNAL(triggered()),this,SLOT(openTaskTable()));
	connect(actionScene,SIGNAL(triggered()),this,SLOT(openSceneTable()));
	connect(actionRevert,SIGNAL(triggered()),this,SLOT(openRevertTable()));
	connect(actionOprManage,SIGNAL(triggered()),this,SLOT(openLocalOpr()));
	connect(actionOprManage_menu,SIGNAL(triggered()),this,SLOT(openLocalOpr()));
	connect(actionHistoryRec,SIGNAL(triggered()),this,SLOT(openHistoryRecTable()));
	connect(actionHistoryRec_menu,SIGNAL(triggered()),this,SLOT(openHistoryRecTable()));
	connect(actionExam,SIGNAL(triggered()),this,SLOT(openExamTable()));
	connect(actionStationConfig_menu, SIGNAL(triggered()), this, SLOT(openStationConfigTable()));
	connect(actionStationConfig, SIGNAL(triggered()), this, SLOT(openStationConfigTable()));
	connect(actionALL_reset,SIGNAL(triggered()),this,SLOT(onactionALL_reset()));
	connect(actionSaveScene,SIGNAL(triggered()),this,SLOT(openSaveSceneTable()));
	connect(actionCallData,SIGNAL(triggered()),this,SLOT(openCallDataTable()));
	connect(actionSetPointMask,SIGNAL(triggered()),this,SLOT(openSetPointMaskTable()));
	//dzy
	connect(action_doc_manage,SIGNAL(triggered()),this,SLOT(openDoc_manage()));
	connect(action_doc_study_plan,SIGNAL(triggered()),this,SLOT(open_study_plan()));
	connect(action_contestmanage,SIGNAL(triggered()),this,SLOT(openContest_manage()));
	connect(action_sendcontest,SIGNAL(triggered()),this,SLOT(openSetContest()));
	connect(actionStudyRec,SIGNAL(triggered()),this,SLOT(openStudyRecTable()));
	connect(actionBrodcast,SIGNAL(triggered()),this,SLOT(showsendBroadcast()));	
}
CTeacherManage::~CTeacherManage()
{
	userLogout();
	CloseHDB(db_conn);
}
void CTeacherManage::loadChinese()
{
	flag_langueage = 0;//0:���� 1��english
	actionChinese->setCheckable(true);
	actionChinese->setChecked(true);
	actionEnglish->setChecked(false);
	QTranslator translator;
	translator.load("SimuTutor_zh_CN");
	qApp->installTranslator(&translator);
	lang_is_chinese=true;
	lang_is_english=false;
	retranslateUi(this);
	this->show();
	emit sigLanguageChanged(flag_langueage);
// 	loginUser->loadChinese();
// 	faulttable->loadChinese();
// 	stationconfigtable->loadChinese();
// 	sendmessagetable->loadChinese();
// 	studentinfotable->loadChinese();
// 	scenetable->loadChinese();
// 	tasktable->loadChinese();
// 	loginstudenttable->loadChinese();
// 	reverttable->loadChinese();
// 	modelform->loadChinese();
// 	historyrectable->loadChinese();
// 	settasktable->loadChinese();
// 	pSequence->loadChinese();
// 	loginrec->loadChinese();
// 	traininfo->loadChinese();
// 	m_doc_manage->loadChinese();
// 	m_study_plan->loadChinese();
}

void CTeacherManage::loadEnglish()
{
	flag_langueage = 1;
	actionEnglish->setCheckable(true);
	actionEnglish->setChecked(true);
	actionChinese->setChecked(false);
	QTranslator translator;
	translator.load("SimuTutor_en");
	qApp->installTranslator(&translator);
	lang_is_english=true;
	lang_is_chinese=false;
	retranslateUi(this);
	this->show();
	emit sigLanguageChanged(flag_langueage);
// 	loginUser->loadEnglish();
// 	faulttable->loadEnglish();
// 	stationconfigtable->loadEnglish();
// 	sendmessagetable->loadEnglish();
// 	studentinfotable->loadEnglish();
// 	scenetable->loadEnglish();
// 	tasktable->loadEnglish();
// 	loginstudenttable->loadEnglish();
// 	reverttable->loadEnglish();
// 	modelform->loadEnglish();
// 	historyrectable->loadEnglish();
// 	settasktable->loadEnglish();
// 	pSequence->loadEnglish();
// 	loginrec->loadEnglish();
// 	traininfo->loadEnglish();
// 	m_doc_manage->loadEnglish();
// 	m_study_plan->loadEnglish();
}
void CTeacherManage::readConfig()
{
	QString myfile = SimuTutorConfigPath;
	char verTmp[20];
	QSettings mySetting(myfile,QSettings::IniFormat);
	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
	strcpy(tch_bg_pic,mySetting.value("background/bgpic").toString().toLocal8Bit().data());
	QPoint pos = mySetting.value("window/pos",QVariant(QPoint(200,200))).toPoint();
	QSize size = mySetting.value("window/size",QVariant(QSize(1000,720))).toSize();
	this->resize(size);
	this->move(pos);
}
void CTeacherManage::writeConfig()
{
	QString myfile = SimuTutorConfigPath;
	QSettings mySetting(myfile,QSettings::IniFormat);
	mySetting.setIniCodec(QTextCodec::codecForName("GB2312"));
	mySetting.setValue("window/pos",QVariant(this->pos()));
	mySetting.setValue("window/size",QVariant(this->size()));
}
void CTeacherManage::bgPic()
{
	QImage image1;
	QPixmap logo1(QString::fromLocal8Bit(":/pic/images/logo.png"));
	QPixmap logo2 = logo1.scaled(150,150);
	QPalette   palette,p_labelName,p_labelNameCo;
	QFont f_labelName(QString::fromLocal8Bit("����"), 70, QFont::Bold);
	QFont f_labelNameCo(QString::fromLocal8Bit("����"), 40, QFont::Bold);
//	f_labelName.setPointSize(fontsize);
	QDir dir;
	dir.setPath(QString::fromLocal8Bit("/home/ems/h9000/ots/images"));
	if (!dir.exists())
		dir.setPath(QString::fromLocal8Bit("/home/ems/h9000/bin/images"));
	image1.load(dir.absoluteFilePath("background.jpg"));
/*
	labelLogo->setAlignment(Qt::AlignLeft | Qt::AlignTop);  
	labelName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  
	labelNameCo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); 
	p_labelName.setColor(QPalette::WindowText,Qt::blue);
	p_labelNameCo.setColor(QPalette::WindowText,Qt::blue);
	labelLogo->setPixmap(logo2);
	labelName->setText(QString::fromLocal8Bit("SimuTutor"));
	labelName->setPalette(p_labelName);
	labelName->setFont(f_labelName);
	labelNameCo->setText(QString::fromLocal8Bit("������ˮ��ˮ��Ƽ��������޹�˾"));
	labelNameCo->setPalette(p_labelNameCo);
	labelNameCo->setFont(f_labelNameCo);
*/
	QImage image2 = image1.scaled(frame->frameSize());
	palette.setBrush(frame->backgroundRole(),QBrush(image2));
	frame->setPalette(palette);
	frame->setAutoFillBackground(true);
	frame->show();
}
void CTeacherManage::resizeEvent ( QResizeEvent *event )
{
	event->ignore();
	writeConfig();
	bgPic();
}
void CTeacherManage::moveEvent( QMoveEvent *event)
{
	event->ignore();
	writeConfig();
}
void CTeacherManage::createActions() 
{ //�����ϵ� 
	minimizeAction = new QAction(QString::fromLocal8Bit("��С�� (&I)"), this); 
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide())); 
	maximizeAction = new QAction(QString::fromLocal8Bit("��� (&X)"), this); 
	connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized())); 
	restoreAction = new QAction(QString::fromLocal8Bit("��ԭ (&R)"), this); 
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal())); 
	quitAction = new QAction(QString::fromLocal8Bit("�˳� (&Q)"), this); 
	quitAction->setShortcut(QString::fromLocal8Bit("CTRL+Q"));
	connect(quitAction, SIGNAL(triggered()), this, SLOT(isQuit())); 
} 
void CTeacherManage::createiTrayIcon()
{
	iTrayIcon=new QSystemTrayIcon(this);	
	iTrayIcon->setIcon(QIcon(":/pic/main.ico"));	
	iTrayIcon->setToolTip(QString::fromLocal8Bit("OTS2000��Ավ"));
	createActions(); 
	createTrayIcon(); 
	iTrayIcon->show();
}
void CTeacherManage::createTrayIcon() 
{
	trayIconMenu = new QMenu(this); 
	trayIconMenu->addAction(minimizeAction); 
	trayIconMenu->addAction(maximizeAction); 
	trayIconMenu->addAction(restoreAction); 
	trayIconMenu->addSeparator(); 
	trayIconMenu->addAction(quitAction); 
	iTrayIcon->setContextMenu(trayIconMenu); 
}//����
void CTeacherManage::iconActivated(QSystemTrayIcon::ActivationReason reason) 
{ 	
	//������굥��˫���¼�
	switch (reason) 
	{ 
	/*case QSystemTrayIcon::Trigger: 	
		if(isHidden()){
			this->showNormal();
			this->focusWidget();}
		break; */
	case QSystemTrayIcon::DoubleClick: 
		this->showNormal();
		this->activateWindow();
		this->focusWidget();
		break;
	default:
		break; 
	} 
} 
void CTeacherManage::closeEvent(QCloseEvent *event)//�رմ�����С��
{
	event->ignore();
	closeTable = new QDialog(this);
	closeTable->setAttribute(Qt::WA_DeleteOnClose);
	chk = new QCheckBox(closeTable);
	chkMin = new QRadioButton(closeTable);
	chkClose = new QRadioButton(closeTable);
	lbl = new QLabel(closeTable);
	butEnter = new QPushButton(closeTable);
	butExit = new QPushButton(closeTable);
	closeTable->setWindowTitle(QString::fromLocal8Bit("�ر���ʾ"));
	QGridLayout *lay = new QGridLayout(closeTable);
	lay->setSizeConstraint(QLayout::SetFixedSize);
	chk->setText(tr("��������"));
	lbl->setText(tr("������˹رհ�ť�������룺"));
	chkMin->setText(tr("��С����ϵͳ�����������˳�����"));
	chkClose->setText(tr("�˳�����"));
	butEnter->setText(tr("ȷ��"));
	butExit->setText(tr("ȡ��"));
	lay->setRowMinimumHeight(3,50);
	lay->setRowMinimumHeight(4,0);
	lay->addWidget(lbl,0,0,Qt::AlignCenter);
	lay->addWidget(chkMin,1,0,1,2);
	lay->addWidget(chkClose,2,0,1,2);
	lay->addWidget(chk,3,0);
	lay->addWidget(butEnter,3,1);
	lay->addWidget(butExit,3,2);
	closeTable->setLayout(lay);	 
	closeTable->setModal(true);
	chkMin->setChecked(TRUE);
	connect(butEnter,SIGNAL(clicked()),this,SLOT(checkQuit()));
	connect(butExit,SIGNAL(clicked()),closeTable,SLOT(reject()));
	connect(chk,SIGNAL(stateChanged(int)),this,SLOT(oncheckbox(int)));
	if (ifshowtip) 
	{
		closeTable->exec();
	}
	else
		this->hide();
}
void CTeacherManage::checkQuit()
{
	if (chkMin->isChecked())
	{
		closeTable->hide();
		this->hide();
	} 
	else if(chkClose->isChecked())
	{
		qApp->quit();
	}
}
void CTeacherManage::oncheckbox(int state)
{
	ifshowtip=state;
}
void CTeacherManage::isQuit()
{
	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle (tr("��ʾ"));
	msgBox.setInformativeText(tr("ȷ��Ҫ�˳�OTS2000��Ավ��"));
	msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Cancel);
	//QPushButton psbOk=addButton();
	QPalette pal = msgBox.palette();
	pal.setColor( QPalette::Active, QPalette::Window, QColor(85, 85, 127,255) );
	pal.setColor( QPalette::Inactive, QPalette::Window, Qt::yellow );
	pal.setColor( QPalette::Disabled, QPalette::Window, Qt::green );
	pal.setColor( QPalette::Active, QPalette::Button, Qt::lightGray );
	pal.setColor( QPalette::Inactive, QPalette::Button, Qt::yellow );
	pal.setColor( QPalette::Disabled, QPalette::Button, Qt::green );
	//	msgBox.setPalette( pal );
	int ret = msgBox.exec();
	if (ret == QMessageBox::Ok ) 
	{
		qApp->quit();
	}
	else 
		this->show();
}
void CTeacherManage::about()
{
	QMessageBox::about(this, tr("���� OTS2000"),
		tr("<p>The <b>OTS2000</b> simulation station " \
		"helps to train workers at hydro-plant to learn how to " \
		"use the complicated H9000 system effiently..\n"\
		"  Copyright by BITC.</p>"));
}
void CTeacherManage::help()
{
	QString filePath = QString::fromLocal8Bit("/home/ems/h9000/ots/help/help.doc");
	QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(filePath).absoluteFilePath())); 
}
 /*************************************** �������ڵĲۺ���***********************************************/
void CTeacherManage::openLoginTable()
{
	if (!loginUser->login_status)
	{

		loginUser->init();
		loginUser->show();
	}
}
void CTeacherManage::openFaultTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_FAULT))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	faulttable = new CFaultTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),faulttable,SLOT(setLanguage( int )));
	faulttable->displayFault();
	faulttable->showMaximized();
	faulttable->listFault->resizeColumnsToContents();
}
void CTeacherManage::openStationConfigTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_HOST))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	stationconfigtable = new CStationConfigTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),stationconfigtable,SLOT(setLanguage( int )));
	stationconfigtable->displayStation();
	stationconfigtable->show();
}
void CTeacherManage::openSendMessageTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SEND_MESSAGE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	sendmessagetable->show();
	buttonSendMsg->setStyleSheet("");
}
void CTeacherManage::openStudentInfoTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_USER_INFO))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	studentinfotable = new CStudentInfoTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),studentinfotable,SLOT(setLanguage( int )));
	studentinfotable->showMaximized();
}
void CTeacherManage::openSceneTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SCENE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	scenetable = new CSceneTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),scenetable,SLOT(setLanguage( int )));
	scenetable->listScene->resizeColumnsToContents();
	scenetable->displayScene();
	scenetable->showMaximized();

}
void CTeacherManage::openTaskTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_TASK))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	tasktable = new CTaskTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),tasktable,SLOT(setLanguage( int )));
	tasktable->listTask->resizeColumnsToContents();
	tasktable->displayTask();
	tasktable->showMaximized();

}
void CTeacherManage::openLoginStudentTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_LOGIN_USER))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	loginstudenttable = new CLoginStudentTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),loginstudenttable,SLOT(setLanguage( int )));
	UpdateTrainInfoModel();
	loginstudenttable->showMaximized();
}
void CTeacherManage::openRevertTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_REVERT))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	reverttable = new CRevertTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),reverttable,SLOT(setLanguage( int )));
	reverttable->displayRevert();
	reverttable->show();
}
void CTeacherManage::openModelForm()	//yyp
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_MODEL))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	modelform = new CModelForm;
	connect(this,SIGNAL(sigLanguageChanged( int )),modelform,SLOT(setLanguage( int )));
	modelform->displayModel();
	modelform->showMaximized();
}

void CTeacherManage::openHistoryRecTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_RECORD))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	historyrectable = new CHistoryRecTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),historyrectable,SLOT(setLanguage( int )));
	//historyrectable->setUserId(loginUser->login_user_id);
	historyrectable->showMaximized();
}
void CTeacherManage::openStudyRecTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_RECORD))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	m_CStudyRecTable = new CStudyRecTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),m_CStudyRecTable,SLOT(setLanguage( int )));
	//historyrectable->setUserId(loginUser->login_user_id);
	m_CStudyRecTable->showMaximized();
}
void CTeacherManage::openSetTaskTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SET_TASK))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	settasktable = new CSetTaskTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),settasktable,SLOT(setLanguage( int )));
	settasktable->setWindowFlags(Qt::WindowStaysOnTopHint);
	settasktable->listTask->setResizeMode(QListView::Adjust);
	settasktable->listScene->setResizeMode(QListView::Adjust);
	settasktable->listFault->setResizeMode(QListView::Adjust);
//	settasktable->setModal(true);
	settasktable->showMaximized();
}
void CTeacherManage::openSetSceneTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SET_SCENE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	setscenetable = new CSetSceneFaultTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),setscenetable,SLOT(setLanguage( int )));
	setscenetable->initScene();
	setscenetable->setWindowFlags(Qt::WindowStaysOnTopHint);
	setscenetable->showMaximized();
	setscenetable->setSceneModel();
}
void CTeacherManage::openSetFaultTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SET_FAULT))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	setfaulttable = new CSetSceneFaultTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),setfaulttable,SLOT(setLanguage( int )));
	setfaulttable->initFault();
	setfaulttable->setWindowFlags(Qt::WindowStaysOnTopHint);
	setfaulttable->showMaximized();
	setfaulttable->setFaultModel();
}
void CTeacherManage::openLocalOpr()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_LOCAL_OPR))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	localopr = new CLocalOprTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),localopr,SLOT(setLanguage( int )));
	localopr->show();
}
void CTeacherManage::openSequence()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SEQUENCE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	pSequence = new SequenceList(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),pSequence,SLOT(setLanguage( int )));
	pSequence->show();
}
void CTeacherManage::openLoginRecTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_LOGIN_REC))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	loginrec = new CLoginRecTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),loginrec,SLOT(setLanguage( int )));
	loginrec->show();
}
void CTeacherManage::openTrainInfoTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	traininfo = new CTrainInfoTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),traininfo,SLOT(setLanguage( int )));
	traininfo->show();
}
void CTeacherManage::openPrivilegeManager()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_PRIV_MANAGER))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	privmgr = new CPrivilegeMananger(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),privmgr,SLOT(setLanguage( int )));
	privmgr->show();
}
void CTeacherManage::openSaveSceneTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SAVE_SCENE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	savescenetable = new CSaveSceneTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),savescenetable,SLOT(setLanguage( int )));
	savescenetable->show();
}
void CTeacherManage::openDlgScore()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SCORE))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	scorerec = new CScoreRec;
	connect(this,SIGNAL(sigLanguageChanged( int )),scorerec,SLOT(setLanguage( int )));
	scorerec->showMaximized();
}
void CTeacherManage::openSetPointMaskTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SET_POINT_MASK))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	setpointmasktable = new CSetPointMaskTable(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),setpointmasktable,SLOT(setLanguage( int )));
	setpointmasktable->show();
}
void CTeacherManage::onactionALL_reset()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_SCENE_RESET))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	pSceneReset = new SceneReset(this);
	connect(this,SIGNAL(sigLanguageChanged( int )),pSceneReset,SLOT(setLanguage( int )));
	pSceneReset->show();
}
void CTeacherManage::openExamTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_EXAM))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	QString program = QString::fromLocal8Bit("/home/ems/h9000/bin/exam/examination_total_form.exe");
	QStringList arguments;
	arguments.append(QString::fromLocal8Bit("otsargs"));
	arguments.append(loginUser->login_user_name);
	arguments.append(loginUser->login_user_password);
	QProcess *processExam = new QProcess(this);
	processExam->start(program,arguments);
}
 /*************************************** �������ڵĲۺ���***********************************************/
void CTeacherManage::userLogin(int user_id,const QString &login_name)
{
	actionLoginStatus->setText(tr("��ǰ��¼�û���")+QString::fromLocal8Bit("%1").arg(login_name));
	sendmessagetable->setUserId(user_id);
}
void CTeacherManage::userLogout()
{
	if (loginUser->login_status)
	{
// 		QMessageBox msgBox;
// 		msgBox.setIcon(QMessageBox::Information);
// 		msgBox.setWindowTitle (QString::fromLocal8Bit("��ʾ"));
// 		msgBox.setInformativeText(QString::fromLocal8Bit("ȷ��Ҫ�˳���ǰ�û���½��"));
// 		msgBox.setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
// 		msgBox.setDefaultButton(QMessageBox::Cancel);
// 		if (msgBox.exec() != QMessageBox::Ok ) 
// 			return;
		DB_FMT data;
		InitDbData(&data,TABLE_LOGIN_INFO);
		data.flag.flag_login_info.logout_time=TRUE;
		GetCurTimeStr(data.seg.seg_login_info.logout_time);
		
		data.cond_flag.flag_login_info.user_id=TRUE;
		data.cond_flag.flag_login_info.login_time=TRUE;
		data.cond_seg.seg_login_info.user_id = loginUser->login_user_id;
		strcpy(data.cond_seg.seg_login_info.login_time,loginUser->login_time.toLocal8Bit().data());
		if( UpdateOneRec(&data) != TRUE)
		{
			//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("�޸�����ʧ��!"),QMessageBox::Ok);		
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}
		actionLoginStatus->setText(tr("�û���δ��¼"));
		loginUser->init();
		//��Ա�û�ע�����޸�train_info�� remove by dm 2012.6.20
		/*InitDbData(&data,TABLE_TRAIN_INFO);
		data.flag.flag_train_info.login_status=TRUE;	
		data.seg.seg_train_info.login_status=0;
		data.flag.flag_train_info.status = TRUE;
		data.seg.seg_train_info.status=0;
		data.flag.flag_train_info.task_status = TRUE;
		data.seg.seg_train_info.task_status=0;
		data.flag.flag_train_info.scene_status = TRUE;
		data.seg.seg_train_info.scene_status=0;
		data.flag.flag_train_info.fault_status = TRUE;
		data.seg.seg_train_info.fault_status=0;
		data.flag.flag_train_info.fault_id =TRUE;
		data.seg.seg_train_info.fault_id = CONST_NEG;	
		data.flag.flag_train_info.scene_id = TRUE;
		data.seg.seg_train_info.scene_id = CONST_NEG;	
		data.flag.flag_train_info.send_task_id = TRUE;
		data.seg.seg_train_info.send_task_id = CONST_NEG;	
		data.flag.flag_train_info.task_id = TRUE;
		data.seg.seg_train_info.task_id = CONST_NEG;	
		data.flag.flag_train_info.user_id = TRUE;
		data.seg.seg_train_info.user_id = CONST_NEG;
		data.cond_flag.flag_train_info.host_id =TRUE;
		data.cond_seg.seg_train_info.host_id = g_host_id;
		if (UpdateOneRec(&data) != TRUE)
		{
			//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("�޸����ݿ�ʧ��!"),QMessageBox::Ok);
			HdbLogWrite(data.sql_str,data.sql_error);
			return;
		}*/
		//logintable->heartBeatThread->terminate();    //��ֹ�߳�  
		//logintable->heartBeatThread->wait();    //�����ȴ�
		//logintable->heartBeatThread->exit();
		//delete logintable->heartBeatThread;
	}
}

void CTeacherManage::initStnView()
{
	GULONG	stn_num,grp_num;
	UCHAR	stn_id,dev_id;
	char	stn_comment[STATION_COMMENT_SIZE];
	char	dev_comment[GROUP_COMMENT_SIZE];
	char	text[128];
	LCUID	lcuno;
	QVariant varStn,varLcuno;
	stndevTable = new QDialog(this);
	stndevTable->setAttribute(Qt::WA_DeleteOnClose);
	stndevTable->setModal(true);
	buttonEnter = new QPushButton(stndevTable);
	buttonExit = new QPushButton(stndevTable);
	stnView = new QTreeWidget(stndevTable);
	stnView->setSortingEnabled(false); //���Զ�����
	stnView->setDragEnabled(false); //�����Ϸ�
	stnView->setAutoScroll(true); //���Ծ�
	stnView->setColumnCount(1); //����
	stnView->header()->setHidden(1); //������ϵı�ͷ
	stnView->setRootIsDecorated(true); //�ø���Ŀǰ��Ҳ����״���� 
	//callDataTable->setWindowTitle(QString::fromLocal8Bit("��������ٻ�"));
	QGridLayout *layout = new QGridLayout(stndevTable);
	//layout->setSizeConstraint(QLayout::SetFixedSize);
	buttonEnter->setText(tr("ȷ��"));
	buttonExit->setText(tr("ȡ��"));
	layout->addWidget(stnView, 0, 0, 1, 2);
	layout->addWidget(buttonEnter, 1, 0, 1, 1);
	layout->addWidget(buttonExit, 1, 1, 1, 1);
	stndevTable->resize(250, 400);
	stndevTable->setLayout(layout);	
	connect(buttonExit,SIGNAL(clicked()), stndevTable, SLOT(close()));
	connect(stnView,SIGNAL(itemChanged( QTreeWidgetItem *, int)),this,SLOT(treeItemChanged(QTreeWidgetItem *,int)));
	GetStationNum(&stn_num);
	for(int i=1; i<=stn_num; i++) 
	{  		
		GetStnIdByIndex(i, &stn_id);

		if( GetStnCommentById(stn_id,(char*)( stn_comment))==-1 )
			continue;

		sprintf(text, "%d. %s", stn_id, stn_comment);
		QTreeWidgetItem *itemStn = new QTreeWidgetItem(stnView, QStringList(QString::fromLocal8Bit(text)));
		varStn.setValue(stn_id);
		itemStn->setData(1,0,varStn);
		itemStn->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		itemStn->setCheckState (0, Qt::Unchecked);
		if(-1==GetGroupNumById(stn_id, &grp_num))
			continue;

		for(dev_id=1; dev_id<=grp_num; dev_id++) 
		{  
			if(-1==GetGroupCommentById(stn_id, dev_id, dev_comment))
				continue;

			sprintf(text, "%d. %s", dev_id, dev_comment);
			QTreeWidgetItem *itemDev = new QTreeWidgetItem(itemStn, QStringList(QString::fromLocal8Bit(text)));
			lcuno.stnid = stn_id;
			lcuno.devid = dev_id;
			varLcuno.setValue(lcuno);
			itemDev->setData(1,0,varLcuno);
			itemDev->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			itemDev->setCheckState (0, Qt::Unchecked);
		}
	}
}

void CTeacherManage::openCallDataTable()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	if (!CheckUserPrivilege(loginUser->login_user_id,TeacherPrivType::PRIV_CALL_DATA))
	{
		PopupMessageBox(this,"�Բ�����û�д˲���Ȩ�ޣ�����ϵ����Ա��",QMessageBox::Warning);
		return;
	}
	initStnView();
	stndevTable->setWindowTitle(tr("��������ٻ�"));
	connect(this,SIGNAL(sigLanguageChanged( int )),stndevTable,SLOT(setLanguage( int )));
	buttonEnter->setText(tr("�ٻ�"));
	buttonEnter->disconnect();
	connect(buttonEnter,SIGNAL(clicked()), this, SLOT(callData()));
	stndevTable->show();
}

void CTeacherManage::treeItemChanged(QTreeWidgetItem *item, int column)
{ 
	if(Qt::Checked == item->checkState(0))
	{  
		int count = item->childCount();     
		if (count > 0)
		{         
			for (int i = 0; i < count; i++)
			{
				item->child(i)->setCheckState(0, Qt::Checked);         
			}     
		}
		else
		{
			updateParentItem(item);
		}
	}
	else if(Qt::Unchecked == item->checkState(0))
	{   
		int count = item->childCount();
		if (count > 0)
		{         
			for (int i = 0; i < count; i++)
			{        
				item->child(i)->setCheckState(0, Qt::Unchecked);
			}     
		}
		else
		{
			updateParentItem(item);
		}
	}
}
void CTeacherManage::updateParentItem(QTreeWidgetItem* item)
{    
	QTreeWidgetItem *parent = item->parent();     
	if (parent == NULL)
	{        
		return;     
	}     //ѡ�е��ӽڵ����     
	int selectedCount = 0;     
	int childCount = parent->childCount();     
	for (int i = 0; i < childCount; i++)
	{         
		QTreeWidgetItem *childItem = parent->child(i);         
		if (childItem->checkState(0) == Qt::Checked)
		{             
			selectedCount++;         
		}     
	}     
	if (selectedCount <= 0)
	{     //δѡ��״̬         
		parent->setCheckState(0, Qt::Unchecked);     
	}
	else if(selectedCount > 0 && selectedCount < childCount)
	{     //����ѡ��״̬         
		parent->setCheckState(0, Qt::PartiallyChecked);     
	}
	else if(selectedCount == childCount)
	{     //ѡ��״̬     
		parent->setCheckState(0, Qt::Checked); 
	}//    
}

void CTeacherManage::callData()
{
	int		stn_num,dev_num;
	LCUID	lcuno;
	QVariant varStn,varLcuno;
	stn_num = stnView->topLevelItemCount();
	for(int i=0;i<stn_num;i++)
	{
		dev_num = stnView->topLevelItem(i)->childCount();
		for (int j=0;j<dev_num;j++)
		{
			if(stnView->topLevelItem(i)->child(j)->checkState(0) == Qt::Checked)
			{
				varLcuno = stnView->topLevelItem(i)->child(j)->data(1,0);
				lcuno = varLcuno.value<LCUID>();
				BdPollingCmd(lcuno.stnid,lcuno.devid);
			}
		}
	}
	stndevTable->close();
	PopupMessageBox(this,"�ٻ��������!",QMessageBox::Information);
}

void CTeacherManage::saveScene()
{
	DB_FMT data;
	int		stn_num,dev_num;
	UCHAR	stn_id;
	LCUID	lcuno;
	int		num=0;
	QString	stn_name;
	QVariant varStn,varLcuno;
	stn_num = stnView->topLevelItemCount();
	for(int i=0;i<stn_num;i++)
	{
		varStn = stnView->topLevelItem(i)->data(1,0);
		stn_id = varStn.value<UCHAR>();
		if(stnView->topLevelItem(i)->checkState(0) == Qt::Checked || 
		   stnView->topLevelItem(i)->checkState(0) == Qt::PartiallyChecked)
		{
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
			stn_name = stnView->topLevelItem(i)->text(0);
			stn_name = stn_name.section(' ', -1);
			stn_name.append(tr("����"));
			data.seg.seg_scene.scene_id = GetInexistenceIdInHdb(TABLE_SCENE);
			data.seg.seg_scene.src = 2;
			data.seg.seg_scene.user_id = loginUser->login_user_id;
			GetCurTimeStr(data.seg.seg_scene.datetime);	
			strcpy(data.seg.seg_scene.remark,"");
			strcpy(data.seg.seg_scene.filename,"");
			strcpy(data.seg.seg_scene.name,stn_name.toLocal8Bit().data());
			data.seg.seg_scene.station_id = stn_id;
			data.seg.seg_scene.dev_id = 0;
			//���ýӿں���������ΪDB_FMT�ṹ��
			if( InsertOneRec(&data) != TRUE)
			{
				//QMessageBox().critical(this,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("��������ʧ��!"),QMessageBox::Ok);		
				HdbLogWrite(data.sql_str,data.sql_error);
				continue;
			}
		}
		dev_num = stnView->topLevelItem(i)->childCount();
		for (int j=0;j<dev_num;j++)
		{
			if(stnView->topLevelItem(i)->child(j)->checkState(0) == Qt::Checked)
			{
				varLcuno = stnView->topLevelItem(i)->child(j)->data(1,0);
				lcuno = varLcuno.value<LCUID>();
				//saveSceneThread[num++] = new SaveSceneThread(lcuno.stnid,lcuno.devid,scene_id,this);
				//saveSceneRunnable[num++] = new SaveSceneRunnable(lcuno.stnid,lcuno.devid,scene_id);
			}
		}
		for (int k=0;k<num;k++)
		{
			//saveSceneThread[k]->start();
			//QThreadPool::globalInstance()->start(saveSceneRunnable[k]);
		}
	}
	stndevTable->close();
}
void CTeacherManage::recvMsg()
{
	flagSendMsg = false;
	if (sendmessagetable->isHidden())
		timerButtonChat->start(1000);
}
void CTeacherManage::blinkChatButton()
{
	if (!flagSendMsg)
	{
		buttonSendMsg->setStyleSheet(QString::fromUtf8("background-color: rgb(199,100,100);"));
		flagSendMsg = true;
	}
	else
	{
		buttonSendMsg->setStyleSheet("");
		flagSendMsg = false;
	}
}
void CTeacherManage::openDoc_manage()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	m_doc_manage = new Doc_manage;
	connect(this,SIGNAL(sigLanguageChanged( int )),m_doc_manage,SLOT(setLanguage( int )));
	m_doc_manage->show();
}

void CTeacherManage::open_study_plan()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	m_study_plan = new Study_plan;
	connect(this,SIGNAL(sigLanguageChanged( int )),m_study_plan,SLOT(setLanguage( int )));
	m_study_plan->show();
}
void CTeacherManage::show_tryconnectfail()
{
	m_threadmsgbox->setIcon(QMessageBox::Information);
	m_threadmsgbox->setWindowTitle (tr("��ʾ"));
	m_threadmsgbox->setInformativeText(tr("��γ�������ʧ�ܣ������˳������鱾����������֮���������ӡ�"));	
	m_threadmsgbox->setStandardButtons(QMessageBox::Ok |QMessageBox::Cancel);
	int ret =m_threadmsgbox->exec();
	if (ret == QMessageBox::Ok )
	{	
// 		cleanUserInfo();
// 		shm_ots_addr->data_task.task_status = 1;
		qApp->quit();
	}
	else
	{
		m_NetstateThreadTutor->cout_connected = 0;
		return;
	}
}
void CTeacherManage::show_tryconnec(int i,bool connectedOK)
{
	m_threadmsgbox->setIcon(QMessageBox::Information);
	m_threadmsgbox->setWindowTitle (tr("��ʾ"));
	if (!connectedOK)
	{
		m_threadmsgbox->setInformativeText(tr("���ӷ�����ʧ�ܣ����ڳ��Ե�")+QString::number(i)+tr("������"));
	}
	else
	{
		m_threadmsgbox->setInformativeText(tr("����������ʷ�������ɹ�"));
		m_NetstateThreadTutor->cout_connected = 0;
	}
	m_threadmsgbox->setStandardButtons(QMessageBox::Ok );
	m_threadmsgbox->exec();
}
void CTeacherManage::openContest_manage()
{
	if (!loginUser->login_status)
	{
		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
		return;
	}
	d_contest = new CContestTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),d_contest,SLOT(setLanguage( int )));
	d_contest->show();
}
void CTeacherManage::openSetContest()
{	
// 	if (!loginUser->login_status)
// 	{
// 		PopupMessageBox(this,"�û�δ��¼�����ȵ�¼ϵͳ",QMessageBox::Information);
// 		return;
// 	}
	d_setcontest = new CSetContestTable;
	connect(this,SIGNAL(sigLanguageChanged( int )),d_setcontest,SLOT(setLanguage( int )));
	d_setcontest->show();
}
void CTeacherManage::createBroadcast()
{
	m_dlgbroadcast = new QDialog(this);
	m_broadcast = new QLineEdit(m_dlgbroadcast);
	m_broadcast->setMinimumHeight(50);
	m_broadcast->setMinimumWidth(400);
	buttonBroadcast = new QPushButton(m_dlgbroadcast);
	buttonquitBroadcast = new QPushButton(m_dlgbroadcast);
	buttonBroadcast->setText(QString::fromLocal8Bit("�� ��"));
	buttonquitBroadcast->setText(QString::fromLocal8Bit("�� ��"));
	buttonBox = new QDialogButtonBox(m_dlgbroadcast);
	buttonBox->addButton(buttonBroadcast, QDialogButtonBox::ActionRole);
	buttonBox->addButton(buttonquitBroadcast, QDialogButtonBox::RejectRole);
	m_dlgbroadcast->setWindowTitle(QString::fromLocal8Bit("���͹㲥"));
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_broadcast);
	mainLayout->addWidget(buttonBox);
	m_dlgbroadcast->setLayout(mainLayout);
	connect(buttonBroadcast, SIGNAL(clicked()), this, SLOT(sendBroadcast()));
	connect(buttonquitBroadcast, SIGNAL(clicked()), m_dlgbroadcast, SLOT(close()));
}
void CTeacherManage::showsendBroadcast()
{
	m_broadcast->clear();
	m_dlgbroadcast->show();
	moveToCenter(m_dlgbroadcast);
}
void CTeacherManage::sendBroadcast()
{
	QString str = m_broadcast->text();
	QByteArray datagram =(QString::fromLocal8Bit("���Խ�Ա:") + str).toLocal8Bit () ;
	udpSocket->writeDatagram(datagram.data(), datagram.size(),
		QHostAddress::Broadcast, 45455);
	m_broadcast->clear();

}