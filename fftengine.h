#ifndef FFTENGINE_H
#define FFTENGINE_H

class FftEngine
{
public:

    static void spectrumRealDb(double *data, int size);

private:
    FftEngine() = delete;

    static const int FT_DIRECT = -1;    // Direct transform.
    static const int FT_INVERSE = 1;    // Inverse transform.
    static int fft(float *Rdat, float *Idat, int N, int LogN, int Ft_Flag);
    static bool isNumber2powK(int number);

};

#endif // FFTENGINE_H
