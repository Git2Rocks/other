#ifndef QFRAMEBASICSETTINGS_H
#define QFRAMEBASICSETTINGS_H

#include <QFrame>
#include <QButtonGroup>
#include <QMap>

#include "ui_basicsettings.h"
#include "qreadwritexmlfile.h"

class QFrameBasicSettings : public QFrame
{
	Q_OBJECT

public:
	QFrameBasicSettings(QWidget *parent);
	~QFrameBasicSettings();

public:
	void refreshSetting(const QMap<QString, QString>& configure);

signals:
	void labelSettingChanged(const QMap<QString, QString>& configure);

private slots:
	void buttonClicked(QAbstractButton* button);

	void onClickedBtnSave();
	void onClickedBtnBrowse();

	void configureChanged(const QMap<QString, QString>& configure);
	void hostsConfigureChanged(const QMap<QString, QString>& configure);

	void currentIndexChanged(int index);

private:
	void initDeaSettings();
	void addDeaItemsToComboBox(QComboBox* comboBox, const QString& key, const QString& defaultValue);
	void saveDeaItemsConfigure(QComboBox* comboBox, const QString& key);

	void dataChanged();

private:
	Ui::FrameBasicSettings*	m_ui;

private:
	QButtonGroup*	m_pButtonGroup;

	QMonitorConfigureFile*	m_pMonitorActions;
	bool	m_bFirstLoadedActions;		//�˵������ļ��Ƿ��ǵ�һ�μ���

	QMonitorConfigureFile*	m_pMonitorHosts;		//�����б������ļ�
	QMap<QString, QString>	m_configureHosts;
	bool	m_bFirstLoadedHosts;		//���������ļ��Ƿ��ǵ�һ�μ���
};

#endif // QFRAMEBASICSETTINGS_H
