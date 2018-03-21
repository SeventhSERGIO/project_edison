/*
######################################################
#  ****************************************
#  MRAA Bluetooth Test on C               \
#  Read a value from rfcomm (Bluetooth)   /
#  and write that on an LED using MRAA    \
#                                         /
#  Alejandro Enedino Hernandez Samaniego  \
#  alejandro.hernandez@linux.intel.com    /
#  alejandro.hernandez@intel.com          \
#  aehs29@ieee.org                        /
#  ****************************************
######################################################

Circuit:
Intel Edison
LED connected on pin 13 (default)

Pass libMRAA to the linker:
gcc-lmraa mraa_edison_bt.c -o mraa_edison_bt

*/

#include <stdio.h>
#include <stdlib.h>
#include <mraa/gpio.h>                     
        
int main(){
  /* Initialize MRAA */
  mraa_init();

  /* Initialize LED */
  mraa_gpio_context led;
  led = mraa_gpio_init(13);
  mraa_gpio_dir(led, MRAA_GPIO_OUT);

  /* Open file for reading */
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  
  /* We assume a connection has already been opened */
  fp = fopen("/dev/rfcomm0", "r");
  if (fp == NULL)
	exit(EXIT_FAILURE);


  int value;
  /* Read file line by line, we could also use something like fgets() */
  while ((read = getline(&line, &len, fp)) != -1) {
	printf("Retrieved line of length %zu :\n", read);
	printf("%s", line);
	value=line[0]-'0';			/* Convert to Integer */
	printf("Converted value: %d", value);
	mraa_result_t result =  mraa_gpio_write(led, value);
  }

  /* Close things up */
  fclose(fp);
  if (line)
	free(line);
  exit(EXIT_SUCCESS);

  mraa_gpio_close(led);

  return MRAA_SUCCESS;
}
