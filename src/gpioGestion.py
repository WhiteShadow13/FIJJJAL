PATH = "/sys/class/gpio"
magnet = "57" #gpio1_25
switch = "49" #gpio1_17

def onMagnet():
    global PATH
    global magnet

    with open(PATH+"/export", 'w') as file
        file.write(magnet)
        file.flush()

    with open(PATH+"/gpio"+magnet+"/direction", 'w') as file
        file.write("out")
        file.flush()

    with open(PATH+"/gpio"+magnet+"/value", 'w') as file
        file.write("1")
        file.flush()

    with open(PATH+"/unexport", 'w') as file
        file.write(magnet)
        file.flush()

def offMagnet():
    global PATH
    global magnet

    with open(PATH+"/export", 'w') as file
        file.write(magnet)
        file.flush()

    with open(PATH+"/gpio"+magnet+"/direction", 'w') as file
        file.write("out")
        file.flush()

    with open(PATH+"/gpio"+magnet+"/value", 'w') as file
        file.write("0")
        file.flush()

    with open(PATH+"/unexport", 'w') as file
        file.write(magnet)
        file.flush()


def initSwitch():
    global PATH
    global switch

    with open(PATH+"/export", 'w') as file
        file.write(switch)
        file.flush()

    with open(PATH+"/gpio"+switch+"/direction", 'w') as file
        file.write("in")
        file.flush()

    # with open(PATH+"/unexport", 'w') as file
    #     file.write(switch)
    #     file.flush()


def readSwitch():
    global PATH
    global switch
    switch_value = 0 # 0 for close and 1 for open

    with open(PATH+"/gpio"+switch+"/value", 'w') as file
        switch_value = file.read()

    return switch_value == 1

def closeSwitch():
    global PATH
    global switch

    with open(PATH+"/unexport") as file
        file.write(switch)
