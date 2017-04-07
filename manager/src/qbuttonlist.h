#ifndef QBUTTONLIST_H
#define QBUTTONLIST_H

#include <QFrame>
#include <QToolButton>
#include <QButtonGroup>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QFont>

class QButtonList : public QFrame
{
	Q_OBJECT

public:
	QButtonList(QWidget *parent);
	~QButtonList();

public:
	void addButton(const QString& text, int id);
	int clickedButton();

public slots:
	void click(int id);

signals:
	void buttonClicked(int id);

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);

private:
	QList<QToolButton*>		m_listButtons;

	QButtonGroup*	m_pGroup;

	int	m_nHeight;		//��ť�߶�
	int m_nSpacing;		//��ť֮��ļ��
	int m_nBorder;		//��ť������

	QFont m_font;
};

#endif // QBUTTONLIST_H
