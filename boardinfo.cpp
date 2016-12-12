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

    manufacturerNameLabel  = new QLabel(tr("Board Manufacturer:"));
    manufacturerNameLabel->setFont(fontlabel);
    manufacturerNameLabel->setStyleSheet("QLabel { background-color : #F3C11B; color : black; border: 1px solid white }");
    manufacturerNameValueLabel  = new QLabel;
    manufacturerNameValueLabel->setFont(fontvalue);
    manufacturerNameValueLabel->setStyleSheet("QLabel { background-color : #F9E08D; color : black; border: 1px solid white }");
    manufacturerlayout=new QHBoxLayout;
    manufacturerlayout->addWidget(manufacturerNameLabel);
    manufacturerlayout->addWidget(manufacturerNameValueLabel);

    pnpLabel      = new QLabel(tr("Manufacturer PNP ID:"));
    pnpLabel->setFont(fontlabel);
    pnpLabel->setStyleSheet("QLabel { background-color : #DCDCDC; color : black; border: 1px solid white }");
    pnpValueLabel = new QLabel;
    pnpValueLabel->setFont(fontvalue);
    pnpValueLabel->setStyleSheet("QLabel { background-color : #F5F5F5; color : black; border: 1px solid white }");
    pnplayout=new QHBoxLayout;
    pnplayout->addWidget(pnpLabel);
    pnplayout->addWidget(pnpValueLabel);

    boardNameLabel         = new QLabel(tr("Board Name:"));
    boardNameLabel->setFont(fontlabel);
    boardNameLabel->setStyleSheet("QLabel { background-color : #F2BB05; color : black; border: 1px solid white }");
    boardNameValueLabel    = new QLabel;
    boardNameValueLabel->setFont(fontvalue);
    boardNameValueLabel->setStyleSheet("QLabel { background-color : #F9E08D; color : black; border: 1px solid white }");
    boardNamelayout=new QHBoxLayout;
    boardNamelayout->addWidget(boardNameLabel);
    boardNamelayout->addWidget(boardNameValueLabel);

    boardIDLabel           = new QLabel(tr("Board ID:"));
    boardIDLabel->setFont(fontlabel);
    boardIDLabel->setStyleSheet("QLabel { background-color : #DCDCDC; color : black; border: 1px solid white }");
    boardIDValueLabel      = new QLabel;
    boardIDValueLabel->setFont(fontvalue);
    boardIDValueLabel->setStyleSheet("QLabel { background-color : #F5F5F5; color : black; border: 1px solid white }");
    boardIDlayout=new QHBoxLayout;
    boardIDlayout->addWidget(boardIDLabel);
    boardIDlayout->addWidget(boardIDValueLabel);

    boardSNLabel           = new QLabel(tr("Board Serial-Number:"));
    boardSNLabel->setFont(fontlabel);
    boardSNLabel->setStyleSheet("QLabel { background-color : #F2BB05; color : black; border: 1px solid white }");
    boardSNValueLabel           = new QLabel;
    boardSNValueLabel->setFont(fontvalue);
    boardSNValueLabel->setStyleSheet("QLabel { background-color : #F9E08D; color : black; border: 1px solid white }");
    boardSNlayout = new QHBoxLayout;
    boardSNlayout->addWidget(boardSNLabel);
    boardSNlayout->addWidget(boardSNValueLabel);

    biosRevisionLabel      = new QLabel(tr("BIOS Revision:"));
    biosRevisionLabel->setFont(fontlabel);
    biosRevisionLabel->setStyleSheet("QLabel { background-color : #DCDCDC; color : black; border: 1px solid white }");
    biosRevisionValueLabel = new QLabel;
    biosRevisionValueLabel->setFont(fontvalue);
    biosRevisionValueLabel->setStyleSheet("QLabel { background-color : #F5F5F5; color : black; border: 1px solid white }");
    biosRevisionlayout=new QHBoxLayout;
    biosRevisionlayout->addWidget(biosRevisionLabel);
    biosRevisionlayout->addWidget(biosRevisionValueLabel);

    platformTypeLabel      = new QLabel(tr("Platform Type:"));
    platformTypeLabel->setFont(fontlabel);
    platformTypeLabel->setStyleSheet("QLabel { background-color : #F2BB05; color : black; border: 1px solid white }");
    platformTypeValueLabel = new QLabel;
    platformTypeValueLabel->setFont(fontvalue);
    platformTypeValueLabel->setStyleSheet("QLabel { background-color : #F9E08D; color : black; border: 1px solid white }");
    platformTypelayout=new QHBoxLayout;
    platformTypelayout->addWidget(platformTypeLabel);
    platformTypelayout->addWidget(platformTypeValueLabel);

    HWRevisionLabel      = new QLabel(tr("HW Revision:"));
    HWRevisionLabel->setFont(fontlabel);
    HWRevisionLabel->setStyleSheet("QLabel { background-color : #DCDCDC; color : black; border: 1px solid white }");
    HWRevisionValueLabel = new QLabel;
    HWRevisionValueLabel->setFont(fontvalue);
    HWRevisionValueLabel->setStyleSheet("QLabel { background-color : #F5F5F5; color : black; border: 1px solid white }");
    HWRevisionlayout=new QHBoxLayout;
    HWRevisionlayout->addWidget(HWRevisionLabel);
    HWRevisionlayout->addWidget(HWRevisionValueLabel);

    manufacturDateLabel      = new QLabel(tr("Manufacturing Date:"));
    manufacturDateLabel->setFont(fontlabel);
    manufacturDateLabel->setStyleSheet("QLabel { background-color : #F2BB05; color : black; border: 1px solid white }");
    manufacturDateValueLabel = new QLabel;
    manufacturDateValueLabel->setFont(fontvalue);
    manufacturDateValueLabel->setStyleSheet("QLabel { background-color : #F9E08D; color : black; border: 1px solid white }");
    manufacturDatelayout=new QHBoxLayout;
    manufacturDatelayout->addWidget(manufacturDateLabel);
    manufacturDatelayout->addWidget(manufacturDateValueLabel);

    specRevisionLabel      = new QLabel(tr("EAPI Specification Version:"));
    specRevisionLabel->setFont(fontlabel);
    specRevisionLabel->setStyleSheet("QLabel { background-color : #DCDCDC; color : black; border: 1px solid white }");
    specRevisionValueLabel = new QLabel;
    specRevisionValueLabel->setFont(fontvalue);
    specRevisionValueLabel->setStyleSheet("QLabel { background-color : #F5F5F5; color : black; border: 1px solid white }");
    specRevisionlayout=new QHBoxLayout;
    specRevisionlayout->addWidget(specRevisionLabel);
    specRevisionlayout->addWidget(specRevisionValueLabel);

    mainLayout = new QVBoxLayout;
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

    mainLayout->addStretch(1);
    setLayout(mainLayout);
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
