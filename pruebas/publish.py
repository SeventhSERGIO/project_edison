import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.publish as publish

publish.single("test", "boo", hostname="192.168.1.117")
