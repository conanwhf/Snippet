config_resolution = (640, 480)

# initialize the camera
camera = PiCamera()
camera.resolution = config_resolution
# allow the camera to warmup
time.sleep(1)
# grab an image from the camera
rawCapture = PiRGBArray(camera, size=config_resolution)
camera.capture(rawCapture, format="bgr")
imgs.append(rawCapture.array)
