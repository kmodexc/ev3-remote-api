import time
import legoapi

b = legoapi.Brick()
b.Initialize()
b.setMotorPower(legoapi.Output.A,50)
time.sleep(2)
b.setMotorPower(legoapi.Output.A,0)