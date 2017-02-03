#include "i2c.h"
#include <dirent.h>
#include <fcntl.h>
#include <qdebug.h>
#include <EApi.h>
#include  <unistd.h>
#include <QPainter>


i2c::i2c(QWidget *parent)
    :QWidget(parent)
{
    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setPointSize(11);

    timer = new QTimer(this);

    readWriteByteRadioButton = new QRadioButton("Read/Write Register");
    readWriteByteRadioButton->setFont(fontvalue);
    readWriteByteRadioButton->setStyleSheet("QLabel { color : black; }");

    readWriteBlockRadioButton = new QRadioButton("Read/Write Block(Continuous)");
    readWriteBlockRadioButton->setFont(fontvalue);
    readWriteBlockRadioButton->setStyleSheet("QLabel { color : black; }");

    readWriteCombineRadioButton = new QRadioButton("Write Read Raw");
    readWriteCombineRadioButton->setFont(fontvalue);
    readWriteCombineRadioButton->setStyleSheet("QLabel { color : black; }");

    readWriteByteRadioButton->setChecked(1);
    protocol = 0; /*0: register, 1:block, 2:raw */

    connect( readWriteByteRadioButton, SIGNAL( toggled(bool) ), this, SLOT( readWriteByteRadioButtonClicked(bool) ) );
    connect( readWriteBlockRadioButton, SIGNAL( toggled(bool) ), this, SLOT( readWriteBlockRadioButtonClicked(bool) ) );
    connect( readWriteCombineRadioButton, SIGNAL( toggled(bool) ), this, SLOT( readWriteCombineRadioButtonClicked(bool) ) );

    protocolLayout = new QVBoxLayout;
    protocolLayout->addWidget(readWriteByteRadioButton);
    protocolLayout->addWidget(readWriteBlockRadioButton);
    protocolLayout->addWidget(readWriteCombineRadioButton);

    protocolGroup = new QGroupBox("Protocol");
    protocolGroup->setFont(fontlabel);
    protocolGroup->setLayout(protocolLayout);

    /*************************************************/

    i2cIDLabel = new QLabel("I2C Select:");
    i2cIDLabel->setFont(fontlabel);
    i2cIDLabel->setStyleSheet("QLabel { color : black; }");

    i2cID = new QComboBox;
    base_addr = find_eeprom();
    i2cID->setFont(fontvalue);
    i2cID->setStyleSheet("QComboBox { color : black; }");
    i2cID->addItem(QString::number(base_addr));
    i2cID->addItem(QString::number(base_addr+1));
    i2cID->addItem(QString::number(base_addr+2));

    i2cBus = base_addr;

    connect(i2cID , SIGNAL(currentIndexChanged(int)),this,SLOT(handleI2CselectionChanged(int)));

    slaveLabel = new QLabel("Slave Address(Hex, ex. A5):");
    slaveLabel->setFont(fontlabel);
    slaveLabel->setStyleSheet("QLabel { color : black; }");

    slaveValue = new QLineEdit;
    slaveValue->setInputMask("HH");
    slaveValue->setStyleSheet("QLabel { color : black; }");
    slaveValue->setFont(fontvalue);
    slaveValue->setText("00");
    slave = 0;

    connect(slaveValue, SIGNAL(textChanged(QString)), this, SLOT(slaveChanged(QString)));

    deviceGrid = new QGridLayout;
    deviceGrid->addWidget(i2cIDLabel,1,0);
    deviceGrid->addWidget(i2cID,1,1);

    deviceGrid->addWidget(slaveLabel,2,0);
    deviceGrid->addWidget(slaveValue,2,1);

    deviceLayout = new QHBoxLayout;
    deviceLayout->addLayout(deviceGrid);

    deviceGroup = new QGroupBox("Device");
    deviceGroup->setFont(fontlabel);
    deviceGroup->setLayout(deviceLayout);

    /***********************************************/
    parameterGrid = new QGridLayout;

    offsetLabel = new QLabel("Register Offset:");
    offsetLabel->setFont(fontlabel);
    offsetLabel->setStyleSheet("QLabel { color : black; }");

    offsetValue = new QLineEdit("0");
    offsetValue->setStyleSheet("QLabel { color : black; }");
    offsetValue->setFont(fontvalue);

    connect(offsetValue, SIGNAL(textChanged(QString)), this, SLOT(offsetChanged(QString)));
    offset =0;

    offsetTypeLabel = new QLabel("Offset Type:");
    offsetTypeLabel->setFont(fontlabel);
    offsetTypeLabel->setStyleSheet("QLabel { color : black; }");

    byteRadioButton = new QRadioButton("byte");
    byteRadioButton->setFont(fontvalue);
    byteRadioButton->setStyleSheet("QLabel { color : black; }");

    wordRadioButton = new QRadioButton("word");
    wordRadioButton->setFont(fontvalue);
    wordRadioButton->setStyleSheet("QLabel { color : black; }");

    connect( byteRadioButton, SIGNAL( toggled(bool) ), this, SLOT( byteRadioButtonClicked(bool) ) );
    connect( wordRadioButton, SIGNAL( toggled(bool) ), this, SLOT( wordRadioButtonClicked(bool) ) );

    byteRadioButton->setChecked(1);
    offsetType = 0; /*0: byte, 1:word */

    parameterGrid->addWidget(offsetTypeLabel,2,2);
    parameterGrid->addWidget(offsetLabel,2,0);
    parameterGrid->addWidget(offsetValue,2,1);
    parameterGrid->addWidget(byteRadioButton,2,3);
    parameterGrid->addWidget(wordRadioButton,2,4);

    readlengthLabel = new QLabel;
    readlengthLabel->setText("Read Length");

    readlengthValue = new QLineEdit("0");
    readlengthValue->setStyleSheet("QLabel { color : black; }");
    readlengthValue->setFont(fontvalue);

    connect(readlengthValue, SIGNAL(textChanged(QString)), this, SLOT(readlengthChanged(QString)));
    readlength = 0;

    parameterGrid->addWidget(readlengthLabel,3,0);
    parameterGrid->addWidget(readlengthValue,3,1);


    writelengthLabel = new QLabel;
    writelengthLabel->setText("Write Length");

    writelengthValue = new QLineEdit("0");
    writelengthValue->setStyleSheet("QLabel { color : black; }");
    writelengthValue->setFont(fontvalue);

    connect(writelengthValue, SIGNAL(textChanged(QString)), this, SLOT(writelengthChanged(QString)));
    writelength = 0;

    parameterGrid->addWidget(writelengthLabel,3,2);
    parameterGrid->addWidget(writelengthValue,3,3);

    timingCheckbox = new QCheckBox("timing(0.005 sec)");
    parameterGrid->addWidget(timingCheckbox,3,4);
    timingCheckbox->setChecked(false);
    timing = false;
    connect(timingCheckbox, SIGNAL(clicked(bool)), this, SLOT(timingSelected(bool)));

    writeLabel = new QLabel("Write(Hex):");

    writeValue = new QTextEdit;
    writeValue->setFont(fontvalue);
    writeValue->setStyleSheet("QLabel { color : black; }");
    connect(writeValue, SIGNAL(textChanged()), this, SLOT(getInput()));

    writeButton = new QPushButton("Write");
    connect( writeButton, SIGNAL( clicked() ), this, SLOT( writeClicked() ) );

    writereadCombineButton = new QPushButton("W/R Combined");
    connect( writereadCombineButton, SIGNAL( clicked() ), this, SLOT( writereadClicked() ) );
    writereadCombineButton->setEnabled(false);

    parameterGrid->addWidget(writeLabel,4,0);
    parameterGrid->addWidget(writeValue,5,0,1,4);
    parameterGrid->addWidget(writeButton,5,4);

    readLabel = new QLabel("Read(Hex):");

    readValue = new QTextEdit();
    readValue->setFont(fontvalue);
    readValue->setStyleSheet("QTextEdit { background-color: #BDD8CA; color : black; }");
    readValue->setReadOnly(true);

    readButton = new QPushButton("Read");
    // readButton->setEnabled(false);
    connect( readButton, SIGNAL( clicked() ), this, SLOT( readClicked() ) );

    parameterGrid->addWidget(readLabel,6,0);
    parameterGrid->addWidget(writereadCombineButton,6,4);
    parameterGrid->addWidget(readValue,7,0,1,4);
    parameterGrid->addWidget(readButton,7,4);

    controlGroup = new QGroupBox("Control");
    controlGroup->setFont(fontlabel);
    controlGroup->setLayout(parameterGrid);

    /******************************************************/
    temperatureButton = new QPushButton("Temperature");

    circlewidget = new CircleWidget;
    circlewidget->setAntialiased(true);
    circlewidget->setFloatBased(false);

    connect( temperatureButton, SIGNAL( clicked() ), this, SLOT( temperatureClicked() ) );
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutTimer()));

    demoGrid = new QGridLayout;
    demoGrid->addWidget(temperatureButton,1,0);
    demoGrid->addWidget(circlewidget, 2, 0);

    demoGroup = new QGroupBox("Demo");
    demoGroup->setFont(fontlabel);
    demoGroup->setLayout(demoGrid);

    grid = new QGridLayout;
    grid->addWidget(protocolGroup,1,0);
    grid->addWidget(deviceGroup,1,1);
    grid->addWidget(controlGroup,2,0);
    grid->addWidget(demoGroup,2,1);
    setLayout(grid);
}
void i2c::readWriteByteRadioButtonClicked(bool checked)
{
    if(checked)
    {
        protocol  = 0;
        readButton->setEnabled(true);
        writeButton->setEnabled(true);
        writereadCombineButton->setEnabled(false);
    }
}
void i2c::readWriteBlockRadioButtonClicked(bool checked)
{
    if(checked)
    {
        protocol  = 1;
        readButton->setEnabled(true);
        writeButton->setEnabled(true);
        writereadCombineButton->setEnabled(false);
    }
}
void i2c::readWriteCombineRadioButtonClicked(bool checked)
{
    if(checked)
    {
        protocol  = 2;
        readButton->setEnabled(false);
        writeButton->setEnabled(false);
        writereadCombineButton->setEnabled(true);
    }
}
void i2c::timingSelected(bool checked)
{
    if(checked)
        timing = true;
}
void i2c::handleI2CselectionChanged(int index)
{
    i2cBus = i2cID->itemText(index).toInt();
}
void i2c::slaveChanged(QString text)
{
    slave = strtol(text.toStdString().c_str(),0,16);
}
void i2c::offsetChanged(QString text)
{
    offset = text.toInt();
}
void i2c::readlengthChanged(QString text)
{
    readlength = text.toInt();
}
void i2c::writelengthChanged(QString text)
{
    writelength = text.toInt();
}
void i2c::byteRadioButtonClicked(bool checked)
{
    if(checked)
        offsetType  = 0;
}
void i2c::wordRadioButtonClicked(bool checked)
{
    if(checked)
        offsetType  = 1;
}
void i2c::readClicked()
{
    unsigned char *TmpStrBuf;
    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;
    int tempLength;

    if (protocol == 0) //read byte
    {
        TmpStrBuf = (unsigned char*) malloc(sizeof(unsigned char)*(1+1));
        tempLength = 1;
    }
    else
    {
        TmpStrBuf = (unsigned char*) malloc(sizeof(unsigned char)*(readlength+1));
        tempLength = readlength;
    }

    int index = 0;
    while (tempLength)
    {
        if (tempLength < 32)
        {

            if (offsetType == 1)
                StatusCode=EApiI2CReadTransfer(i2cBus, slave, EAPI_I2C_ENC_EXT_CMD(offset+index),TmpStrBuf + index, tempLength, tempLength);
            else
                StatusCode=EApiI2CReadTransfer(i2cBus, slave, EAPI_I2C_ENC_STD_CMD(offset+index),TmpStrBuf + index, tempLength, tempLength);
            tempLength = 0;
        }
        else
        {
            if (offsetType == 1)
                StatusCode=EApiI2CReadTransfer(i2cBus, slave, EAPI_I2C_ENC_EXT_CMD(offset+index),TmpStrBuf + index, 32, 32);
            else
                StatusCode=EApiI2CReadTransfer(i2cBus, slave, EAPI_I2C_ENC_STD_CMD(offset+index),TmpStrBuf + index, 32, 32);

            tempLength -= 32;
            index += 32;
        }
    }

    if(EAPI_TEST_SUCCESS(StatusCode))
    {
        if (protocol == 0) //read byte
            tempLength = 1;
        else
            tempLength = readlength;

        QString tokens;
        for(int i = 0; i < tempLength ;i ++) {
            uint8_t value = TmpStrBuf[i] / 16;
            if (value ==0 || value <=9)
                tokens.append(48+value);
            else
                tokens.append(65+(value%10));

            value = TmpStrBuf[i] % 16;
            if (value ==0 || value <=9)
                tokens.append(48+value);
            else
                tokens.append(65+(value%10));

            tokens.append(" ");
        }
        readValue->setText(tokens);
    }
    else
        readValue->setText("Error!");

    free(TmpStrBuf);
}
void i2c::writeClicked()
{
    unsigned int size = 0;
    uint8_t *writestr;
    unsigned int originsize;
    unsigned int i = 0 , j =0;
    char hex[2];
    uint8_t num;

    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;

    originsize = input.size();

    if (originsize % 2 == 0)
        size = originsize / 2 ;
    else
        size = (originsize /2) + 1;

    writestr = (uint8_t*) malloc(sizeof(uint8_t)*(size));

    j = 0;
    for (i = 0; i < originsize ; i+=2)
    {
        if (((i+1) == originsize) && (originsize % 2 != 0))
        {
            hex[0] = (char)'0';
            hex[1] = input.at(i).toLatin1();
        }
        else
        {
            hex[0] = input.at(i).toLatin1();
            hex[1] = input.at(i+1).toLatin1();
        }

        num = (int)strtol(hex, NULL, 16);
        if (j < size)
        {
            writestr[j] = num;
            j++;
        }
    }

     int tempLength = size;

    if (protocol == 0 && size > 0) //write byte
    {
        tempLength = 1;
    }
    else
    {
        if (writelength > size)
            tempLength = size;
        else
            tempLength = writelength;
    }

    int index = 0;
    while (tempLength)
    {
        if (timing) // write one byte
        {
            if (offsetType == 1)
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_EXT_CMD(offset+index),writestr + index, 1);
            else
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_STD_CMD(offset+index),writestr + index, 1);
            tempLength--;
            index++;
            usleep(5000);
        }
        else if (tempLength < 32)
        {

            if (offsetType == 1)
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_EXT_CMD(offset+index),writestr + index, tempLength);
            else
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_STD_CMD(offset+index),writestr + index, tempLength);
            tempLength = 0;
        }
        else
        {
            if (offsetType == 1)
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_EXT_CMD(offset+index),writestr + index, 32);
            else
                StatusCode=EApiI2CWriteTransfer(i2cBus, slave, EAPI_I2C_ENC_STD_CMD(offset+index),writestr + index, 32);

            tempLength -= 32;
            index += 32;
        }
    }

    if(EAPI_TEST_SUCCESS(StatusCode))
        writeValue->setText("Successful");
    else
        writeValue->setText("Error!");
}
void i2c::writereadClicked()
{
    unsigned int size = 0;
    uint8_t *writestr;
    uint8_t *readstr;
    unsigned int originsize;
    unsigned int i = 0 , j =0;
    char hex[2];
    uint8_t num;

    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;

    originsize = input.size();

    if (originsize % 2 == 0)
        size = originsize / 2 ;
    else
        size = (originsize /2) + 1;

    writestr = (uint8_t*) malloc(sizeof(uint8_t)*(size));

    j = 0;
    for (i = 0; i < originsize ; i+=2)
    {
        if (((i+1) == originsize) && (originsize % 2 != 0))
        {
            hex[0] = (char)'0';
            hex[1] = input.at(i).toLatin1();
        }
        else
        {
            hex[0] = input.at(i).toLatin1();
            hex[1] = input.at(i+1).toLatin1();
        }

        num = (int)strtol(hex, NULL, 16);
        if (j < size)
        {
            writestr[j] = num;
            j++;
        }
    }

    int writetempLength = size;
    if (writelength > size)
        writetempLength = size;
    else
        writetempLength = writelength;

    readstr = (uint8_t*) malloc(sizeof(uint8_t)*(readlength+1));

    StatusCode = EApiI2CWriteReadRaw(i2cBus, slave, writestr , writetempLength+1, readstr ,  readlength+1  ,  readlength+1);

    if(EAPI_TEST_SUCCESS(StatusCode))
    {
        writeValue->setText("Successful");

        QString tokens;
        for(i = 0; i < readlength ;i ++) {
            uint8_t value = readstr[i] / 16;
            if (value ==0 || value <=9)
                tokens.append(48+value);
            else
                tokens.append(65+(value%10));

            value = readstr[i] % 16;
            if (value ==0 || value <=9)
                tokens.append(48+value);
            else
                tokens.append(65+(value%10));

            tokens.append(" ");
        }
        readValue->setText(tokens);
    }
    else
    {
        writeValue->setText("Error!");
        readValue->setText("Error!");
    }

    free(readstr);
    free(writestr);
}
void i2c::temperatureClicked()
{
    if (!timer->isActive())
    {
        temperatureButton->setText("stop");
        timer->start(1000);
    }
    else
    {
        temperatureButton->setText("Temperature");
        circlewidget->setDiameter(0);
        timer->stop();
    }
}
void i2c::timeoutTimer()
{
    unsigned char TmpStrBuf;
    EApiStatus_t StatusCode;
    StatusCode=EApiI2CReadTransfer(base_addr, 0x48, EAPI_I2C_ENC_STD_CMD(0),&TmpStrBuf, 1, 1);

    if(EAPI_TEST_SUCCESS(StatusCode))
    {
        circlewidget->setDiameter((int)TmpStrBuf);
    }
    else
        circlewidget->setDiameter(0);
    update();
}
void i2c::getInput()
{
    if ((writeValue->toPlainText() == "Successful") ||
        (writeValue->toPlainText() == "Error!"))
    {
        input.clear();
        return;
    }
    input = writeValue->toPlainText().toUpper();
    input.replace(QRegExp("[^A-F0-9]"), "");
    QStringList tokens;
    for(int i = 0; i < input.length(); i += 2) {
        tokens << input.mid(i, 2);
    }
    writeValue->blockSignals(true);
    writeValue->setText(tokens.join(" "));
    writeValue->moveCursor(QTextCursor::EndOfBlock);
    writeValue->blockSignals(false);
}

