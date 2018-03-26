#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
//  Macros
#define ADDRESS     "192.168.1.64"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "test"
#define PAYLOAD     "Que onda!"
#define QOS         1
#define TIMEOUT     10000L
volatile MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}
int main(int argc, char* argv[])
{
    // A handle representing an MQTT client
    MQTTClient client;
    // Defines several settings that control the way the client connects to an MQTT server
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    // A structure representing the payload and attributes of an MQTT message
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    // A delivery token is returned to the client application when a message is published.
    // The token can then be used to check that the message was successfully delivered to its destination
    MQTTClient_deliveryToken token;
    int rc;
    // This function creates an MQTT client ready for connection to the specified server and
    // using the specified persistent storage
    // &client A pointer to an MQTTClient handle
    // ADDRESS string specifying the server to which the client will connect
    // CLIENTID The client identifier passed to the server when the client connects to it
    // MQTTCLIENT_PERSISTENCE_NONE The type of persistence to be used by the client
    // NULL persistence_context, this argument is unused and should be set to NULL
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    // The keep alive interval enables the client to detect when the server is no longer available
    conn_opts.keepAliveInterval = 20;
    // If a previous session still exists, and cleansession=true,
    // then the previous session information at the client and server is cleared
    conn_opts.cleansession = 1;
    // This function sets the callback functions for a specific client
    // client A valid client handle
    // NULL A pointer to any application-specific context
    // connlost A pointer to an MQTTClient_connectionLost() callback function
    // msgarrvd A pointer to an MQTTClient_messageArrived() callback function
    // delivered A pointer to an MQTTClient_deliveryComplete() callback function
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    //
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
      printf("Failed to connect, return code %d\n", rc);
      exit(EXIT_FAILURE);
    }
    int valor;
    scanf("%d\n",&valor);
    pubmsg.payload = valor;
    pubmsg.payloadlen = strlen(valor);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    deliveredtoken = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            PAYLOAD, TOPIC, CLIENTID);
    while(deliveredtoken != token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
