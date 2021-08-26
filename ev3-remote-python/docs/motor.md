# Motor

`class Motor(port)`

Object that allows interaction with a connected motor.

Parameters:

 * port ([Output](/output/)): The port on the EV3 Brick, where the motor is connected.

## Methods

`angle()`

Returns the degree of the motor.

`reset_angle()`

Resets the degree of the motor to 0.

`stop()`

Stops the motor without braking.

`brake()`

Stops the motor with active braking.

`run(speed)`

Starts the motor with a speed.

Parameters:

 * speed(percetage) - Speed of motor in percent between -100 and 100.

`run_time(speed, time, then)`

Starts the motor for a specific time and speed.

Parameters:

 * speed(percetage) - Speed of motor in percent between -100 and 100.
 * time(ms) - Time how long the speed should be maintained.
 * then([Then](/then/)) - What should be done after this action.

`run_angle(speed, angle, then)`

Starts the motor for a specific rotation-angle and speed.

Parameters:

 * speed(percetage) - Speed of motor in percent between -100 and 100.
 * angle(deg) - Angle by which the motor should rotate.
 * then([Then](/then/)) - What should be done after this action.

`run_target(speed, angle, then)`

Starts the motor for a specific rotation-angle and speed.

Parameters:

 * speed(percetage) - Speed of motor in percent between -100 and 100.
 * angle(deg) - Angle to which the motor should rotate.
 * then([Then](/then/)) - What should be done after this action.