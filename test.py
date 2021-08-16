import time
import legoapi

b = legoapi.Brick()
b.Initialize()
b.setMotorPower(legoapi.Output.A,50)
b.setMotorPower(legoapi.Output.B,50)
time.sleep(2)
b.setMotorPower(legoapi.Output.A,0)
b.setMotorPower(legoapi.Output.B,0)