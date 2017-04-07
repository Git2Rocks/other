#include "hostpage.h"

Hostpage::Hostpage(QWidget* parent)
:QWidget(parent)
{
	setupUi(this);
	show_count = 0;
	dlg_created_flag[HOSTPAGEDLG]= true;
	this->setObjectName("hostpage");
	this->setAttribute(Qt::WA_DeleteOnClose);
	if (flag_langueage == 0)
	{
		loadChinese();
	}
	else if (flag_langueage == 1)
	{
		loadEnglish();
	}	
	this->setStyleSheet("");
	connect(toolButton_ModeS,SIGNAL(clicked()),this,SLOT(on_toolButton_ModeS()));
	connect(toolButton_ModeE,SIGNAL(clicked()),this,SLOT(on_toolButton_ModeE()));
	connect(toolButton_ModeC,SIGNAL(clicked()),this,SLOT(on_toolButton_ModeC()));
	connect(pushButton_EtStudy,SIGNAL(clicked()),this,SLOT(on_pushButton_EtStudy()));
	connect(pushButton_EtExam,SIGNAL(clicked()),this,SLOT(on_pushButton_EtExam()));
	connect(pushButton_EtComplet,SIGNAL(clicked()),this,SLOT(on_pushButton_EtComplet()));
	connect(pushButton_oprrecord,SIGNAL(clicked()),this,SLOT(on_pushButton_oprrecord()));
	connect(pushButton_studyrecord,SIGNAL(clicked()),this,SLOT(on_pushButton_studyrecord()));
	connect(pushButton_scorerecord,SIGNAL(clicked()),this,SLOT(on_pushButton_scorerecord()));
	connect(toolButton_personinfo, SIGNAL(clicked()), this, SLOT(on_toolButton_personinfo()));
}
Hostpage::~Hostpage()
{
	show_count = 0;
	dlg_created_flag[HOSTPAGEDLG]= false;
}
void Hostpage::loadChinese()
{
	QTranslator translator;
	translator.load("SimuTrainee_zh_CN");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void Hostpage::loadEnglish()
{
	QTranslator translator;
	translator.load("SimuTrainee_en");
	qApp->installTranslator(&translator);
	retranslateUi(this);
}
void Hostpage::showEvent(QShowEvent *event)
{
	if (show_count == 0)
	{
// 		this->setStyleSheet("");
// 		this->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/images/background/hostpagebackround.png);"));
// 		bool i;
// 		QFile file(":/pic/qss/mdidialog.qss");
// 		i = file.open(QFile::ReadOnly);
// 		QString m_styleSheet= QLatin1String(file.readAll());
// 		//m_styleSheet = this->styleSheet();
// 		// 		//qApp->setStyleSheet(styleSheet);
// 		this->setStyleSheet(m_styleSheet);	
	}
	show_count ++;
// 	if (flag_langueage == 0)
// 	{
// 		loadChinese();
// 	}
// 	else if (flag_langueage == 1)
// 	{
// 		loadEnglish();
// 	}
	update();
	event->accept();
}
void Hostpage::update()
{
	label_username->setText(login_user_longname);

	QString userrange;
	switch (u_info.user_type_id/2)
	{
		case 0:
			userrange = QString::fromLocal8Bit("һ   ��");
			label_userrange->setStyleSheet("color: rgb(0, 0, 200);");
			break;
		case 1:
			userrange = QString::fromLocal8Bit("��   ��");
			label_userrange->setStyleSheet("color: rgb(163, 163, 163);");
			break;	
		case 2:
			userrange = QString::fromLocal8Bit("��   ��");
			label_userrange->setStyleSheet("color: rgb(149, 149, 0);");			
			break;
	}
	label_userrange->setText(userrange);
	QString usetype;
	switch (u_info.user_type_id)
	{
	case 0:
		usetype = QString::fromLocal8Bit("��Ա��");
		break;
	case 1:
		usetype = QString::fromLocal8Bit("������");
		break;	
	case 2:
		usetype = QString::fromLocal8Bit("�м���");
		break;
	case 3:
		usetype = QString::fromLocal8Bit("�߼���");
		break;
	case 4:
		usetype = QString::fromLocal8Bit("��ʦ");
		break;	
	case 5:
		usetype = QString::fromLocal8Bit("�߼���ʦ");
		break;
	}
	label_usertype->setText(usetype);
	QString simumode;
	switch (shm_ots_addr->simu_mode)
	{
	case 0:
		simumode = QString::fromLocal8Bit("ѧϰ");
		break;
	case 1:
		simumode = QString::fromLocal8Bit("����");
		break;	
	case 2:
		simumode = QString::fromLocal8Bit("����");
		break;
	}
	if (u_info.groups_id >0)
	{
		label_usermode->setText(QString::fromLocal8Bit("����%1ģʽ(%2��)").arg(simumode).arg(u_info.groups_name));
	}
	else
		label_usermode->setText(QString::fromLocal8Bit("����%1ģʽ").arg(simumode));
	if (shm_ots_addr->simu_mode ==2)
	{
		DB_FMT data;
		data.table_id = TABLE_CONTEST;
		InitDbData(&data,data.table_id);
		data.cond_flag.flag_contest.open_state= TRUE;
		data.cond_seg.seg_contest.open_state = 1;
		if (SelectRecs(&data)!= TRUE)
		{
			PopupMessageBox(this,"��ǰ�޿����еľ���",QMessageBox::Information);
			return;
		}
		label_ContestNum->setEnabled(true);
		label_ContestNum->setText(QString::fromLocal8Bit("%1�����������С�").arg(data.rownum));
	}
	else
		label_ContestNum->setText("");
//	label_userrange->setText(QString::number(u_info.user_range));
}
void  Hostpage::on_toolButton_ModeS()
{
	if (shm_ots_addr->simu_mode ==0)
	{
		radioButton_ST->setEnabled(true);
		radioButton_SO->setEnabled(true);
		radioButton_ET->setEnabled(false);
		radioButton_EO->setEnabled(false);
		pushButton_EtStudy->setEnabled(true);
		pushButton_EtExam->setEnabled(false);
		pushButton_EtComplet->setEnabled(false);
	}
	else
	{
		PopupMessageBox(this,"��ǰѧԱģʽ����ѧϰģʽ",QMessageBox::Information);
		return;
	}

}
void  Hostpage::on_toolButton_ModeE()
{
	if (shm_ots_addr->simu_mode ==1)
	{
		radioButton_ST->setEnabled(false);
		radioButton_SO->setEnabled(false);
		radioButton_ET->setEnabled(true);
		radioButton_EO->setEnabled(true);
		pushButton_EtStudy->setEnabled(false);
		pushButton_EtExam->setEnabled(true);
		pushButton_EtComplet->setEnabled(false);
	}
	else
	{
		PopupMessageBox(this,"��ǰѧԱģʽ���ǿ���ģʽ",QMessageBox::Information);
		return;
	}
}
void  Hostpage::on_toolButton_ModeC()
{
	if (shm_ots_addr->simu_mode ==2)
	{
		radioButton_ST->setEnabled(false);
		radioButton_SO->setEnabled(false);
		radioButton_ET->setEnabled(false);
		radioButton_EO->setEnabled(false);
		pushButton_EtStudy->setEnabled(false);
		pushButton_EtExam->setEnabled(false);
		pushButton_EtComplet->setEnabled(true);
	}
	else
	{
		PopupMessageBox(this,"��ǰѧԱģʽ���Ǿ���ģʽ",QMessageBox::Information);
		return;
	}
}
void Hostpage::on_pushButton_EtStudy()
{
	if (!radioButton_ST->isChecked ()&&!radioButton_SO->isChecked ())
	{
		PopupMessageBox(this,"����ѡ��һ��ѧϰģʽ",QMessageBox::Information);
	}
	else if (radioButton_ST->isChecked ())
	{
		emit STclicked();
	}
	else if (radioButton_SO->isChecked ())
	{
		emit SOclicked();
	}
}
void Hostpage::on_pushButton_EtExam()
{
	if (!radioButton_ET->isChecked ()&&!radioButton_EO->isChecked ())
	{
		PopupMessageBox(this,"����ѡ��һ�ֿ���",QMessageBox::Information);
	}
	else if (radioButton_ET->isChecked ())
	{
		emit ETclicked();
	}
	else if (radioButton_EO->isChecked ())
	{
		emit EOclicked();
	}
}
void Hostpage::on_pushButton_EtComplet()
{
	emit CPTclicked();
}
void Hostpage::on_pushButton_oprrecord()
{
	emit 	sig_showrecords();
}
void Hostpage::on_pushButton_studyrecord()
{
	emit  sig_showstudyrecords();
}
void Hostpage::on_pushButton_scorerecord()
{
	emit  sig_showscores();
}
void Hostpage::on_toolButton_personinfo()
{
	emit  sig_showpersoninfo();
}

void  Hostpage::setLanguage(int language)
{	
	QTranslator translator;
	if (language == 0)
	{
		translator.load("SimuTrainee_zh_CN");
	}
	else if (language == 1)
	{
		translator.load("SimuTrainee_en");
	}
	qApp->installTranslator(&translator);
	retranslateUi(this);
		update();
}