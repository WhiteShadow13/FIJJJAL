# How does it works ? #

The motionCotroller here comes to implement the different functions for controlling the drone as :

- Setup the Motors 
- Ascending
- Landing 
- Going Forward 
- Going Backward 
- Turn Left 
- Turn Right
</br>

The principe is the following. Motors are going to rotate clockwise or counter clockwise according to their place. 
If you are watching your drone from the top.The opposite motors on a frame spin will have the same sense of rotation. If all rotors turn in the same direction, the craft would spin just like the regular helicopter without the tail rotor</br>
     
- Motor upLeft and Motor downRight are rotating clockwise
- Motor upRight and Motor downLeft are rotating counterClockwise

To make the brushless motors turn counterClockwise , we just need to inverse two of the three wires when you plug the motors. 

![How it works](https://image.slidesharecdn.com/howdoesquadcopterworks-171207055800/95/how-does-quadcopter-drone-works-5-638.jpg?cb=1512626305 "how it works")

## The MotionController ##

So controlling the motors to go in the wanted direction is more simple.
The quadcopter should continuously take the required measurements from the sensors, and make alterations to the speed of each rotor to maintain the body level. 

According to the direction with will have : 

- Ascending.</br>
    Motors UpLeft and downRight will increase their RPM</br>
    Motors upRight and downLeft will increase their RPM

- Landing </br>
    Motors UpLeft and downRight will decrease their RPM</br>
    Motors upRight and downLeft will decrease their RPM

- Going Forward </br>
    Motors upRight and upLeft will decrease their RPM</br>
    Motors dowRight and downLeft will increase their RPM

- Going Backward </br>
    Motors upRight and upLeft will increase their RPM</br>
    Motors dowRight and downLeft will decrease their RPM

To make the drone turning in the wanted direction , we choose to make it roll left or right and not turning. So we have :

- Roll Left </br>
    Motors upRight and downRight will increase their RPM</br>
    Motors upLeft and downLeft will decrease their RPM
    
- Roll Right </br>
    Motors upRight and downRight will decrease their RPM</br>
    Motors upLeft and downLeft will icrease their RPM

## Connexion with the Motors ##

The controller simply instantiate the motors, send them the attributes they need and the wanted behaving.
See more about motors at : [motor](/motor/README.md)

## Connexion with the Gyro##

Periodically the controller is going to ask the position of the drone to send it to the pid to correct the values on the motors if needed.

## Connexion with the PID ##

Normally in a 2D space,you have to initialize 2 pids for each axis so 6 pids.</br>
From the Motioncontroller, we instanciate 4 motors to which we send instructions according to the direction we want to go. 
The pids implemented are going to recalculate and correct the instructions(values sent to the ESC) to communicate to the motors continuously according to the gyro value and the wished value. 

To see how the pid works, you can see [PID](/pid/README.md).