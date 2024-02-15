/*
 * main.cpp
 *
 * Created on 2022. júl 6.
 * 		Author: Zoltán Berkula
 */

#include "Arduino.h"

#define DEF_BAUD 115200

extern "C"
{
#include "adc_dma.h"
}

static adc1_channel_t channel[4] = {
		ADC1_CHANNEL_0,
		ADC1_CHANNEL_3,
		ADC1_CHANNEL_6,
		ADC1_CHANNEL_7
};


extern "C" void app_main(void)
{
	initArduino();
	Serial.begin(DEF_BAUD);
	memset(result, SRAM_ADDR_1, TIMES);
	continuous_adc_init(channel, sizeof(channel) / sizeof(adc1_channel_t));
	adc_digi_start();
	while(true)
	{
		perform_adc_dma_read();
		print_buffer(adc_samples_CH0_ptr, ADC_SAMPLE_BUFFER_SIZE, "channel 0");
		print_buffer(adc_samples_CH3_ptr, ADC_SAMPLE_BUFFER_SIZE, "channel 3");
		print_buffer(adc_samples_CH6_ptr, ADC_SAMPLE_BUFFER_SIZE, "channel 6");
		print_buffer(adc_samples_CH7_ptr, ADC_SAMPLE_BUFFER_SIZE, "channel 7");
	}
}
