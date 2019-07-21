def applyToTech(reading,math,writing):
  total = reading + math + writing
  r = reading in range(680,801)
  m = math in range(690,801)
  w = writing in range(650,801)
  t = total in range(2060,2401)
  if reading >= 800 or math >= 800 or writing >= 800:       
    return "Invalid scores. Try again."
  elif t and r and m and w:
    return "Congratulations, you have been admitted to Georgia Tech. Go Jackets!"
  else:
    return "I am sorry to inform you we cannot offer you admission to Georgia Tech."

def guessAge(age):
  i = 0
  while i < 6:
    guess = input("Guess the Age")
    if guess.lower() == "quit":
      print("Don't give up just because things are hard!")
      break
    elif int(guess) == age:
      print("Great Job! It took you {} tries to guess the age".format(i))
      break
    else:
      print("Try again.")
    i += 1
  if i == 6:
    print("You have exceeded the number of tries.")
  print("Thank you for playing!")
    
def encryptMessage(secretMsg):
  newMsg = ""
  for ch in secretMsg:
    if ch.isupper():
      newMsg += ch.lower()+"^"
    elif ch.islower():
      newMsg += ch
    elif ch == "1":
      newMsg += "@"
    elif ch == "2":
      newMsg += "#"
    elif ch == "3":
      newMsg += "$"
    else:
      newMsg += "*"
  return newMsg
             
def numberPyramid(num):
  n = int(num)
  for i in range(n,0,-1):
    print("{:<{width}}".format(str(i)*i,width=n), end="")
    print("{:>{width}}".format(str(i)*i, width=n))
      
def reverseMultiTable(n):
  for i in range(n,0,-1):
    for j in range(n,0,-1):
      print("{:>3}".format(i*j),end="")
    print("")
        
def enoughFor():
  desired_grade = input("What letter-grade would you like to get?(A-D)").upper()
  if desired_grade == "A":
    desired = 90
  elif desired_grade == "B":
    desired = 80
  elif desired_grade == "C":
    desired = 70
  elif desired_grade == "D":
    desired = 60   
  else:  
    print("That's not a letter-grade.")
    return
  current = int(input("What's your current grade on the class in % (0-100)"))
  w = int(input("How much is the final worth?"))
  final = (100*desired - (100-w)*current)/w
  if final > 100:
    print("I'm sorry it's impossible for you to get this grade")
  else:    
    print("You need {} in the final to get a {} in the class.".format(final,desired_grade))
    