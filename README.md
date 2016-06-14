## Wind River Rocket [**Arduino-lite**](https://github.com/Wind-River/rocket-arduino-lite) API

# Arduino-lite MQTT Client Sketch  
A device connects to a remote MQTT broker and publishes and subscribes to MQTT topics.  

*** 



##  Required Hardware
 * [**Intel Galileo Gen 2**](http://www.intel.com/content/www/us/en/embedded/products/galileo/galileo-overview.html) or [**NXP FRDM-K64F**](http://www.nxp.com/products/software-and-tools/hardware-development-tools/freedom-development-boards/freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:FRDM-K64F)  
 
An Ethernet cable (attached to a network with Internet access) must be plugged into the **RJ45** connector

## Output
The Console view in the Helix App Cloud IDE displays:
* The Ethernet link coming up with an IP address (from DHCP)
* MQTT messages between the Client and Broker
* Messages that are published; and
* Messages that are received from the broker.

```publishing topic rocket/greeting payload hello from rocket  
TX: PUBLISH dup=0 qos=1 retain=0 len=36  
sent acknowledge 38 bytes  
RX: PUBACK dup=0 qos=0 retain=0 len=2
RX: PUBLISH dup=0 qos=1 retain=0 len=36
Rocket received message  [rocket/greeting] hello from rocket
TX: PUBACK dup=0 qos=0 retain=0 len=2
sent acknowledge 4 bytes
```

