from Myro import *
from hw8_film import *
from hw8_sfx import *

footage1 = action1()
footage2 = action1()
footage3 = action2()
footage4 = action3()
scene1 = fadeIn(footage1)
scene2 = crossFade(footage1, footage2)
scene3 = seeingRed(footage2)
scene4 = turningLightUp(footage2[::-1])
scene5 = turningLightDown(footage3)
scene6 = turningLightUp(footage4)
scene7 = turningLightDown(footage4[::-1])
scene8 = blackScreen(footage4)
scene9 = screenShake(scene8[-1])                      
movie = scene1 + scene2 + scene3 + scene4 + scene5 + scene6 + scene7 + scene8 + scene9

i = 1
for frame in movie:
  savePicture(frame, "frame{:0>3}.gif".format(i))
  show(frame)
  wait(0.07)
  i += 1
