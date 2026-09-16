#include "test/driver/adc/mock_adc.h"

// -----------------------------------------------------------------------------
esp_err_t adc_oneshot_io_to_channel(int io_num, adc_unit_t *const unit_id, adc_channel_t *const channel)
{
    // Pure dummy - do nothing.
    (void) (io_num);
    (void) (unit_id);
    (void) (channel);
}