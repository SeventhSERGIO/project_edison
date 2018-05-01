#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include <signal.h>
#include <unistd.h>
#include "mraa/aio.h"
/* AIO port */
#define AIO_PORT 0
#define LEN 20
//  Macros
#define ADDRESS     "192.168.1.100"
#define CLIENTID    "Edison"
#define TOPIC       "inTopic"
#define PAYLOAD     "Que onda!"
#define QOS         1
#define TIMEOUT     10000L

int sensor (void);
void delivered(void *context, MQTTClient_deliveryToken dt);
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
void connlost(void *context, char *cause);
