#ifndef _POINTNAME_H_
#define _POINTNAME_H_

#include "ui_pointname.h"
#include "qcommon.h"

Q_DECLARE_METATYPE(POINTER);
class CPointNameTable : public QDialog,public Ui_CPointNameTable
{
	Q_OBJECT
public:
	CPointNameTable(QWidget *parent=0);
	void loadChinese();
	void loadEnglish();
	void InitTreeView();
	void SetSelected(const QString &selected_pt_name);	
	void DispTreeView(short stn,short dev,short data_type);
	QString P_entry_name;
protected:
	void showEvent(QShowEvent *);
signals:
	void sig_curPointName(const QString &);
	void sig_curEntryName(const QString &);
private:
	QString curPointName;
private slots:
	void ItemSelected(QTreeWidgetItem *);
	void Enter();
public slots:
	void setLanguage( int );
};
#endif