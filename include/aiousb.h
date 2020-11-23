#ifndef AIOUSB_H
#define AIOUSB_H

#include <stdint.h>
#include <stddef.h>
#include "accesio_usb_ioctl.h"

typedef struct aiousb_device* aiousb_device_handle;

#define ADC_CONT_CALLBACK_FLAG_BEGIN_BC 0x1
#define ADC_CONT_CALLBACK_FLAG_END_STREAM 0x2
#define ADC_CONT_CALLBACK_FLAG_INSERTED 0x4

typedef void (*adc_cont_callback) (uint16_t *buff, uint32_t buff_size,
              uint32_t flags, void *context);

//init type stuff
#ifdef __cplusplus
extern "C"
{
#endif
int aiousb_init();
int aiousb_device_handle_by_path (const char *fname, aiousb_device_handle *device);
int aiousb_device_handle_by_index(unsigned long device_index, aiousb_device_handle *device);
int aiousb_device_index_by_path (const char *fname, unsigned long *device_index);
uint32_t aiousb_get_devices();
#ifdef __cplusplus
}
#endif

//Special device indexes
#define diNone  0xffffffff
#define diFirst 0xfffffffe
#define diOnly  0xfffffffd


//device handle based functions

int aiousb_query_device_info(aiousb_device_handle device,
                              uint32_t *pid, uint32_t *name_size, char *name,
                              uint32_t *dio_bytes, uint32_t *counters);

int aiousb_generic_vendor_read(aiousb_device_handle device,
            uint8_t request, uint16_t value, uint16_t index,
            uint16_t size, void *data);

int aiousb_generic_vendor_write(aiousb_device_handle device,
            uint8_t request, uint16_t value, uint16_t index,
            uint16_t size, void *data);

int aiousb_generic_bulk_in (aiousb_device_handle device,
          unsigned int pipe_index, void *data, int size,
          int *transferred);

int aiousb_generic_bulk_out (aiousb_device_handle device, unsigned int pipe_index,
           void *data, int size,	int *transferred);

int aiousb_custom_eeprom_write(aiousb_device_handle device,
            uint32_t start_address, uint32_t data_size, void *data);

int aiousb_custom_eeprom_read(aiousb_device_handle device,
            uint32_t start_address, uint32_t data_size, void *data);

int aiousb_dio_configure (aiousb_device_handle device, uint8_t b_tristate,
          void *out_mask, void *data);

int aiousb_dio_configure_ex (aiousb_device_handle device, void * out_mask,
                void *data, void *tristate_mask);

int aiousb_dio_configure_masked(aiousb_device_handle device, void *outs,
                void *outs_mask, void *data, void *data_mask, void *tristates,
                void *tristates_mask);

int aiousb_dio_write_all(aiousb_device_handle device, void *data);

int aiousb_dio_write_8(aiousb_device_handle device, uint32_t byte_index,
                uint8_t data);

int aiousb_dio_write1(aiousb_device_handle device, uint32_t bit_index,
                uint8_t data);

int aiousb_dio_read_all(aiousb_device_handle device, void *data);

int aiousb_dio_read_8(aiousb_device_handle device, uint32_t byte_index,
                uint8_t *data);

int aiousb_dio_read_1(aiousb_device_handle device, uint32_t bit_index,
                uint8_t *data);

int aiousb_dio_configuration_query(aiousb_device_handle device, void *out_mask,
                void *tristate_mask);

int aiousb_dio_stream_open(aiousb_device_handle device, uint32_t is_read);

int aiousb_dio_stream_close(aiousb_device_handle device);

int aiousb_dio_stream_set_clocks(aiousb_device_handle device, double *read_hz,
                double *write_hz);

int aiousb_dio_stream_frame (aiousb_device_handle device, uint32_t frame_points,
                uint16_t *frame_data, uint32_t *bytes_transferred);

int aiousb_ctr_8254_mode(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint32_t mode);

int aiousb_ctr_8254_load(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint16_t load_value);

int aiousb_ctr_8254_mode_load(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint32_t mode, uint16_t load_value);

int aiousb_ctr_8254_start_output_frequency(aiousb_device_handle device,
                uint32_t block_index, double *frequency);

int aiousb_ctr_8254_read(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint16_t *read_value);

int aiousb_ctr_8254_read_all(aiousb_device_handle device, uint16_t *data);

int aiousb_ctr_8254_read_status(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint8_t *read_value, uint8_t *status);

int aiousb_ctr_8254_read_mode_load(aiousb_device_handle device, uint32_t block_index,
                uint32_t counter_index, uint32_t mode, uint16_t load_value,
                uint16_t *read_value);

int aiousb_get_scan_v(aiousb_device_handle device, double *data);

int aiousb_get_channel_v (aiousb_device_handle device, uint32_t channel_index,
                double *volts);

int aiousb_get_trig_scan_v (aiousb_device_handle device, double *data,
                uint32_t timeout_ms);

int aiousb_set_scan_limits (aiousb_device_handle device, uint32_t start_channel,
                uint32_t end_channel);

int aiousb_adc_bulk_continuous_start (aiousb_device_handle device,
                uint32_t buff_size, uint32_t base_buff_count, void *context,
                adc_cont_callback callback);

int aiousb_adc_bulk_continuous_end (aiousb_device_handle device);

int aiousb_adc_get_config(aiousb_device_handle device, uint8_t *config_buff,
                uint32_t *config_size);

int aiousb_adc_range_all(aiousb_device_handle device, uint8_t *gain_codes,
                uint32_t *b_differential);

