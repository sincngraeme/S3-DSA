// contains parity function prototype and Enum 
typedef enum PARITY 
{
    PAR_EVEN,
    PAR_ODD,
    PAR_ERROR
    
} PARITY;

PARITY Parity(unsigned char* buff, int buflen);
PARITY ParityOnBytes(char* buf, int iBufLen);