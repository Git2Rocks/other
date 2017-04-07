#ifndef QTREEVIEWCOMPAREFILE_H
#define QTREEVIEWCOMPAREFILE_H

#include <QTreeView>
#include <QPoint>
#include <QUndoCommand>

#include "qcomparefiledelegate.h"

class QCompareFileUndoCommand;
class QTreeViewCompareFile : public QTreeView
{
	Q_OBJECT

public:
	QTreeViewCompareFile(bool inverse=false, bool lockable=false, QWidget *parent=0);
	~QTreeViewCompareFile();

public:
	void selectItem(const QModelIndex& index);
	void selectBlock(const QModelIndexList& indexes);
	void selectChangedBlock(const QModelIndex& index);

	QCompareFileUndoCommand* copy(QTreeViewCompareFile* treeview);
	QCompareFileUndoCommand* copyWhole(QTreeViewCompareFile* treeview);

	QModelIndexList selectedIndexes() const;
	QVector<int> lockedColumns() const;

	bool nextDifference(bool move=true);
	bool previousDifference(bool move=true);

	bool nextItemDifference(bool move=true);
	bool previousItemDifference(bool move=true);

public:
	virtual void setModel(QAbstractItemModel* model);

public:
	static QModelIndexList treePath(const QModelIndex& index);

public slots:
	void sectionClicked(int logicalIndex);

signals:
	void blockSelection(const QModelIndexList& indexes);
	void itemSelection(const QModelIndex& index);
	void lockedChanged();
	void mouseRightButtonPress(QPoint pos);

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

private slots:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	void doubleClicked(const QModelIndex& index);

private:
	void copy(QAbstractItemModel* smodel, const QModelIndex& psindex, QAbstractItemModel* tmodel, const QModelIndex& ptindex,
		QCompareFileUndoCommand* command);

private:
	enum HeaderUserRole
	{
		LockRole=Qt::UserRole
	};

private:
	void clearSelected();
	void setSelected(const QModelIndexList& indexes);

	bool findPreviousDifference(const QModelIndex& index, bool move=true);		//move=true,�ƶ�����һ�����죬����ֻ�ǲ���
	bool findNextDifference(const QModelIndex& index, bool move=true);

	bool findPreviousItemDifference(const QModelIndex& index, bool move=true);
	bool findNextItemDifference(const QModelIndex& index, bool move=true);

private:
	QCompareFileDelegate*	m_pDelegate;

	QModelIndexList			m_indexes;

	QModelIndex		m_indexClicked;		//����ͬһ��

	bool	m_bLockable;	//�Ƿ���Զ��н�������
};

class QCompareFileUndoCommand : public QUndoCommand
{
public:
	QCompareFileUndoCommand(QAbstractItemModel* model, QUndoCommand* parent=0);
	virtual ~QCompareFileUndoCommand();

public:
	typedef struct _undoCommand
	{
		QModelIndex index;		//�����޸�Ŀ��
		QVariant	svalue;		//��ֵǰֵ
		QVariant	tvalue;		//��ֵ��ֵ
		int			role;
	}UndoCommand;

public:
	virtual void redo();
	virtual void undo();

public:
	void appendCommand(const QModelIndex& index, const QVariant& svalue, const QVariant& tvalue, int role=Qt::EditRole);

private:
	QAbstractItemModel* m_pModel;

	QVector<UndoCommand>	m_commands;
};

#endif // QTREEVIEWCOMPAREFILE_H
