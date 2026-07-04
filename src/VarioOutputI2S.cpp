#include "VarioOutput.h"
#include "driver/i2s.h"

void VarioOutput::begin(OutputMode m) {
    mode = m;

    if (mode == OutputMode::I2S) {

        i2s_config_t cfg = {
            .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
            .sample_rate = 22050,
            .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
            .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
            .communication_format = I2S_COMM_FORMAT_I2S,
            .intr_alloc_flags = 0,
            .dma_buf_count = 4,
            .dma_buf_len = 256,
            .use_apll = false
        };

        i2s_pin_config_t pins = {
            .bck_io_num = 26,
            .ws_io_num = 25,
            .data_out_num = 22,
            .data_in_num = -1
        };

        i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
        i2s_set_pin(I2S_NUM_0, &pins);
    }
}

void VarioOutput::writeSample(float sample) {

    sample = smoothSample(sample);

    int16_t s = (int16_t)(sample * volume * 32767);

    if (mode == OutputMode::I2S) {
        size_t written;
        i2s_write(I2S_NUM_0, &s, sizeof(s), &written, portMAX_DELAY);
    }
}