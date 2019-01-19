from Myro import *
init()

def main():
  pic = takePicture()
  red_count = 0
  blue_count = 0
  red_xs = []
  red_ys = []
  blue_xs = []
  blue_ys = []
  for pix in pic.getPixels():
    r = getRed(pix)
    g = getGreen(pix)
    b = getBlue(pix)
    if r > b and (r+g+b)/3 < 35:
      red_count = red_count + 1
      red_xs.append(getX(pix))
      red_ys.append(getY(pix))
    elif r < b and (r+g+b)/3 < 35:
      blue_count = blue_count + 1
      blue_xs.append(getX(pix))
      blue_ys.append(getY(pix))        
  if red_count > blue_count:
    beep(2,800)
    height = max(red_ys) - min(red_ys)
    width = max(red_xs) - min(red_xs)
    if height > width:
      forward(1,0.5)
      backward(1,0.5)
    else:
      turnLeft(1,0.5)
      turnRight(1,0.5)    
  else:
    beep(2,800)
    wait(2)
    beep(2,800)
    height = max(blue_ys) - min(blue_ys)
    width = max(blue_xs) - min(blue_xs)
    if height > width:
      forward(1,0.5)
      backward(1,0.5)
    else:
      turnLeft(1,0.5)
      turnRight(1,0.5)
main()
