#define CTRL_KEY(k) ((k) & 0x1f)		// allows for processing ctrl inputs

class Debug {
    private:
        // int dTxAudio();
        void dTxText();
        // int dTxImage();
        // int dRxAudio();
        // int dRxText();
        // int dRxImage();
        // int dSetParameters();

    public:
        void debugGeneral();

};