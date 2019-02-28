from Myro import *

def fadeIn(pics):
  new_pics = []
  s = 200
  for pic in pics:
    new_pic = makePicture(427,266)
    for x in range(getWidth(pic)):
      for y in range(getHeight(pic)):
        pix = getPixel(pic,x,y)
        new_pix = getPixel(new_pic,x,y)
        setRed(new_pix, max(getRed(pix)-s, 0))
        setGreen(new_pix, max(getGreen(pix)-s, 0))
        setBlue(new_pix, max(getBlue(pix)-s, 0))
    new_pics.append(new_pic)
    s -= 255//len(pics)
  return new_pics
    
def crossFade(pics1,pics2):
  new_pics = []
  p = 0
  n = min(len(pics1),len(pics2))
  for i in range(n):
    new_pic = makePicture(427,266)
    pic1 = pics1[i]
    pic2 = pics2[i]
    for x in range(getWidth(new_pic)):
      for y in range(getHeight(new_pic)):
        new_pix = getPixel(new_pic,x,y)
        pix1 = getPixel(pic1,x,y)
        pix2 = getPixel(pic2,x,y)
        r = (1-p)*getRed(pix1) + p*getRed(pix2)
        g = (1-p)*getGreen(pix1) + p*getGreen(pix2)
        b = (1-p)*getBlue(pix1) + p*getBlue(pix2)
        setRGB(new_pix,(int(r),int(g),int(b)))
    new_pics.append(new_pic)
    p = min(p+0.1,1)
  return new_pics

def seeingRed(pics):
  new_pics = []
  r = 0
  for pic in pics:
    new_pic = makePicture(427,266)
    for x in range(getWidth(pic)):
      for y in range(getHeight(pic)):
        pix = getPixel(pic,x,y)
        new_pix = getPixel(new_pic,x,y)
        setRed(new_pix, min(getRed(pix)+r,255))
        setGreen(new_pix, getGreen(pix))
        setBlue(new_pix, getBlue(pix))
    new_pics.append(new_pic)
    r += 255//len(pics)
  return new_pics

def turningLightUp(pics):
  new_pics = []
  s = 0
  for pic in pics:
    new_pic = makePicture(427,266)
    for x in range(getWidth(new_pic)):
      for y in range(getHeight(new_pic)):
        new_pix = getPixel(new_pic,x,y)
        pix = getPixel(pic,x,y)
        d = ((x-213)**2+(y-133)**2)**0.5
        g = getGreen(pix) + 5000*(1+s)/(d+30)
        b = getBlue(pix) + 4000*(1+s)/(d+30)
        setRed(new_pix,255)
        setGreen(new_pix, min(int(g),255))
        setBlue(new_pix, min(int(b),255))
    new_pics.append(new_pic)
    s += 0.25
  return new_pics
    
def turningLightDown(pics):
  new_pics = []
  s = 5
  for pic in pics:
    new_pic = makePicture(427,266)
    for x in range(getWidth(new_pic)):
      for y in range(getHeight(new_pic)):
        new_pix = getPixel(new_pic,x,y)
        pix = getPixel(pic,x,y)
        r = getRed(pix)
        g = getGreen(pix)
        b = getBlue(pix)
        d = ((x-213)**2+(y-133)**2)**0.5
        new_r = getRed(pix) + 5000*(1+s)/(d+30)
        new_g = getGreen(pix) + 5000*(1+s)/(d+30)
        new_b = getBlue(pix) + 4000*(1+s)/(d+30)
        setRed(new_pix, max(new_r,r))
        setGreen(new_pix, max(new_g,g))
        setBlue(new_pix, max(new_b,b))
    new_pics.append(new_pic)
    s -= 0.25
  return new_pics

def blackScreen(pics):
  new_pics = []
  face = makePicture("photo.jpg")
  for pic in pics:
    new_pic = makePicture(427,266)
    for x in range(getWidth(pic)):
      for y in range(getHeight(pic)): 
        new_pix = getPixel(new_pic,x,y)
        pix = getPixel(pic,x,y)
        face_pix = getPixel(face,x,y)
        r = getRed(pix)
        g = getGreen(pix)
        b = getBlue(pix)
        if r < 30 or g < 30 or b < 30:
          setRGB(new_pix,getRGB(face_pix))
        else:
          setRGB(new_pix,getRGB(pix))
    new_pics.append(new_pic)
  return new_pics

def screenShake(pic):
  new_pics = []
  l_pic = makePicture(427,266, makeColor(0,0,0))
  for x in range(getWidth(l_pic)-10):
    for y in range(getHeight(l_pic)):
      l_pix = getPixel(l_pic,x,y)
      pix = getPixel(pic,x+10,y)
      setRGB(l_pix, getRGB(pix))
  t_pic = makePicture(427,266, makeColor(0,0,0))
  for x in range(getWidth(t_pic)):
    for y in range(getHeight(t_pic)-10):
      t_pix = getPixel(t_pic,x,y)
      pix = getPixel(pic,x,y+10)
      setRGB(t_pix, getRGB(pix))
  r_pic = makePicture(427,266, makeColor(0,0,0))
  for x in range(10,getWidth(r_pic)):
    for y in range(getHeight(r_pic)):
      r_pix = getPixel(r_pic,x,y)
      pix = getPixel(pic,x-10,y)
      setRGB(r_pix, getRGB(pix))
  b_pic = makePicture(427,266, makeColor(0,0,0))
  for x in range(getWidth(b_pic)):
    for y in range(10,getHeight(b_pic)):
      b_pix = getPixel(b_pic,x,y)
      pix = getPixel(pic,x,y-10)
      setRGB(b_pix, getRGB(pix))
  for i in range(5):
    new_pics.append(l_pic)
    new_pics.append(t_pic)
    new_pics.append(r_pic)
    new_pics.append(b_pic)
  return new_pics
  