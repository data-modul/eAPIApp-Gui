#ifndef I2C_H
#define I2C_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QTextEdit>
#include <QRadioButton>
#include <QComboBox>
#include <QTimer>
#include <QCheckBox>
#include <QPlainTextEdit>

#ifndef _MSC_VER
  #include <unistd.h>
#else
  #include <stdint.h>
  #include <EApiOsNTC.h>
#endif

#include "temperatureBar.h"

struct i2c_adap {
    int nr;
    char *name;
};

#define BUNCH 8
#define I2C_DMEC        "i2c-dmec"
#define MUX_CHANNEL     "%s (chan_id %d"

class i2c: public QWidget
{
    Q_OBJECT
public:
    i2c(QWidget *parent = 0);
    int find_eeprom(void);
    void free_adapters(struct i2c_adap *adapters);
    struct i2c_adap* gather_i2c_busses(void);
    struct i2c_adap* more_adapters(struct i2c_adap *adapters, int n);
    int add_i2c_busses(QComboBox *i2cBusses);

public slots:
    void readClicked();
    void writeClicked();
    void writereadClicked();
    void temperatureClicked();
    void timingSelected(bool checked);
    void offsetChanged(QString text);
    void readlengthChanged(QString text);
    void writelengthChanged(QString text);
    void timeoutTimer();

    void readWriteByteRadioButtonClicked(bool checked);
    void readWriteBlockRadioButtonClicked(bool checked);
    void readWriteCombineRadioButtonClicked(bool checked);
    void byteRadioButtonClicked(bool checked);
    void wordRadioButtonClicked(bool checked);
    void handleI2CselectionChanged(int index);
    void slaveChanged(QString text);
    void getInput();

private:
    uint32_t offset;
    uint32_t readlength;
    uint32_t writelength;
    int protocol;
    uint32_t i2cBus;
    uint32_t base_addr;
    uint32_t slave;
    unsigned int offsetType; /*0: byte, 1:word */
    bool timing;

    QRadioButton *readWriteByteRadioButton;
    QRadioButton *readWriteBlockRadioButton;
    QRadioButton *readWriteCombineRadioButton;

    QVBoxLayout *protocolLayout;
    QGroupBox *protocolGroup;
    QGroupBox *deviceGroup;
    QHBoxLayout *deviceLayout;

    QGridLayout *parameterGrid;
    QGridLayout *deviceGrid;

    QLabel *i2cIDLabel;
    QComboBox *i2cID;

    QLabel *slaveLabel;
    QLineEdit *slaveValue;

    QLabel *offsetLabel;
    QLineEdit *offsetValue;

    QLabel *offsetTypeLabel;
    QRadioButton *byteRadioButton;
    QRadioButton *wordRadioButton;

    QLabel *readlengthLabel;
    QLineEdit *readlengthValue;

    QLabel *writelengthLabel;
    QLineEdit *writelengthValue;

    QCheckBox *timingCheckbox;

    QLabel *writeLabel;
    QTextEdit *writeValue;

    QLabel *readLabel;
    QTextEdit *readValue;

    QPushButton *readButton;
    QPushButton *writeButton;
    QPushButton *writereadCombineButton;

    QGroupBox *controlGroup;

    QPushButton *temperatureButton;
    QGridLayout *demoGrid;
    QGroupBox *demoGroup;


    QGridLayout *grid;

    TemperatureBar *temperaturebar;
    QTimer *timer;

    QString input;


};

#endif // I2C_H
