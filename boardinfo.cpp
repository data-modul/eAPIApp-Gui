#include "boardinfo.h"

char CompressedAsciiLookup[]={
  ' ', 'A', 'B', 'C',
  'D', 'E', 'F', 'G',
  'H', 'I', 'J', 'K',
  'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S',
  'T', 'U', 'V', 'W',
  'X', 'Y', 'Z',
  /* Invalid Values */
  '*', '*', '*', '*', '*'
};

const EApiId_t EApiStrings[]={
    EAPI_ID_BOARD_MANUFACTURER_STR  ,
    EAPI_ID_BOARD_NAME_STR          ,
    EAPI_DMO_ID_BOARD_ID_STR        ,
    EAPI_ID_BOARD_SERIAL_STR        ,
    EAPI_ID_BOARD_BIOS_REVISION_STR ,
    EAPI_ID_BOARD_PLATFORM_TYPE_STR ,
    EAPI_ID_BOARD_HW_REVISION_STR ,
    EAPI_DMO_ID_BOARD_MANUFACTURING_DATE_STR
};


const EApiId_t EApiValues[]={
    EAPI_ID_GET_EAPI_SPEC_VERSION,
    EAPI_ID_BOARD_PNPID_VAL
};


int
EApiAHCreatePNPIDString(
    __IN  uint32_t        Value     , /* Input Value to be interpreted */
    __OUT char * const   pString   , /* Pointer To String pBuffer */
    __IN  const uint32_t  StrBufLen   /* String pBuffer Length */
    )
{
  int cnt;
  unsigned short PNPID=(unsigned short)EAPI_BYTE_SWAP_W(Value);
  if(pString == NULL)
      return -1;
  if(StrBufLen<4){
    return -1;
  }
  if(PNPID&(1<<15)){
    return -1;
  }
  for(cnt=0; cnt < 3; cnt++){
    pString[2 - cnt]=CompressedAsciiLookup[(PNPID>>(cnt*5))&0x1F];
  }
  pString[cnt]=0;
    return 0;
}


