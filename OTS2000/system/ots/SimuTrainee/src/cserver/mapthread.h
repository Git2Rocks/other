#ifndef MAPTHREAD_H
#define MAPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPixmap>

class MapThread : public QThread
{
    Q_OBJECT

private:

    int dest_width;           //�ͻ���ָ���Ŀ��
    int dest_height;          //�ͻ���ָ���ĸ߶�
    int send_width;           //����ͼ��Ŀ��
    int send_height;          //����ͼ��ĸ߶�
    int scaleby;              //����������Ŀ��ͼ��ĸ߶Ȼ��ǿ��

    uchar* sent_img_buf;   //buffer of the image that have been sent
    uchar* curt_img_buf;   //buffer of the current image
    uchar* send_data_buf;
    uchar cmd_buf[4];
    int   cmd_buf_fill;

    bool started;

    int          interval;         //֡��ʱ����
    QTcpSocket*  mapSocket;
    QTimer* timer;

public:
    MapThread(QTcpSocket* socket, QObject *parent = 0);
    ~MapThread();

    const static int SCALE_BY_WIDTH  = 1;
    const static int SCALE_BY_HEIGHT = 2;

    void setSendInterval(int i);
    
signals:
    
public slots:
    void sendFrame();
    void newData();
    void newCommand();
    void quit();

protected:
    void run();
    
};

#endif // MAPTHREAD_H