int aiousb_adc_range1(aiousb_device_handle device, uint32_t adc_channel,
                uint8_t gain_code, uint32_t b_differential);

int aiousb_adc_set_oversample(aiousb_device_handle device, uint8_t oversample);

int aiousb_adc_set_config(aiousb_device_handle device, uint8_t *config_buff,
              uint32_t *config_size);

int aiousb_adc_init_fast_scan_v(aiousb_device_handle device);

int aiousb_adc_get_fast_scan_v(aiousb_device_handle device, double *data);

int aiousb_adc_reset_fast_scan_v(aiousb_device_handle device);

int aiousb_abort_pipe(aiousb_device_handle device);



///Device index based functions
#ifdef __cplusplus
extern "C"
{
#endif
int aiousb_query_device_info(unsigned long device_index,
                            uint32_t *pid, uint32_t *name_size, char *name,
                            uint32_t *dio_bytes, uint32_t *counters);

int aiousb_generic_vendor_read(unsigned long device_index,
            uint8_t request, uint16_t value, uint16_t index,
            uint16_t size, void *data);

int aiousb_generic_vendor_write(unsigned long device_index,
            uint8_t request, uint16_t value, uint16_t index,
            uint16_t size, void *data);

int aiousb_generic_bulk_in (unsigned long device_index,
          unsigned int pipe_index, void *data, int size,
          int *transferred);

int aiousb_generic_bulk_out (unsigned long device_index, unsigned int pipe_index,
           void *data, int size,	int *transferred);

int aiousb_custom_eeprom_write(unsigned long device_index,
            uint32_t start_address, uint32_t data_size, void *data);

int aiousb_custom_eeprom_read(unsigned long device_index,
            uint32_t start_address, uint32_t data_size, void *data);

int aiousb_dio_configure (unsigned long device_index, uint8_t b_tristate,
          void *out_mask, void *data);

int aiousb_dio_configure_ex (unsigned long device_index, void * out_mask,
                void *data, void *tristate_mask);

int aiousb_dio_configure_masked(unsigned long device_index, void *outs,
                void *outs_mask, void *data, void *data_mask, void *tristates,
                void *tristates_mask);

int aiousb_dio_write_all(unsigned long device_index, void *data);

int aiousb_dio_write_8(unsigned long device_index, uint32_t byte_index,
                uint8_t data);

int aiousb_dio_write1(unsigned long device_index, uint32_t bit_index,
                uint8_t data);

int aiousb_dio_read_all(unsigned long device_index, void *data);

int aiousb_dio_read_8(unsigned long device_index, uint32_t byte_index,
                uint8_t *data);

int aiousb_dio_read_1(unsigned long device_index, uint32_t bit_index,
                uint8_t *data);

int aiousb_dio_configuration_query(unsigned long device_index, void *out_mask,
                void *tristate_mask);

int aiousb_dio_stream_open(unsigned long device_index, uint32_t is_read);

int aiousb_dio_stream_close(unsigned long device_index);

int aiousb_dio_stream_set_clocks(unsigned long device_index, double *read_hz,
                double *write_hz);

int aiousb_dio_stream_frame (unsigned long device_index, unsigned long frame_points,
                unsigned short *frame_data, uint32_t *bytes_transferred);

int aiousb_ctr_8254_mode(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint32_t mode);

int aiousb_ctr_8254_load(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint16_t load_value);

int aiousb_ctr_8254_mode_load(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint32_t mode, uint16_t load_value);

int aiousb_ctr_8254_start_output_frequency(unsigned long device_index,
                uint32_t block_index, double *frequency);

int aiousb_ctr_8254_read(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint16_t *read_value);

int aiousb_ctr_8254_read_all(unsigned long device_index, uint16_t *data);

int aiousb_ctr_8254_read_status(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint8_t *read_value, uint8_t *status);

int aiousb_ctr_8254_read_mode_load(unsigned long device_index, uint32_t block_index,
                uint32_t counter_index, uint32_t mode, uint16_t load_value,
                uint16_t *read_value);

int aiousb_get_scan_v(unsigned long device_index, double *data);

int aiousb_get_channel_v (unsigned long device_index, uint32_t channel_index,
                double *volts);

int aiousb_get_trig_scan_v (unsigned long device_index, double *data,
                uint32_t timeout_ms);

int aiousb_set_scan_limits (unsigned long device_index, uint32_t start_channel,
                uint32_t end_channel);

int aiousb_adc_bulk_continuous_start (unsigned long device_index,
                uint32_t buff_size, uint32_t base_buff_count, void *context,
                adc_cont_callback callback);

int aiousb_adc_bulk_continuous_end (unsigned long device_index);

int aiousb_adc_get_config(unsigned long device_index, uint8_t *config_buff,
                uint32_t *config_size);

int aiousb_adc_range_all(unsigned long device_index, uint8_t *gain_codes,
                uint32_t *b_differential);

int aiousb_adc_range1(unsigned long device_index, uint32_t adc_channel,
                uint8_t gain_code, uint32_t b_differential);

int aiousb_adc_set_oversample(unsigned long device_index, uint8_t oversample);

int aiousb_adc_set_config(unsigned long device_index, uint8_t *config_buff,
              uint32_t *config_size);

int aiousb_adc_init_fast_scan_v(unsigned long device_index);

int aiousb_adc_get_fast_scan_v(unsigned long device_index, double *data);

int aiousb_adc_reset_fast_scan_v(unsigned long device_index);

int aiousb_abort_pipe(unsigned long device_index);
#ifdef __cplusplus
}
#endif

#endif

