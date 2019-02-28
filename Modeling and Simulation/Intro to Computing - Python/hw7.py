from Myro import *
init()

def seeingRed():
  pic = takePicture()
  savePicture(pic,"seeing-red-input.gif")
  for pix in getPixels(pic):
    setRed(pix,min(getRed(pix)+100,255))
  savePicture(pic,"seeing-red.gif")
    
def fade():
  pics = []
  s = 0
  for i in range(10):
    pic = takePicture()
    for pix in getPixels(pic):
      setRed(pix,max(getRed(pix)-s,0))
      setGreen(pix,max(getGreen(pix)-s,0))
      setBlue(pix,max(getBlue(pix)-s,0))
    pics.append(pic)
    s += 25
  savePicture(pics,"fade.gif")
    
def overlay():
  pic = takePicture()
  savePicture(pic,"overlay-input.gif")
  w = getWidth(pic)
  h = getHeight(pic)
  for x in range(w//2-10, w//2+10):
    for y in range(h):
      pix = getPixel(pic,x,y)
      setRGB(pix,(0,255,0))
  for y in range(h//2-10,h//2+10):
    for x in range(w):
      pix = getPixel(pic,x,y)
      setRGB(pix,(0,255,0))
  savePicture(pic,"overlay.gif")
    
def multipleExposure():
  pics = []
  for i in range(10):
    pic = takePicture()    
    pics.append(pic)
  pic = makePicture(427,266)    
  for x in range(getWidth(pic)):
    for y in range(getHeight(pic)):
      pix = getPixel(pic,x,y)
      r = 0
      g = 0
      b = 0
      for i in range(10):
        p = getPixel(pics[i],x,y)
        r += getRed(p)*0.1
        g += getGreen(p)*0.1
        b += getBlue(p)*0.1
      setRGB(pix,(int(r),int(g),int(b)))
  savePicture(pic,"multiple-exposure.gif")

def crossFade():
  pics1 = []
  for i in range(11):
    pic = takePicture()
    pics1.append(pic)
  pics2 = []
  for i in range(11):
    pic = takePicture()
    pics2.append(pic)
  pics = []
  p = 0
  for i in range(11):
    pic = makePicture(427,266)
    for x in range(getWidth(pic)):
      for y in range(getHeight(pic)):
        pix = getPixel(pic,x,y)
        pix1 = getPixel(pics1[i],x,y)
        pix2 = getPixel(pics2[i],x,y)
        r = (1-p)*getRed(pix1) + p*getRed(pix2)
        g = (1-p)*getGreen(pix1) + p*getGreen(pix2)
        b = (1-p)*getBlue(pix1) + p*getBlue(pix2)
        setRGB(pix,(int(r),int(g),int(b)))
    pics.append(pic)
    p += 0.1
  savePicture(pics, "cross-fade.gif")

def splitScreen():
  pics1 = []
  for i in range(10):
    pic = takePicture()
    pics1.append(pic)
  pics2 = []
  for i in range(10):
    pic = takePicture()
    pics2.append(pic)
  pics = []
  for i in range(10):
    pic = makePicture(427,266)
    for x in range(getWidth(pic)):
      for y in range(getHeight(pic)//2):
        pix = getPixel(pic,x,y)
        pix1 = getPixel(pics1[i],x,y)
        setRGB(pix,getRGB(pix1))
      for y in range(getHeight(pic)//2,getHeight(pic)):
        pix = getPixel(pic,x,y)
        pix2 = getPixel(pics2[i],x,y)
        setRGB(pix,getRGB(pix2))
    pics.append(pic)
  savePicture(pics,"split-screen.gif")

def greenScreen():
  pic = makePicture("http://img.uncova.com/13c91e6765961bdb0bdaca4e6b4c1306f2649969.jpg")
  savePicture(pic,"green-screen-input.gif")
  b_pic = makePicture("https://lh6.googleusercontent.com/-DjxErEr0uKw/Tv8Obud0z8I/AAAAAAAACG8/zf2MUhseEGk/w800-h800/5th_Solvay_conference_Physics_1927.jpg")
  savePicture(b_pic,"green-screen-background.gif")
  for x in range(getWidth(pic)):
    for y in range(getHeight(pic)):
      pix = getPixel(pic,x,y)
      r = getRed(pix)
      g = getGreen(pix)
      b = getBlue(pix)
      if g > r and g > b:
        b_pix = getPixel(b_pic,x,y)
        setRGB(pix,getRGB(b_pix))
  savePicture(pic,"green-screen.gif")

def screenShake():
  pic = takePicture()
  savePicture(pic,"screen-shake-input.gif")
  l_pic = makePicture(427,266,makeColor(0,0,0))
  for x in range(getWidth(l_pic)-10):
    for y in range(getHeight(l_pic)):
      l_pix = getPixel(l_pic,x,y)
      pix = getPixel(pic,x+10,y)
      setRGB(l_pix,getRGB(pix))
  t_pic = makePicture(427,266,makeColor(0,0,0))
  for x in range(getWidth(t_pic)):
    for y in range(getHeight(t_pic)-10):
      t_pix = getPixel(t_pic,x,y)
      pix = getPixel(pic,x,y+10)
      setRGB(t_pix,getRGB(pix))
  r_pic = makePicture(427,266,makeColor(0,0,0))
  for x in range(10,getWidth(r_pic)):
    for y in range(getHeight(r_pic)):
      r_pix = getPixel(r_pic,x,y)
      pix = getPixel(pic,x-10,y)
      setRGB(r_pix,getRGB(pix))
  b_pic = makePicture(427,266,makeColor(0,0,0))
  for x in range(getWidth(b_pic)):
    for y in range(10,getHeight(b_pic)):
      b_pix = getPixel(b_pic,x,y)
      pix = getPixel(pic,x,y-10)
      setRGB(b_pix,getRGB(pix))
  savePicture([l_pic,t_pic,r_pic,b_pic],"screen-shake.gif")

def lensFlare():
  pic = takePicture()
  savePicture(pic,"lens-flare-input.gif")
  for x in range(getWidth(pic)):
    for y in range(getHeight(pic)):
      pix = getPixel(pic,x,y)
      d = ((x-213)**2 + (y-133)**2)**0.5
      r = getRed(pix)+10000/(d+30) 
      g = getGreen(pix)+10000/(d+30)
      b = getBlue(pix)+9000/(d+30)
      setRed(pix, min(int(r),255))
      setGreen(pix,min(int(g),255))
      setBlue(pix, min(int(b),255))
  savePicture(pic,"lens-flare.gif") 

def yinYang():
  pic = takePicture()
  savePicture(pic,"yin-yang-input.gif")
  for x in range(getWidth(pic)):
    for y in range(getHeight(pic)):
      pix = getPixel(pic,x,y)
      if( 
        ((x-106)**2+(y-66)**2 < 15600 or  y < 0.623*x)
        and (x-106)**2+(y-66)**2 > 500
        and (x-320)**2+(y-199)**2 > 15600
        or (x-320)**2+(y-199)**2 < 500
      ):
        setRed(pix, min(getRed(pix)+50,255))
        setGreen(pix, min(getGreen(pix)+50,255))
        setBlue(pix, min(getBlue(pix)+50,255))            
      else:
        setRed(pix, max(getRed(pix)-50,0))
        setGreen(pix, max(getGreen(pix)-50,0))
        setBlue(pix, max(getBlue(pix)-50,0))
  savePicture(pic,"yin-yang.gif")
  