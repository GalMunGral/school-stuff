from Myro import *
init()

def themeSong():
  beep(3,500)
  beep(3,600)
  beep(3,700)
  beep(3,800)
  beep(3,900)
    
def signatureAbility():
  # moving in a circle
  for t in timer(15):
    motors(0.3,1)
    themeSong()
  stop()
  print(getName())
       
def secondAbility():
  # it keeps moving unless it senses something in front of it
  for t in timer(10):
    forward(1)
    while getObstacle(1)>3000:
      stop()
  stop()

def thirdAbility():
  # moving around in different directions
  for t in timer(10):
    motors(0.3,1,1)
    motors(1,0.3,1)
        
def battleMenu():        
  while True:
    print("1.One Ability")
    print("2.Two Abilities")
    print("3.Three Abilities")
    print("4.Exit")
    ans = input("Which option would you like?")
    try:
      choice = int(ans)
      if choice == 1:
        signatureAbility()
      elif choice == 2:
        signatureAbility()
        secondAbility()
      elif choice == 3:
        signatureAbility()
        secondAbility()
        thirdAbility()
      elif choice == 4:
        print("You won the battle!")
        return
      else:
        print("I'm sorry, that is not a valid choice.")
    except:
      print("I'm sorry, that is not a valid choice.")
      