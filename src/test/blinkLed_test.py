import time

PATH = "/sys/class/gpio"
pin = "57" #gpio1_25

if __name__ == "__main__":

    with open(PATH+"/export", 'w') as file
        file.write(pin)
        file.flush()

    with open(PATH+"/gpio"+pin+"/direction", 'w') as file
        file.write("out")
        file.flush()

    with open(PATH+"/gpio"+pin+"/value", 'w') as file
        file.write("1")
        file.flush()

        time.sleep(1)

        file.write("0")
        file.flush()

        time.sleep(1)

    with open(PATH+"/unexport", 'w') as file
        file.write(pin)
        file.flush()
