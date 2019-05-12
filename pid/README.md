# PID
The PID is difficult to calculate, so we have consulte a [raspberry site](https://projects.raspberrypi.org/en/projects/robotPID/5) to understand how make a simple PID. </br>
The principe is simple, we need to see the present, futur and past error to make the proportional, integral and derivative actions.

## Why we need this ?
The PID allows to control the motors. We can see the motor like a systeme, when we to move the drone, we control the motion with a set point. Each motor must follow the set point and the PID allows to do that.

## Calcul
The regulation is based on a set point and a mesured value. </br>
With both elements, we can calculate the error like : `error = setPoint - mesuredValue`. </br>

We can create four differents regulators:
1) P
2) PI
3) PD
4) PID

### Regulator P
This regulator is based only on the present error. </br> So, the action on the systeme is calculate like that : `action = Kp * error` where Kp is equal to the proportional factor. </br>

The function at call to apply this regulator its the following:
```
PID::calcP(float setPoint, float input)
```
You can see in the params the set point and the input. In our case, the input its the value sends by the gyroscope.

### Regulator PI
The PI regulator use the proportional and integral actions. </br> The integral action use the past error. </br>
We have `action = Kp * error + Ki * previousError` where Ki is equal to the integration factor. </br>
Add this action allows to cancel the static error. If we have not a integrator in the system, it's important to add it with the regulator. </br>

The function at call to apply this regulator its the following:
```
PID::calcPI(float setPoint, float input)
```

### Regulator PD
Now we can see of the past and the present, we need to see in the futur, like we can not predict the futur, we sum all of the previous errors and divided it by the error's number, we take the mean. </br>

The output action is calculated like that : `action = Kp * error + Kd * sumOfError` where Kd is the derivative factor. </br>
The derivative action allows to increase the system's dynamic. Be careful, to add too much action, can destabilize the system. </br>

The function at call to apply this regulator its the following:
```
PID::calcPD(float setPoint, float input)
```

### Regulator PID
This regulator is the most completed, we have the three actions. </br>
We can cancel the static error with the integrator, the derivator increase the dynamic and "boost" with the proportional. </br>

The function at call to apply this regulator its the following:
```
PID::calcPID(float setPoint, float input)
```


## ESC mapping
The ESC mapping is important because the PID can generate the output value different of the input accepted by the ESC .</br>
So, the principe is simple. We have two bounds: </br>
1) The minimum value to send at the ESC, called *minBound* in the **pid.h**.
2) The maximum value to send at the ESC, called *maxBound* in the **pid.h**.

**The both are determinated arbitrarily with tests** </br>

We accept a maximum error (for the moment it's 10°) and with this error, we calculate the maximum output that the regulator can give. </br>
The mapping estimates that the regulator used is allways the **P**, so the maximum output accepted is : `outputMax = Kp * errorMax`. We define the maximum output like the 100% for the ESC. </br>

Now, we can use a simple formula to determinate the new output : `newOutput = minBound + (output/maxOutput) * maxBound`. </br>
To be sure that the value send by the function is between the maximum and minimum bounds, we check if :
1) The new output is smaller than *minBound*, we send the minimum bound.
2) The new output is greater than *maxBound*, we send the maximum bound.
3) The new output is between both bounds, we send the new output.

## Tests
We have tested the regulator with the [main.cpp](./main.cpp). </br>
We simulate the value sends by the gyroscope with *value* and the set point with *setPoint*. We apply the PID function to put the action with the error in a log file. </br>
And for simulating the drone motion, we decrease *value* by 0.5. </br>

Unfortunately, we did not test the function on the motors and the mapping function does not work too. </br>

## Authors
- Merel Ludovic - *Initial work* - [WhiteShadow13](https://github.com/WhiteShadow13)