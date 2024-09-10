typedef enum PARITY 
{
    PAR_EVEN,
    PAR_ODD,
    PAR_ERROR
    
} PARITY;

// Function Prototype

PARITY ParityOnBytes(char* buf, int iBufLen);