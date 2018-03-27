#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
/* mraa header */
#include "mraa/aio.h"

/* AIO port */
#define AIO_PORT 0
int main ()
{
    mraa_result_t status = MRAA_SUCCESS;
    mraa_aio_context aio;
    uint16_t value = 0;

    /* initialize mraa for the platform (not needed most of the times) */
    mraa_init();

    //! [Interesting]
    /* initialize AIO */
    aio = mraa_aio_init(AIO_PORT);
    if (aio == NULL) {
        fprintf(stderr, "Failed to initialize AIO\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }

    while (1) {
        value = mraa_aio_read(aio);
        //float_value = mraa_aio_read_float(aio);
        fprintf(stdout, "ADC A0 read %X - %d\n", value, value);
        //fprintf(stdout, "ADC A0 read float - %.5f\n", float_value);
    }

    /* close AIO */
    status = mraa_aio_close(aio);
    if (status != MRAA_SUCCESS) {
        goto err_exit;
    }

    return EXIT_SUCCESS;
}
