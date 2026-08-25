#include "fft.h"
#include <math.h>

fft_cfg fft_config(float sample_size, float min_freq, float max_freq, float sample_rate)
{
    fft_cfg cfg;

    cfg.sample_size = sample_size;
    cfg.min_freq = min_freq;
    cfg.max_freq = max_freq;
    cfg.sample_rate = sample_rate;
    cfg.ss_sr_ratio = sample_size / sample_rate;

    return cfg;
}

void compute_mags(float* mags, size_t size, Complex* out)
{
    for (size_t i = 0; i < size; i++) 
    {
        mags[i] = sqrtf(out[i].re * out[i].re + out[i].im * out[i].im); 
    }
}

float freq_to_bin(float freq, fft_cfg* cfg) 
{
    return freq * cfg->ss_sr_ratio;
}

void compute_bar_bins(float* bar_start_bin, size_t num_bars, fft_cfg* cfg)
{
    for (int i = 0; i <= num_bars; i++) 
    {
        float t = (float)i / num_bars;
        float freq = cfg->min_freq * powf(cfg->max_freq / cfg->min_freq, t);
        bar_start_bin[i] = freq_to_bin(freq, cfg);
    }
}

void fill_bars(float* mags, float* bars, size_t num_bars, float* bar_start_bin, fft_cfg* cfg)
{
    int max_bin = (int)(cfg->sample_size / 2);

    for (int i = 0; i < num_bars; i++)
    {
        float start_f = bar_start_bin[i];
        float end_f   = bar_start_bin[i + 1];

        if (end_f - start_f < 1.0f)
        {
            int lo = (int)start_f;
            int hi = lo + 1;
            if (hi > max_bin) hi = max_bin;
            if (lo > max_bin) lo = max_bin;

            float frac = start_f - (float)lo;
            bars[i] = mags[lo] * (1.0f - frac) + mags[hi] * frac;
        }
        else
        {
            int start = (int)start_f;
            int end   = (int)end_f;
            end = end > max_bin ? max_bin : end;

            float total = 0.0f;
            int size = end - start;
            for (int j = start; j < end; j++)
                total += mags[j];

            bars[i] = total / (float)size;
        }
    }
}
