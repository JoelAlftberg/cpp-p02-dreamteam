/**
 * @file ESP32 GPIO driver mock.
 */
#ifndef ESP_GPIO_MOCK_H_
#define ESP_GPIO_MOCK_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

#include "arch/env/hw_platform.h"

#define ADC_UNIT_1 0

// 1. Kolla in dina driverfiler vilka funktioner/struktar som har definirats. Mocka struktar, men bara de struktmedlemmar
// som används, inte övriga. Mocka alla funktioner, skapa eventuella typer, typ esp_err_t, som bara är heltal.

/** Forward declarations. */
struct adc_channel_t;

/**
 * @brief Mocked ADC unit structure.
 */
typedef struct
{
    uint8_t id;
} adc_unit_t;

esp_err_t adc_oneshot_io_to_channel(int io_num, adc_unit_t *const unit_id, adc_channel_t *const channel);

#ifdef __cplusplus
} // extern "C"
#endif
#endif /** MOCK_ADC_H_ */