/**
 * @file Hardware platform.
 */
#pragma once

// Use mocked hardare platform if TESTSUITE is defined.
#ifdef TESTSUITE
#include "arch/env/test/hw_platform.h"

// Else use real ESP32 headers.
#else
#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_continuous.h>
#include <esp_adc/adc_cali.h>
#include <esp_adc/adc_cali_scheme.h>
#include <hal/adc_types.h>
#include <sdkconfig.h>
#endif /** TESTSUITE */