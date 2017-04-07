#ifndef QABSTRACTGRAPHICSITEM_H
#define QABSTRACTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QFont>
#include <QMap>

enum GraphicsItemType
{
	GraphicsItemAbstract=QGraphicsItem::UserType,
	GraphicsItemRouter,
	GraphicsItemSwitch,
	GraphicsItemHub,
	GraphicsItemHost,
	GraphicsItemLink,
	GraphicsItemEnd
};

class QAbstractGraphicsItem : public QGraphicsItem
{
public:
	QAbstractGraphicsItem(QGraphicsItem* parent=0);
	~QAbstractGraphicsItem();

public:
	enum StatusType
	{
		StatusOnline,
		StatusOffline,
		StatusEnd
	};

	enum TickType
	{
		TickZero,
		TickInc,
		TickTop
	};

	typedef struct _common
	{
		QPointF	origin;			//����ԭ��
		QRectF	bounding;		//��Χ��

		QFont font;
		QString	tag;

		int	tick;				//�豸δ���ִ���

		StatusType	status;
		QPixmap	pixmap[StatusEnd];
	}Common;

	enum {Type=GraphicsItemAbstract};

public:
	virtual int type() const	{ return Type; }

public:
	QAbstractGraphicsItem* findServer(quint32 address);		//����ip����ȡ����

	virtual void closeEvent();
	virtual void reconnect();

public:
	void setOrigin(const QPointF& origin);
	void setOrigin(double x, double y);
	QPointF origin() const;

	void setStatus(StatusType status);
	virtual void setTickCount(TickType tick);
	void setTickCountAll(TickType tick);

	void setTag(const QString& tag);

public:
	void addItem(quint32 address, QAbstractGraphicsItem* item, QAbstractGraphicsItem* link=NULL);
	QPair<QAbstractGraphicsItem*, QAbstractGraphicsItem*> removeItem(quint32 address);
	QAbstractGraphicsItem* item(quint32 address) const;
	QAbstractGraphicsItem* itemFromSegment(quint32 segment) const;
	QList<quint32>	items() const;

	bool contains(quint32 address) const;

public:
	virtual void translateItem(double dx, double dy);
	virtual double adjust(double angle=0.0);	//����ͼԪ���֣����ذ�ΧԲ�뾶

public:
	virtual QRectF rect() const;
	virtual QRectF boundingRect() const;

	virtual QRectF boundingVolume() const;		//��������item�İ�Χ��

	void drawBounding(QPainter* painter);

public:
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget=0);

protected:
	Common		m_common;

	QMap<quint32, QPair<QAbstractGraphicsItem*, QAbstractGraphicsItem*> >	m_mapItems;
};

#endif // QABSTRACTGRAPHICSITEM_H
