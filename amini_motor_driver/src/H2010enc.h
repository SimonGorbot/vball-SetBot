#ifndef H2010enc_H
#define H2010enc_H

class H2010enc {
    private:
        int outPin;
    public:
        H2010enc(int digitalInPin);
        float getRPM();
};

#endif