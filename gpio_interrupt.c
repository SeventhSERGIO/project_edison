#include <signal.h>
#include <mraa/gpio.h>

sig_atomic_t volatile run_flag = 1;

void do_when_interrupted()
{
		run_flag = 0;
}

int main()
{
	mraa_gpio_context led, button;

	led = mraa_gpio_init(13);
	button = mraa_gpio_init(4);
	mraa_gpio_dir(led, MRAA_GPIO_OUT);
	mraa_gpio_dir(button, MRAA_GPIO_IN);

	mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &do_when_interrupted, NULL);

	while (run_flag)
	{
		mraa_gpio_write(led, 1);
		sleep(1);
		mraa_gpio_write(led, 0);
		sleep(1);
	}

	mraa_gpio_close(led);
	return 0;
}