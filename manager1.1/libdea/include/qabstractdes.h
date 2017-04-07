#ifndef QABSTRACTDES_H
#define QABSTRACTDES_H

#include "global.h"
#include "qidea.h"

typedef bool (*PSubKey)[16][48];

class QAbstractDES : public QIDEA
{
public:
	QAbstractDES();
	~QAbstractDES();

public:
	bool run(char *out,const char *in,long datalen,const char *key,int keylen,bool type = ENCRYPT);

protected:
	void des(char out[8], const char in[8], const PSubKey pSubKey, bool type);//��׼DES��/����
	void setKey(const char* key, int len);// ������Կ
	void setSubKey(PSubKey pSubKey, const char key[8]);// ��������Կ
	void fFunc(bool in[32], const bool ki[48]);// f ����
	void sFunc(bool out[32], const bool in[48]);// S �д���
	void transform(bool *out, bool *in, const char *table, int len);// �任
	void _xor(bool *inA, const bool *inB, int len);// ���
	void rotateL(bool *in, int len, int loop);// ѭ������
	void byteToBit(bool *out, const char *in, int bits);// �ֽ���ת����λ��
	void bitToByte(char *out, const bool *in, int bits);// λ��ת�����ֽ���

private:
	bool m_subKey[2][16][48];// 16Ȧ����Կ
	bool m_bIs3DES;// 3��DES��־
};

#endif // QABSTRACTDES_H
