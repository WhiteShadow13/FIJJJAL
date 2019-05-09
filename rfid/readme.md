# RFID

This part has two files in Python, one for writing informations on a RFID card and one for reading these.

## Getting Started

If you want to test the codes, download this project and go in this directory then follow this instructions.

### Prerequisites

You need to install these libraries :

* RC522 library (pi-rc522)

    [Link of the Github](https://github.com/ondryaso/pi-rc522 "Named link title")

    Install using pip:

    ```
    pip install pi-rc522
    ```
* Spidev

    ```
    pip install spidev
    ```

* RPi.GPIO

    ```
    pip install RPi.GPIO
    ```

### Connecting
Connecting RC522 module to SPI is pretty easy. The following table come from [the library's Github](https://github.com/ondryaso/pi-rc522).
If you want more informations, you can go check this Github.

| Board pin name | Board pin | Physical RPi pin | RPi pin name |
|----------------|-----------|------------------|--------------|
| SDA            | 1         | 24               | GPIO8, CE0   |
| SCK            | 2         | 23               | GPIO11, SCKL |
| MOSI           | 3         | 19               | GPIO10, MOSI |
| MISO           | 4         | 21               | GPIO9, MISO  |
| IRQ            | 5         | 18               | GPIO24       |
| GND            | 6         | 6, 9, 20, 25     | Ground       |
| RST            | 7         | 22               | GPIO25       |
| 3.3V           | 8         | 1,17             | 3V3          |

### Running the codes

For the writing part, you can already launch the code by writing this following bash instruction on your Raspberry.

In this project, we're using python3.

```
python3 RFID_writeCard.py
```
See later for the explanation of the code.

For the reading part, you have to create the ".exe" which is the code from the other parts that you have to lauch when the door is closed.
You have to modify the line 69 with your relative path to the ".exe".

```
b = subprocess.call(["relative_path", str(latitude), str(longitude)], shell = False)
```

After that you can run the code without error by writing :

```
python3 RFID_readCard.py
```

## Informations about RFID

The RFID module detect magnetic badges and cards from a distance of 10cm. By passing your card before, this module can read the id of the card (UID) and all the informations on it. Each card has `its own UID`.

In this project, we used the most common card with a frequency of 13,56MHz.

### Structure

A RFID card is divided in many sectors subdivided in blocks which is also subdivided in datas. <br>
There are : 
* 16 sectors
* 4 blocks per sector (64 in total)
* 16 datas per block (each data is a number of 8 bits)

This picture comes from this [tutorial](https://plaisirarduino.fr/rfid-avec-arduino/). Don't hesitate to check this tutorial for more informations.

To write on a card informations, you have to define the sector (in red) and the address or the block (in blue). We will see later how to do this in python. 

![Structure of the card](https://plaisirarduino.fr/arduino/wp-content/uploads/2018/07/contenue-RFID.png "RFID card structure")

`Don't write the block 0` because sometime it can't be modified because it contains the UID. Some cards allow to modify the UID and others don't.

`Don't write the last block of each sector` because it can make the card unuseable (example : sector 1 block 7, sector 2 block 11, ...).

This structure is very important because it determines the structure of the code.

### Encryption

We can also encrypt the data that we put in the differents sectors. For this, we use two keys, a `key A` and a `key B`. Then, the person, who wants to read informations in a certain sector, has to have the correct key to decrypt them. Otherwise he can't read them.

By default these key has the value OxFF OxFF OxFF OxFF OxFF OxFF. We don't change it at this moment but it can be interesting to change them. In fact, it can prevent that anybody can read and write on the card.

### Important instructions

After the instanciation of an object RFID (object = RFID()), we can call methods on it to make some actions.

* Wait the presence of a RFID tag

    The first instruction initializes the detection, it enables IRQ to be on detect and waits for a tag. If there is one, we "ask" the state of the tag. The request method returns `True` if the tag is **not** present. If the request is successful, we can call the next instruction.

    ```
    object.wait_for_tag()
    object.request()
    ```
* Recover the id of a RFID tag

    This method returns if there is an error or not and returns the identifier of the tag.

    ```
    object.anticoll()
    ```

* Select the RFID tag by its identifier

    Thanks to this instruction, we can now do whatever we want.

    ```
    object.select_tag(uid)
    ```

* Authentification

    With this instruction, we give the authentification that we use (A or B) (see Encryption part). We also give in parameters which block we want to access with the key which is the third parameter in this instruction. The fourth is the identifier of the tag. 

    ```
    object.card_auth(object.auth_a, block_number, key_array, uid)
    ```

 * Read values on the card

    The first instruction reads the entire block and the second one gives us only the informations.

    ```
    object.read(block_number)
    object.read(block_number)[1]
    ```

* Use the class RFIDUtil

    RFIDUtil contains useful methods for dealing with tags and simplifies the previous instructions.

    ```
    util = object.util()
    ```

    For the simplification, you can see it on [the library's Github](https://github.com/ondryaso/pi-rc522).

* Write on the RFID tag

    We can write an entire block with the first instruction or rewrite specific bytes in block using RFIDUtil class with the second instruction.

    ```
    object.write(block_number, informations_array)
    util.rewrite(block_number, partial_informations_array)
    ```

## Explanation of the logic of the code

### RFID_writeCard

The idea of this code is to run on another RFID reader to simulate a shop. The person asks for an item and this one is delivered a few days later by drone. <br>
Then the person in the shop can launch this code to put the location of the customer's house on the tag which is going to be on the package and an unique UID on the RFID card of the customer which gives him the possibility to open the box.

For this, we wait to detect a tag. When we detect it, we ask the seller to enter the latitude and the longitude where the customer want to recover his package. After that we make manipulations on them to fit the structure of the RFID tag that I explain above.

We can only put in the RFID tag integer of 8 bits (value from 0 to 255). Then we split these numbers by the comma character and decompose the decimal parts two by two in three parts. We can't take by three numbers because the max value is then 999 and this value is not possible to put in the RFID tag. <br>
We use the value 255 for positive and 0 for negative values.

After that, we write on the RFID tag in a certain order :

```
util.rewrite(9, [latitude_sign, latitude_integer, latitude_decimal1, latitude_decimal2, latitude_decimal3, longitude_sign, longitude_integer, longitude_decimal1, longitude_decimal2, longitude_decimal3])
```
We let two seconds to the seller to put the customer's card on the RFID reader and write on this card the UID of the other RFID tag.

### RFID_readCard

The idea of this code is to run the other parts when the package is in the box.

For this, we wait that the seller closes the door of the box under the drone. We detect it thanks to the switch. Once it's done, we check if there is a RFID tag. If it's ok, we read the informations on the card at the right block and reconstruct the latitude and the longitude. We activate the electromagnet to close the door and run the code with the correct parameters to start to fly.

Once this code has finished that means that we arrived to the correct location. We wait for a card with the uid of the tag on the package at the block 9. If the customer scan his card, the electromagnet turn off and he can take his package. After 5 second, we redo all the routine.

The part of the code for the return is missing because of a lack of time.

## Authors

* **Beard Julien** - *Initial work* - [Julienyou](https://github.com/Julienyou)


    

