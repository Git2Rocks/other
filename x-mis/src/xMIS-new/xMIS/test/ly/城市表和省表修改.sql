--SELECT * FROM xmis.add_��ַ WHERE ����ID=109
--����341��
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID<34

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=34
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=35
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=36

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=37 AND ����ID<=58

UPDATE xmis.add_���� SET ��������='�ӱ߳�����������' WHERE ����ID=59

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=60 AND ����ID<=71

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID=72
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=73 AND ����ID<=108
DELETE FROM xmis.add_���� WHERE ����ID=109
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=110 AND ����ID<=179
UPDATE xmis.add_���� SET ��������='��ʩ����������������' WHERE ����ID=180
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=181 AND ����ID<=193
UPDATE xmis.add_���� SET ��������='��������������������' WHERE ����ID=194

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=195 AND ����ID<=249

UPDATE xmis.add_���� SET ��������='���Ӳ���Ǽ��������' WHERE ����ID=250
UPDATE xmis.add_���� SET ��������='���β���������' WHERE ����ID=251
UPDATE xmis.add_���� SET ��������='��ɽ����������' WHERE ����ID=252
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=253 AND ����ID<=257

UPDATE xmis.add_���� SET ��������='ǭ���ϲ���������������' WHERE ����ID=259
UPDATE xmis.add_���� SET ��������='ǭ�������嶱��������' WHERE ����ID=260
UPDATE xmis.add_���� SET ��������='ǭ�ϲ���������������' WHERE ����ID=261
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=262 AND ����ID<=269

UPDATE xmis.add_���� SET ��������='��ɽ׳������������' WHERE ����ID=270
UPDATE xmis.add_���� SET ��������='��ӹ���������������' WHERE ����ID=271
UPDATE xmis.add_���� SET ��������='��˫���ɴ���������' WHERE ����ID=272
UPDATE xmis.add_���� SET ��������='��������������' WHERE ����ID=273
UPDATE xmis.add_���� SET ��������='�������������' WHERE ����ID=274
UPDATE xmis.add_���� SET ��������='�º���徰����������' WHERE ����ID=275
UPDATE xmis.add_���� SET ��������='ŭ��������������' WHERE ����ID=276
UPDATE xmis.add_���� SET ��������='�������������' WHERE ����ID=277

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=278

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID>278 AND ����ID<285
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=285 AND ����ID<=306
UPDATE xmis.add_���� SET ��������='���Ļ���������' WHERE ����ID=307
UPDATE xmis.add_���� SET ��������='���ϲ���������' WHERE ����ID=308
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=309

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID=310

UPDATE xmis.add_���� SET ��������='��������������' WHERE ����ID=311
UPDATE xmis.add_���� SET ��������='���ϲ���������' WHERE ����ID=312
UPDATE xmis.add_���� SET ��������='�������������' WHERE ����ID=314
UPDATE xmis.add_���� SET ��������='���ϲ���������' WHERE ����ID=313
UPDATE xmis.add_���� SET ��������='��������������' WHERE ����ID=315
UPDATE xmis.add_���� SET ��������='�����ɹ������������' WHERE ����ID=316

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID>=317 AND ����ID<=323

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID>323 AND ����ID<329
UPDATE xmis.add_���� SET ��������='�������տ¶�����������' WHERE ����ID=329
UPDATE xmis.add_���� SET ��������='���������ɹ�������' WHERE ����ID=330

UPDATE xmis.add_���� SET ��������='��������������' WHERE ����ID=331
UPDATE xmis.add_���� SET ��������='���������ɹ�������' WHERE ����ID=332
UPDATE xmis.add_���� SET ��������='���������������' WHERE ����ID=333

UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID=334
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'����' WHERE ����ID=335
UPDATE xmis.add_���� SET ��������='����ر�������' WHERE ����ID=336
UPDATE xmis.add_���� SET ��������='�����ر�������' WHERE ����ID=337
UPDATE xmis.add_���� SET ��������='̨��' WHERE ����ID=338
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=339
UPDATE xmis.add_���� SET ��������=RTRIM(��������)+'��' WHERE ����ID=340

INSERT INTO xmis.add_����
        ( ����ID ,
          ���б��� ,
          �������� ,
          ���м�� ,
          ���� ,
          ʡID ,
          ����޸����� ,
          ����޸���ID
        )
VALUES  ( 341, -- ����ID - smallint
          '' , -- ���б��� - varchar(50)
          '��ɳ��' , -- �������� - varchar(50)
          '' , -- ���м�� - varchar(50)
          '' , -- ���� - varchar(50)
          20 , -- ʡID - smallint
          '2012-11-05 09:46:49' , -- ����޸����� - datetime
          0  -- ����޸���ID - int
        )
--ʡ
UPDATE xmis.add_ʡ SET ʡ���� = RTRIM(ʡ����)+'ʡ' WHERE ʡID  NOT IN(1,2,9,22,32,33,31,30,26,21,5)

UPDATE xmis.add_ʡ SET ʡ���� = RTRIM(ʡ����)+'��' WHERE ʡID  IN(1,2,9,22)


UPDATE xmis.add_ʡ SET ʡ����='����ر�������' WHERE ʡID=32

UPDATE xmis.add_ʡ SET ʡ����='�����ر�������' WHERE ʡID=33
 
UPDATE xmis.add_ʡ SET ʡ����='�½�ά���������' WHERE ʡID=31

UPDATE xmis.add_ʡ SET ʡ����='���Ļ���������' WHERE ʡID=30

UPDATE xmis.add_ʡ SET ʡ����='����������' WHERE ʡID=26

UPDATE xmis.add_ʡ SET ʡ����='����׳��������' WHERE ʡID=21
 
UPDATE xmis.add_ʡ SET ʡ����='���ɹ�������' WHERE ʡID=5