boardInfo::boardInfo(QWidget *parent)
    :QWidget(parent)
{
    QFont fontlabel;
    fontlabel.setBold(true);
    fontlabel.setPointSize(11);

    QFont fontvalue;
    fontvalue.setPointSize(11);

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2);

    manufacturerNameLabel  = new QLabel("Board Manufacturer:");
    manufacturerNameLabel->setFont(fontlabel);
    manufacturerNameLabel->setAlignment(Qt::AlignLeft);
    manufacturerNameLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    manufacturerNameLabel->setSizePolicy(spLeft);

    manufacturerNameValueLabel  = new QLabel;
    manufacturerNameValueLabel->setFont(fontvalue);
    manufacturerNameValueLabel->setAlignment(Qt::AlignLeft);
    manufacturerNameValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    manufacturerNameValueLabel->setSizePolicy(spRight);

    manufacturerlayout=new QHBoxLayout;
    manufacturerlayout->setSpacing(1);
    manufacturerlayout->addWidget(manufacturerNameLabel);
    manufacturerlayout->addWidget(manufacturerNameValueLabel);



    pnpLabel      = new QLabel("Manufacturer PNP ID:");
    pnpLabel->setFont(fontlabel);
    pnpLabel->setAlignment(Qt::AlignLeft);
    pnpLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    pnpLabel->setSizePolicy(spLeft);

    pnpValueLabel = new QLabel;
    pnpValueLabel->setFont(fontvalue);
    pnpValueLabel->setAlignment(Qt::AlignLeft);
    pnpValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    pnpValueLabel->setSizePolicy(spRight);

    pnplayout=new QHBoxLayout;
    pnplayout->setSpacing(1);
    pnplayout->addWidget(pnpLabel);
    pnplayout->addWidget(pnpValueLabel);

    boardNameLabel         = new QLabel("Board Name:");
    boardNameLabel->setFont(fontlabel);
    boardNameLabel->setAlignment(Qt::AlignLeft);
    boardNameLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardNameLabel->setSizePolicy(spLeft);

    boardNameValueLabel    = new QLabel;
    boardNameValueLabel->setFont(fontvalue);
    boardNameValueLabel->setAlignment(Qt::AlignLeft);
    boardNameValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardNameValueLabel->setSizePolicy(spRight);

    boardNamelayout=new QHBoxLayout;
    boardNamelayout->setSpacing(1);
    boardNamelayout->addWidget(boardNameLabel);
    boardNamelayout->addWidget(boardNameValueLabel);

    boardIDLabel           = new QLabel("Board ID:");
    boardIDLabel->setFont(fontlabel);
    boardIDLabel->setAlignment(Qt::AlignLeft);
    boardIDLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardIDLabel->setSizePolicy(spLeft);

    boardIDValueLabel      = new QLabel;
    boardIDValueLabel->setFont(fontvalue);
    boardIDValueLabel->setAlignment(Qt::AlignLeft);
    boardIDValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardIDValueLabel->setSizePolicy(spRight);

    boardIDlayout=new QHBoxLayout;
    boardIDlayout->setSpacing(1);
    boardIDlayout->addWidget(boardIDLabel);
    boardIDlayout->addWidget(boardIDValueLabel);

    boardSNLabel           = new QLabel("Board Serial-Number:");
    boardSNLabel->setFont(fontlabel);
    boardSNLabel->setAlignment(Qt::AlignLeft);
    boardSNLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardSNLabel->setSizePolicy(spLeft);

    boardSNValueLabel           = new QLabel;
    boardSNValueLabel->setFont(fontvalue);
    boardSNValueLabel->setAlignment(Qt::AlignLeft);
    boardSNValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    boardSNValueLabel->setSizePolicy(spRight);

    boardSNlayout = new QHBoxLayout;
    boardSNlayout->setSpacing(1);
    boardSNlayout->addWidget(boardSNLabel);
    boardSNlayout->addWidget(boardSNValueLabel);

    biosRevisionLabel      = new QLabel("BIOS Revision:");
    biosRevisionLabel->setFont(fontlabel);
    biosRevisionLabel->setAlignment(Qt::AlignLeft);
    biosRevisionLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    biosRevisionLabel->setSizePolicy(spLeft);

    biosRevisionValueLabel = new QLabel;
    biosRevisionValueLabel->setFont(fontvalue);
    biosRevisionValueLabel->setAlignment(Qt::AlignLeft);
    biosRevisionValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    biosRevisionValueLabel->setSizePolicy(spRight);

    biosRevisionlayout=new QHBoxLayout;
    biosRevisionlayout->setSpacing(1);
    biosRevisionlayout->addWidget(biosRevisionLabel);
    biosRevisionlayout->addWidget(biosRevisionValueLabel);

    platformTypeLabel      = new QLabel("Platform Type:");
    platformTypeLabel->setFont(fontlabel);
    platformTypeLabel->setAlignment(Qt::AlignLeft);
    platformTypeLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    platformTypeLabel->setSizePolicy(spLeft);

    platformTypeValueLabel = new QLabel;
    platformTypeValueLabel->setFont(fontvalue);
    platformTypeValueLabel->setAlignment(Qt::AlignLeft);
    platformTypeValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    platformTypeValueLabel->setSizePolicy(spRight);

    platformTypelayout=new QHBoxLayout;
    platformTypelayout->setSpacing(1);
    platformTypelayout->addWidget(platformTypeLabel);
    platformTypelayout->addWidget(platformTypeValueLabel);

    HWRevisionLabel      = new QLabel("HW Revisio:n");
    HWRevisionLabel->setFont(fontlabel);
    HWRevisionLabel->setAlignment(Qt::AlignLeft);
    HWRevisionLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    HWRevisionLabel->setSizePolicy(spLeft);

    HWRevisionValueLabel = new QLabel;
    HWRevisionValueLabel->setFont(fontvalue);
    HWRevisionValueLabel->setAlignment(Qt::AlignLeft);
    HWRevisionValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    HWRevisionValueLabel->setSizePolicy(spRight);

    HWRevisionlayout=new QHBoxLayout;
    HWRevisionlayout->setSpacing(1);
    HWRevisionlayout->addWidget(HWRevisionLabel);
    HWRevisionlayout->addWidget(HWRevisionValueLabel);

    manufacturDateLabel      = new QLabel("Manufacturing Date:");
    manufacturDateLabel->setFont(fontlabel);
    manufacturDateLabel->setAlignment(Qt::AlignLeft);
    manufacturDateLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    manufacturDateLabel->setSizePolicy(spLeft);

    manufacturDateValueLabel = new QLabel;
    manufacturDateValueLabel->setFont(fontvalue);
    manufacturDateValueLabel->setAlignment(Qt::AlignLeft);
    manufacturDateValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    manufacturDateValueLabel->setSizePolicy(spRight);

    manufacturDatelayout=new QHBoxLayout;
    manufacturDatelayout->setSpacing(1);
    manufacturDatelayout->addWidget(manufacturDateLabel);
    manufacturDatelayout->addWidget(manufacturDateValueLabel);

    specRevisionLabel      = new QLabel("EAPI Specification Version:");
    specRevisionLabel->setFont(fontlabel);
    specRevisionLabel->setAlignment(Qt::AlignLeft);
    specRevisionLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    specRevisionLabel->setSizePolicy(spLeft);

    specRevisionValueLabel = new QLabel;
    specRevisionValueLabel->setFont(fontvalue);
    specRevisionValueLabel->setAlignment(Qt::AlignLeft);
    specRevisionValueLabel->setStyleSheet("QLabel { color : #143850; border: 1px solid #999A9B }");
    specRevisionValueLabel->setSizePolicy(spRight);

    specRevisionlayout=new QHBoxLayout;
    specRevisionlayout->setSpacing(1);
    specRevisionlayout->addWidget(specRevisionLabel);
    specRevisionlayout->addWidget(specRevisionValueLabel);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addLayout(manufacturerlayout);
    mainLayout->addLayout(pnplayout);
    mainLayout->addLayout(boardNamelayout);
    mainLayout->addLayout(boardIDlayout);
    mainLayout->addLayout(boardSNlayout);
    mainLayout->addLayout(biosRevisionlayout);
    mainLayout->addLayout(platformTypelayout);
    mainLayout->addLayout(HWRevisionlayout);
    mainLayout->addLayout(manufacturDatelayout);
    mainLayout->addLayout(specRevisionlayout);

    group = new QGroupBox("Information");
    group->setFont(fontlabel);
    group->setLayout(mainLayout);

    grid = new QGridLayout;
    grid->setHorizontalSpacing(0);
    grid->addWidget(group,0,0,1,2);
    grid->setRowStretch(1,1);
    setLayout(grid);

    fill();
}

