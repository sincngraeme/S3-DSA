// contains parity function prototype and Enum 
typedef enum PARITY 
{
    PAR_EVEN,
    PAR_ODD,
    PAR_ERROR
    
} PARITY;

PARITY Parity(unsigned char* buff, int buflen);     // determines if there is even or odd parity for binary values using bitwise operators
PARITY ParityOnBytes(char* buf, int iBufLen);       // detemines if there is even or odd parity for ASCII values using for loops