/**************************************/
struct i2c_adap* i2c::more_adapters(struct i2c_adap *adapters, int n)
{
    struct i2c_adap *new_adapters;

    new_adapters = (struct i2c_adap*)realloc(adapters, (n + BUNCH) * sizeof(struct i2c_adap));
    if (!new_adapters) {
        free_adapters(adapters);
        return NULL;
    }
    memset(new_adapters + n, 0, BUNCH * sizeof(struct i2c_adap));

    return new_adapters;
}

struct i2c_adap* i2c::gather_i2c_busses(void)
{
    char s[120];
    struct dirent *de, *dde;
    DIR *dir, *ddir;
    FILE *f;
    char fstype[NAME_MAX], sysfs[NAME_MAX], n[NAME_MAX];
    int foundsysfs = 0;
    int count=0;
    struct i2c_adap *adapters;

    adapters = (struct i2c_adap*)calloc(BUNCH, sizeof(struct i2c_adap));
    if (!adapters)
        return NULL;
    /* look in sysfs */
    /* First figure out where sysfs was mounted */
    if ((f = fopen("/proc/mounts", "r")) == NULL) {
        goto done;
    }
    while (fgets(n, NAME_MAX, f)) {
        sscanf(n, "%*[^ ] %[^ ] %[^ ] %*s\n", sysfs, fstype);
        if (strcasecmp(fstype, "sysfs") == 0) {
            foundsysfs++;
            break;
        }
    }
    fclose(f);
    if (! foundsysfs) {
        goto done;
    }
    /* Bus numbers in i2c-adapter don't necessarily match those in
       i2c-dev and what we really care about are the i2c-dev numbers.
       Unfortunately the names are harder to get in i2c-dev */
    strcat(sysfs, "/class/i2c-dev");
    if(!(dir = opendir(sysfs)))
        goto done;
    /* go through the busses */
    while ((de = readdir(dir)) != NULL) {
        if (!strcmp(de->d_name, "."))
            continue;
        if (!strcmp(de->d_name, ".."))
            continue;

        /* this should work for kernels 2.6.5 or higher and */
        /* is preferred because is unambiguous */
        sprintf(n, "%s/%s/name", sysfs, de->d_name);
        f = fopen(n, "r");
        /* this seems to work for ISA */
        if(f == NULL) {
            sprintf(n, "%s/%s/device/name", sysfs, de->d_name);
            f = fopen(n, "r");
        }
        /* non-ISA is much harder */
        /* and this won't find the correct bus name if a driver
           has more than one bus */
        if(f == NULL) {
            sprintf(n, "%s/%s/device", sysfs, de->d_name);
            if(!(ddir = opendir(n)))
                continue;
            while ((dde = readdir(ddir)) != NULL) {
                if (!strcmp(dde->d_name, "."))
                    continue;
                if (!strcmp(dde->d_name, ".."))
                    continue;
                if ((!strncmp(dde->d_name, "i2c-", 4))) {
                    sprintf(n, "%s/%s/device/%s/name",
                            sysfs, de->d_name, dde->d_name);
                    if((f = fopen(n, "r")))
                        goto found;
                }
            }
        }

found:
        if (f != NULL) {
            int i2cbus;
            char *px;

            px = fgets(s, 120, f);
            fclose(f);
            if (!px) {
                fprintf(stderr, "%s: read error\n", n);
                continue;
            }
            if ((px = strchr(s, '\n')) != NULL)
                *px = 0;
            if (!sscanf(de->d_name, "i2c-%d", &i2cbus))
                continue;

            if ((count + 1) % BUNCH == 0) {
                /* We need more space */
                adapters = more_adapters(adapters, count + 1);
                if (!adapters)
                    return NULL;
            }


            adapters[count].nr = i2cbus;
            adapters[count].name = strdup(s);
            if (adapters[count].name == NULL) {
                free_adapters(adapters);
                return NULL;
            }
            count++;
        }
    }
    closedir(dir);

done:
    return adapters;
}

void i2c::free_adapters(struct i2c_adap *adapters)
{
    int i;

    for (i = 0; adapters[i].name; i++)
        free(adapters[i].name);
    free(adapters);
}

int i2c::find_eeprom(void)
{
    struct i2c_adap *adapters = NULL;
    int count;
    int result = -1;
    adapters = gather_i2c_busses();
    if (adapters == NULL)
    {
        fprintf(stderr, "Error: Out of memory!\n");
        return result;
    }
    for (count = 0; adapters[count].name; count++) {
        if (!strncmp(adapters[count].name, I2C_DMEC,8))
        {
            result = adapters[count].nr +1;
            break;
        }
    }
    free_adapters(adapters);
    return result;
}


