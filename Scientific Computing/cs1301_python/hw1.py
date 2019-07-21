def machToFPS():
  mach = float(input("Enter the speed in mach."))
  FPS = mach * 1116.4370079
  print(FPS," feet/second.")

def sqPyramidVolume():
  base = float(input("Enter the length of one side of the base in inches."))
  height = float(input("Enter the height in inches."))
  volume = base * base * height / 3
  print("Volume of the square pyramid is %s inches-cubed."%volume)

def makeChange():
  cent = int(input("Enter the number of cents."))
  dollar = cent // 100
  cent = cent % 100 
  quarter = cent // 25
  cent = cent % 25
  dime = cent // 10
  cent = cent % 10
  nickel = cent // 5
  penny = cent % 5
  print("%s dollar(s) %s quarter(s) %s dime(s) %s nickel(s) %s penny/pennies."%(dollar, quarter, dime, nickel, penny))
     
def PPIIndex():
  weight = float(input("Enter your weight in pounds.")) 
  height = float(input("Enter your height in inches."))
  PPI = weight / height * 1.125
  print("Your corrected PPI is %.1f."%PPI)
  