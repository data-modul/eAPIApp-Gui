#ifndef STORAGE_H
#define STORAGE_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QTextEdit>


class storage: public QWidget
{
    Q_OBJECT
public:
    storage(QWidget *parent = 0);

public slots:
    void readClicked();
    void writeClicked();
    void offsetChanged(QString text);
    void lengthChanged(QString text);

private:
    bool  definedStorage;
    uint32_t offset;
    uint32_t length;
    uint32_t pStorgeSize;

    QLabel *storageSize;
    QLabel *storageType;
    QVBoxLayout *infoLayout;

    QLabel *offsetLabel;
    QLineEdit *offsetValue;

    QLabel *lengthLabel;
    QLineEdit *lengthValue;

    QLabel *writeLabel;
    QTextEdit *writeValue;

    QLabel *readLabel;
    QTextEdit *readValue;

    QGridLayout *bytegrid;

    QPushButton *readButton;
    QPushButton *writeButton;

     QGroupBox *infoGroup;
     QGroupBox *byteGroup;

     QGridLayout *grid;
};

#endif // STORAGE_H