void boardInfo::fill(void)
{
    EApiStatus_t StatusCode = EAPI_STATUS_SUCCESS;
    char  *pBuffer;
    uint32_t pBufferLen;
    unsigned i=0;
    uint32_t Value;

    pBufferLen = 100;
    pBuffer=(char *)malloc((pBufferLen) * sizeof(char));

    unsigned int size = sizeof(EApiStrings)/(sizeof(EApiStrings[0]));
    for(i=0;i<size;i++){
        pBufferLen = 100;
        StatusCode = EApiBoardGetStringA(EApiStrings[i], pBuffer,&pBufferLen);
        if (StatusCode == EAPI_STATUS_SUCCESS)
        {
            switch(EApiStrings[i])
            {
            case EAPI_ID_BOARD_MANUFACTURER_STR:
                manufacturerNameValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_NAME_STR:
                boardNameValueLabel->setText(pBuffer);
                break;
            case EAPI_DMO_ID_BOARD_ID_STR:
                boardIDValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_SERIAL_STR:
                boardSNValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_BIOS_REVISION_STR:
                biosRevisionValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_PLATFORM_TYPE_STR:
                platformTypeValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_HW_REVISION_STR:
                HWRevisionValueLabel->setText(pBuffer);
                break;
            case EAPI_DMO_ID_BOARD_MANUFACTURING_DATE_STR:
                manufacturDateValueLabel->setText(pBuffer);
                break;
            }
        }
        else
        {
            switch(EApiStrings[i])
            {
            case EAPI_ID_BOARD_MANUFACTURER_STR:
                manufacturerNameValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_NAME_STR:
                boardNameValueLabel->setText("Unsupported");
                break;
            case EAPI_DMO_ID_BOARD_ID_STR:
                boardIDValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_SERIAL_STR:
                boardSNValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_BIOS_REVISION_STR:
                biosRevisionValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_PLATFORM_TYPE_STR:
                platformTypeValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_HW_REVISION_STR:
                HWRevisionValueLabel->setText("Unsupported");
                break;
            case EAPI_DMO_ID_BOARD_MANUFACTURING_DATE_STR:
                manufacturDateValueLabel->setText("Unsupported");
                break;
            }
        }
    }

    size = sizeof(EApiValues)/(sizeof(EApiValues[0]));
    for(i=0;i<size;i++){
        StatusCode = EApiBoardGetValue(EApiValues[i],&Value);
        if (StatusCode == EAPI_STATUS_SUCCESS)
        {
            switch(EApiValues[i])
            {
            case EAPI_ID_GET_EAPI_SPEC_VERSION:
                snprintf(pBuffer, sizeof(pBufferLen),"%u.%u",EAPI_VER_GET_VER(Value),EAPI_VER_GET_REV(Value));
                specRevisionValueLabel->setText(pBuffer);
                break;
            case EAPI_ID_BOARD_PNPID_VAL:
                EApiAHCreatePNPIDString(Value,pBuffer,pBufferLen);
                pnpValueLabel->setText(pBuffer);
                break;
            }
        }
        else
        {
            switch(EApiValues[i])
            {
            case EAPI_ID_GET_EAPI_SPEC_VERSION:
                specRevisionValueLabel->setText("Unsupported");
                break;
            case EAPI_ID_BOARD_PNPID_VAL:
                pnpValueLabel->setText("Unsupported");
                break;
            }
        }
    }
    free(pBuffer);
}
