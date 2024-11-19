
class Port {
private: // by default
    char* port_name;
    static int count;

public:
    int baud;


    Port();
    Port(int baud_rate);
    ~Port();

    int sendData(char* data);
};