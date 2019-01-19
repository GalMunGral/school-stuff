from Myro import *
init()

def action1():
  footage = []
  i = 1
  while i <= 50:
    forward(0.1)
    pic = takePicture()
    footage.append(pic)
    i += 1
    while getObstacle(1) > 3000:
      turnLeft(0.01)
      pic = takePicture()
      footage.append(pic)
      i += 1
  stop()
  return footage

def action2():
  footage = []
  for i in range(50):
    forward(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(15):
    turnRight(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(30):
    turnLeft(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(15):
    turnRight(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(40):
    backward(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(30):
    turnRight(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
  for i in range(15):
    turnLeft(0.1)
    pic = takePicture()
    footage.append(pic)        
  stop()
  return footage

def action3():
  footage = []
  i = 1
  while i <= 50:
    forward(0.1,0.1)
    pic = takePicture()
    footage.append(pic)
    i += 1
    if getObstacle(1) > 3000:
      break
  stop()
  return footage
  