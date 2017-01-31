#include "storage.h"
#include <EApi.h>

storage::storage(QWidget *parent)
    :QWidget(parent)
{
    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setPointSize(11);

    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;
    pStorgeSize = 0 ;
    uint32_t pBlockLen = 0;
    offset = 0 ;
    length = 0;
    char temp[300];

    storageSize = new QLabel;
    storageSize->setFont(fontvalue);
    storageSize->setStyleSheet("QLabel { color : black; }");

    storageType = new QLabel;
    storageType->setText( "<span style='font-size:11pt; font-weight:600; color:black;'>Selected Area: </span><span style='font-size:11pt; font-weight:normal; color:black;'>Standard Storage Area</span>" );

    StatusCode=EApiStorageCap(EAPI_ID_STORAGE_STD,&pStorgeSize,&pBlockLen);
    if(EAPI_TEST_SUCCESS(StatusCode))
    {
        definedStorage = true;
        sprintf(temp,"<span style='font-size:11pt; font-weight:600; color:black;'>Area Size: </span><span style='font-size:11pt; font-weight:normal; color:black;'>%d bytes</span>",pStorgeSize);
        storageSize->setText(temp);
    }
    else
    {
        definedStorage = false;
        storageSize->setText( "<span style='font-size:11pt; font-weight:600; color:black;'>Area Size: </span><span style='font-size:11pt; font-weight:normal; color:black;'>No defined user storage area</span>" );
    }

    infoLayout = new QVBoxLayout;
    infoLayout->addWidget(storageType);
    infoLayout->addWidget(storageSize);

    infoGroup = new QGroupBox(tr("Information"));
    infoGroup->setFont(fontlabel);
    infoGroup->setLayout(infoLayout);
    /*************************************************/
    bytegrid = new QGridLayout;


    offsetLabel = new QLabel("Offset:");
    offsetLabel->setFont(fontlabel);
    offsetLabel->setStyleSheet("QLabel { color : black; }");

    offsetValue = new QLineEdit("0");
    offsetValue->setStyleSheet("QLabel { color : black; }");
    offsetValue->setFont(fontvalue);
    offsetValue->setFixedWidth(50);

    connect(offsetValue, SIGNAL(textChanged(QString)), this, SLOT(offsetChanged(QString)));

    bytegrid->addWidget(offsetLabel,1,0);
    bytegrid->addWidget(offsetValue,1,1);

    lengthLabel = new QLabel;
    if (pStorgeSize > 0)
        sprintf(temp,"Length(1-%d):",pStorgeSize);
    else
        sprintf(temp,"Length(only 0):");
    lengthLabel->setText(temp);

    lengthValue = new QLineEdit("0");
    lengthValue->setStyleSheet("QLabel { color : black; }");
    lengthValue->setFont(fontvalue);
    lengthValue->setFixedWidth(50);

    connect(lengthValue, SIGNAL(textChanged(QString)), this, SLOT(lengthChanged(QString)));

    bytegrid->addWidget(lengthLabel,2,0);
    bytegrid->addWidget(lengthValue,2,1);


    writeLabel = new QLabel("Write:");

    writeValue = new QTextEdit;
    writeValue->setFont(fontvalue);
    writeValue->setStyleSheet("QLabel { color : black; }");
    connect(writeValue, SIGNAL(textChanged()), this, SLOT(getInput()));

    writeButton = new QPushButton(tr("Write"));
    connect( writeButton, SIGNAL( clicked() ), this, SLOT( writeClicked() ) );
    if (definedStorage == false)
        writeButton->setEnabled(false);

    bytegrid->addWidget(writeLabel,3,0);
    bytegrid->addWidget(writeValue,3,1);
    bytegrid->addWidget(writeButton,3,2);

    readLabel = new QLabel("Read:");

    readValue = new QTextEdit();
    readValue->setFont(fontvalue);
    readValue->setStyleSheet("QTextEdit { background-color: #BDD8CA; color : black; }");
    readValue->setReadOnly(true);

    readButton = new QPushButton(tr("Read"));
    if (definedStorage == false)
        readButton->setEnabled(false);
    connect( readButton, SIGNAL( clicked() ), this, SLOT( readClicked() ) );

    bytegrid->addWidget(readLabel,4,0);
    bytegrid->addWidget(readValue,4,1);
    bytegrid->addWidget(readButton,4,2);


    byteGroup = new QGroupBox(tr("Read/Write Data"));
    byteGroup->setFont(fontlabel);
    byteGroup->setLayout(bytegrid);

    grid = new QGridLayout;
    grid->addWidget(infoGroup,0,0,1,2);
    grid->addWidget(byteGroup,1,0,1,2);
    setLayout(grid);
}
void storage::readClicked()
{
    char *TmpStrBuf;

    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;

    if (definedStorage)
    {
        TmpStrBuf = (char*) malloc(sizeof(char)*(pStorgeSize+1));

        StatusCode=EApiStorageAreaRead(EAPI_ID_STORAGE_STD,offset,TmpStrBuf,pStorgeSize, length);
        if(EAPI_TEST_SUCCESS(StatusCode))
        {
            QString tokens;
            for(unsigned int i = 0; i < length ;i ++) {
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
    else
        readValue->setText("Error! No defined user storage area!");
}
void storage::writeClicked()
{
    unsigned int size = 0;
    uint8_t *writestr;
    unsigned int originsize;
    unsigned int i = 0 , j =0;
    char hex[2];
    uint8_t num;

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

    if (length > size)
        tempLength = size;
    else
        tempLength = length;

    EApiStatus_t StatusCode;
    StatusCode=EApiStorageAreaWrite(EAPI_ID_STORAGE_STD,offset,writestr,tempLength);
    if(EAPI_TEST_SUCCESS(StatusCode))
        writeValue->setText("Successful");
    else
        writeValue->setText("Error!");

}
void storage::offsetChanged(QString text)
{
    char temp[50];

    offset = text.toInt();

    if ((pStorgeSize - offset) > 0)
        sprintf(temp,"Length(1-%d):",pStorgeSize - offset);
    else
        sprintf(temp,"Length(only 0):");
    lengthLabel->setText(temp);
}
void storage::lengthChanged(QString text)
{
    length = text.toInt();
}
void storage::getInput()
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
