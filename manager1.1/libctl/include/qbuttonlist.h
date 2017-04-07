#ifndef QBUTTONLIST_H
#define QBUTTONLIST_H

#include <QFrame>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QFont>

#include "libctlglobal.h"

class CTL_EXPORT QButtonList : public QFrame
{
	Q_OBJECT

public:
	QButtonList(QWidget *parent);
	~QButtonList();

public:
	void addButton(const QString& text, int id);
	void addCheckableButton(const QString& text, int id);

	void addButton(QAbstractButton* button, int id);

	int clickedButton() const;
	QVector<int> checkedButtons() const;

	bool hasChecked() const;

	void setExclusive(bool exclusive);

public slots:
	void click(int id);

signals:
	void buttonClicked(int id);
	void buttonChecked(int id, bool checked);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

private slots:
	void stateChanged(int id);

private:
	QList<QWidget*>		m_listButtons;

	QButtonGroup*	m_pGroup;
	QButtonGroup*	m_pCheckGroup;

	int	m_nHeight;		//��ť�߶�
	int m_nSpacing;		//��ť֮��ļ��
	int m_nBorder;		//��ť������

	QFont m_font;
};

#endif // QBUTTONLIST_H
