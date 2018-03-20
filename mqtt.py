import paho.mqtt.client as mqtt

#Callback  - called when the connection is established
def on_connect(client, userdata, flags, rc):
    print("Connected to server. Connection code: "+str(rc))

    # Do a subscribe to "MQTTEdison" topic whenever a new connection is done 
    client.subscribe("Distancia")

# Callback - called when a new message is received / published
def on_message(client, userdata, msg):
	#writes on console screen the topic and the message received
	print("Topico: "+msg.topic+" - Mensaje Recibido: "+str(msg.payload)) 
	
#main program
client = mqtt.Client()
client.on_connect = on_connect   #configures callback for new connection established
client.on_message = on_message   #configures callback for new message received

client.connect("192.168.1.77", 1883, 60)  #connects to broker (the '60' parameter means keepalive time). If no messages are exchanged in 60 seconds, This program automatically sends ping to broker (for keeping connection on)

#Stay here forever. Blocking function.
client.loop_forever()
