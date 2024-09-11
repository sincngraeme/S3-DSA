// contains the enum type for the input flags to Checksum()
typedef enum CHECKSUM{

    CHK_16BIT,
    CHK_8BIT,
    CHK_ERROR

} CHECKSUM;

unsigned int Checksum(void* buf, int iBufLen, CHECKSUM iType);