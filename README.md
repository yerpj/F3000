Power Unit 
----------------

This project aims at designing a generic power IO board for automotive projects

It features:
- 10x 12[V] digital inputs (fully filtered and protected)
- 1x lowside NTC conditionning circuit
- 1x full bridge power output (12V/13A) with temperature protection
- 2x isolated power relay outputs (12V/300mA) with voltage/current spike protection

The headers are meant to be project-agnostic and easy to wire

The interface voltage can be 3.3[V] or 10[V]

More info on demand

![alt tag](https://github.com/yerpj/F3000/blob/master/V2/DOC/V2_3dPreview.png)

![alt tag](https://github.com/yerpj/F3000/blob/master/V2/DOC/PCB_assembled_and_tested.jpg)

Control Unit
----------------

As an integral part of the steering wheel, this control unit is able to monitor and drive every IO from the Power Unit, as well as the user interface.

It features:
- 10x 12[V] digital inputs 
- 3x digital outputs
- 6x pushbuttons inputs (SW debounced)
- 1x 7-seg display
- 21 LEDs forming a beautiful bargraph-style regime speed indicator
- individual LEDs for motor temperature, oil warning, neutral-position indication and driving mode*

*: The pilot can at any time select the best gear-driving mode:
- manual control: The gearbox is controlled by pallets on the steering wheel, foot-controlled declutching
- semi-automatic: The gearbox is controlled by pallets on the steering wheel, automatic declutching
- automatic: The gearbox is automatically driven according to engine speed for ascending gears engagement, and manually controlled for descending gears engagement


![alt tag](https://github.com/yerpj/F3000/blob/master/V2/DOC/Control_Unit_3dPreview.png)
![alt tag](https://github.com/yerpj/F3000/blob/master/V2/DOC/Control_Unit.jpg)


           
           


