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

struct i2c_adap {
    int nr;
    char *name;
};

#define BUNCH 8
#define I2C_DMEC    "i2c-dmec"

class i2c: public QWidget
{
    Q_OBJECT
public:
    i2c(QWidget *parent = 0);
    int find_eeprom(void);
    void free_adapters(struct i2c_adap *adapters);
    struct i2c_adap* gather_i2c_busses(void);
    struct i2c_adap* more_adapters(struct i2c_adap *adapters, int n);

public slots:
    void readClicked();
    void writeClicked();
    void temperatureClicked();
    void offsetChanged(QString text);
    void lengthChanged(QString text);

    void readWriteByteRadioButtonClicked(bool checked);
    void readWriteBlockRadioButtonClicked(bool checked);
    void readWriteCombineRadioButtonClicked(bool checked);
    void byteRadioButtonClicked(bool checked);
    void wordRadioButtonClicked(bool checked);
    void handleI2CselectionChanged(int index);
    void slaveChanged(QString text);

private:
    uint32_t offset;
    uint32_t length;
    int protocol;
    uint32_t i2cBus;
    uint32_t base_addr;
    uint32_t slave;
    unsigned int offsetType; /*0: byte, 1:word */

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

    QLabel *lengthLabel;
    QLineEdit *lengthValue;

    QLabel *writeLabel;
    QTextEdit *writeValue;

    QLabel *readLabel;
    QTextEdit *readValue;

    QPushButton *readButton;
    QPushButton *writeButton;

    QGroupBox *controlGroup;

    QPushButton *temperatureButton;
    QGridLayout *demoGrid;
    QGroupBox *demoGroup;


    QGridLayout *grid;
};

#endif // I2C_H
