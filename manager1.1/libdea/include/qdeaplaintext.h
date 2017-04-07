#ifndef QDEAPLAINTEXT_H
#define QDEAPLAINTEXT_H

#include <QByteArray>

#include "qabstractdes.h"

class DEA_EXPORT QDeaPlainText : public QIDEA
{
public:
	QDeaPlainText();
	~QDeaPlainText();

public:
	enum {Type=PlainText};

public:
	virtual int type() const	{return Type;}	//����
	virtual const QString desc() const {return "PlainText";}

	virtual QByteArray encrypt(const QByteArray& data);	//����
	virtual QByteArray decrypt(const QByteArray& data);
};

#endif // QDEAPLAINTEXT_H
