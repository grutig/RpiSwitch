#RpiSwitch

I have a headless raspberry Pi application, designed to work in my car. 
So, the system must boot automatically when the engine is turned on. When the engine is stopped it must trigger the system shutdown and wait until it ends.
I have designed this simple solution to handle this kind of situations, but it is just a starting point.
The phisical switch is based on a arduino nano.
The schematic diagram is very simple and easy to undestand. 
There are two +12 input lines, one coming from battery (+vbatteria), the other one from then ignition line (vchiave).
When the engine is switched on, the arduino is powered through diode D1 and a 5V regulator (I’ve used a linear 7805 I had in the lab). When powered up, the arduino put D7 output to high, closing the relais and guaranteeing power to the device from car battery. At the same time it starts to monitor the status of the D6 line, which is high if ignition line is powered.
When the engine is shut off D6 turns LOW. This triggers the CPU to send a \*\*PowerFail\*\* message over the serial line and to start a timer. If the engine is swithed back on before the time expires, the timer is reset and a \*\*PowerBack\*\* message is sent over the serial line.
If the timer reaches to end, the CPU lowers the D6 line, opening the relay and cutting off the power to all the circuitry.

On the RPI a daemon is listening on the serial for messages from the switch, in order to start the shutdown of the operating system after a few seconds from receiving the first \*\*PowerFail\*\* message.
