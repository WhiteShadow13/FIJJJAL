# How does it works ?

The motionCotroller here comes to implement the different functions for controlling the drone as  :

- Setup the Motors 
- Ascending
- Landing 
- Going Forward 
- Going Backward 
- Going Left 
- Going Right

</br>

The principe is the following. Motors are going to rotate clockwise or counter clockwise according to their place. 
If you are watching your drone from the top.The opposite motors on a frame axis will have the same sense of rotation.</br>
     
- Motor upLeft and Motor downRight are rotating clockwise
- Motor upRight and Motor downLeft are rotating counterClockwise

To make the brushless motors turn counterClockwise , we just need to inverse two of the three wires when you plug the motors. 

## The MotionController

So controlling the motors to go in the wanted direction is more simple.

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

### Connexion with the GPS
    To be complete ...
### Connexion with the Motors

The controller simply instantiate the motors, send them the attributes they need and the wanted behaving.
See more about motors at : [motor](/motor/README.md)

### Connexion with the PID

Each motor is connected to a pid.</br>
From the Motioncontroller, we instanciate 4 motors to which send instructions according to the direction we want to go. 
The pid implemented in each motor is going to recalculate and correct the instructions to communicate to the motors continuously according to the gyro information. 

To see how the pid works, you can see [PID](/pid/README.md).