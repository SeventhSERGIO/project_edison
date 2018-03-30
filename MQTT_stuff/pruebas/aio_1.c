#include "mqtt.h"

int sensor (void)
{
    mraa_result_t status = MRAA_SUCCESS;
    mraa_aio_context aio;
    uint16_t value = 0;

    /* initialize mraa for the platform (not needed most of the times) */
    mraa_init();

    /* initialize AIO */
    aio = mraa_aio_init(AIO_PORT);
    if (aio == NULL) {
        fprintf(stderr, "Failed to initialize AIO\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }
    value = mraa_aio_read(aio);
    return value;
}
