#ifndef QLEADERELECTION_H
#define QLEADERELECTION_H

#include <QObject>
#include <QMutex>

#include "global.h"
#include "qmulticastsender.h"

class DDB_EXPORT QLeaderElection : public QObject
{
	Q_OBJECT

public:
	QLeaderElection(const QString& uid, QMulticastSenderPtr& sender, QObject *parent=0);
	~QLeaderElection();

public:
	enum ElectionRole
	{
		LeaderRole,
		CandidateRole,
		VoteRole,	//ͶƱ
		UncheckedRole,	//δѡ��
		ManagedRole
	};

public:
	ElectionRole electionRole();
	void setElectionRole(ElectionRole role);

public:
	void queryElectLeader();
	void queryVote(double performance);

private:
	QMulticastSenderPtr		m_pSender;

	QMutex		m_mutex;

	QString			m_uid;
	ElectionRole	m_role;		//���쵼��ѡ���еĵ�ǰ��ɫ
};

#endif // QLEADERELECTION_H
