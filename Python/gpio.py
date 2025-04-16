import time
import RPi.GPIO as GPIO


gpio_pin = 17


def gpio_test(pin):
    print("start gpio test for pin=bcm%d" % pin)
    GPIO.setmode(GPIO.BCM)
    # 读取GPIO
    GPIO.setup(pin, GPIO.IN)
    value = GPIO.input(pin)
    print("before set, pin=%d" % value)
    # 改变GPIO输出
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, ~value)
    print("now pin=%d" % GPIO.input(pin))
    GPIO.cleanup()
    print("GPIO test done")


moves_pin = {'up': 11, 'down': 13, 'left': 15, 'right': 16}
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(list(moves_pin.values()), GPIO.OUT, initial=GPIO.HIGH)
GPIO.setup(start_button, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(start_button, GPIO.FALLING,
                      callback=onPress, bouncetime=1000)
GPIO.cleanup(list(moves_pin.values()))
GPIO.cleanup(start_button)


def onPress(pin):
	print("key press")
