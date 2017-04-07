#include "inc/TranslatePoint.h"
CTranslatePoint::CTranslatePoint(QWidget* parent)
	:QMainWindow(parent)
{	  
	flagStart=true;
	createTrayIcon();
	pPopupMsg = new CPopupMsg;
	board = QApplication::clipboard();   
	connect(board,SIGNAL(dataChanged()),this,SLOT(openPopupMsg()));
	connect(iTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
CTranslatePoint::~CTranslatePoint()
{
	
} 
void CTranslatePoint::createActions() 
{ //�����ϵ� 
	startAction = new QAction(QString::fromLocal8Bit("�ı�ץȡ (&S)"), this);
	startAction->setCheckable(true);
	startAction->setChecked(true);
	connect(startAction, SIGNAL(triggered()), this, SLOT(setStartGrab())); 
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
void CTranslatePoint::createTrayIcon()
{
	iTrayIcon=new QSystemTrayIcon(this);	
	iTrayIcon->setIcon(QIcon(QString::fromLocal8Bit(":/images/main.ico")));	
	iTrayIcon->setToolTip(QString::fromLocal8Bit("TranslatePoint"));
	createActions(); 
	createTrayMenu(); 
	iTrayIcon->show();
}
void CTranslatePoint::createTrayMenu() 
{
	trayIconMenu = new QMenu(this); 
	trayIconMenu->addAction(startAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(minimizeAction); 
	trayIconMenu->addAction(maximizeAction); 
	trayIconMenu->addAction(restoreAction); 
	trayIconMenu->addSeparator(); 
	trayIconMenu->addAction(quitAction); 
	iTrayIcon->setContextMenu(trayIconMenu); 
}//����
void CTranslatePoint::iconActivated(QSystemTrayIcon::ActivationReason reason) 
{ 	
	//������굥��˫���¼�
	switch (reason) 
	{ 
		case QSystemTrayIcon::DoubleClick: 
			this->showNormal();
			this->activateWindow();
			this->focusWidget();
			break;
		default:
			break; 
	} 
} 
void CTranslatePoint::closeEvent(QCloseEvent *event)//�رմ�����С��
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
	chk->setText(QString::fromLocal8Bit("��������"));
	lbl->setText(QString::fromLocal8Bit("������˹رհ�ť�������룺"));
	chkMin->setText(QString::fromLocal8Bit("��С����ϵͳ�����������˳�����"));
	chkClose->setText(QString::fromLocal8Bit("�˳�����"));
	butEnter->setText(QString::fromLocal8Bit("ȷ��"));
	butExit->setText(QString::fromLocal8Bit("ȡ��"));
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
void CTranslatePoint::checkQuit()
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
void CTranslatePoint::oncheckbox(int state)
{
	ifshowtip=state;
}
void CTranslatePoint::isQuit()
{
	QMessageBox msgBox(this);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setWindowTitle (QString::fromLocal8Bit("��ʾ"));
	msgBox.setInformativeText(QString::fromLocal8Bit("ȷ��Ҫ�˳�TranslatePoint��"));
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
void CTranslatePoint::setStartGrab()
{
	if (startAction->isChecked())
	{
		flagStart=true;
	}
	else
	{
		flagStart=false;
	}
}
void CTranslatePoint::openPopupMsg()
{
	if (flagStart)
	{
		QString text = board->text();
		if (CheckPointName(text)==false && CheckPointId(text)==false)	return;
		pPopupMsg->setSelectedText(text);
		pPopupMsg->updateMsg();
		pPopupMsg->showNormal();
		pPopupMsg->activateWindow();
		pPopupMsg->move(QCursor::pos());
	}
}