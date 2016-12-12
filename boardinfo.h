#ifndef BOARDINFO_H
#define BOARDINFO_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <EApi.h>

class boardInfo : public QWidget
{
    Q_OBJECT

public:
    boardInfo(QWidget *parent = 0);
    void fill(void);

private:
    QLabel *manufacturerNameLabel;
    QLabel *manufacturerNameValueLabel;
    QHBoxLayout* manufacturerlayout;
    QLabel *pnpLabel;
    QLabel *pnpValueLabel;
    QHBoxLayout* pnplayout;
    QLabel *boardNameLabel;
    QLabel *boardNameValueLabel;
    QHBoxLayout* boardNamelayout;
    QLabel *boardIDLabel;
    QLabel *boardIDValueLabel;
    QHBoxLayout* boardIDlayout;
    QLabel *boardSNLabel;
    QLabel *boardSNValueLabel ;
    QHBoxLayout* boardSNlayout;
    QLabel *biosRevisionLabel;
    QLabel *biosRevisionValueLabel;
    QHBoxLayout* biosRevisionlayout;
    QLabel *platformTypeLabel;
    QLabel *platformTypeValueLabel;
    QHBoxLayout* platformTypelayout;
    QLabel *HWRevisionLabel;
    QLabel *HWRevisionValueLabel;
    QHBoxLayout* HWRevisionlayout;
    QLabel *manufacturDateLabel;
    QLabel *manufacturDateValueLabel;
    QHBoxLayout* manufacturDatelayout;
    QLabel *specRevisionLabel;
    QLabel *specRevisionValueLabel;
    QHBoxLayout* specRevisionlayout;
    QVBoxLayout *mainLayout;
};

#endif // BOARDINFO_H
