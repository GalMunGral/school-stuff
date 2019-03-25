import math

def square(base):
  result = base ** 2
  return result
    
def taylorSwift(numFans):
  totalTime = numFans * 3
  hour = 9 + totalTime // 60
  minute = totalTime % 60
  print("Taylor Swift is done at {}:{} PM".format(hour,minute))
  return None

def girlScoutCookies():
  boxes = float(input("How Many Boxes Do You Want?"))
  moneyOwed = boxes * 4
  moneyPayed = float(input("How Much Money Do You Have?"))
  difference = moneyOwed - moneyPayed
  print("You still need ${:.1f}".format(difference))
    
def conversionTime(metersPerSecond):
  milesPerHour = metersPerSecond * 3.28084 / 5280 * 3600
  feetPerSecond = metersPerSecond * 3.28084
  kilometersPerHour = metersPerSecond / 1000 * 3600
  s1 = "You have {:.2f} mph, {:.2f} feet per second, and {:.2f} kilometers per hour"
  print(s1.format(milesPerHour,feetPerSecond,kilometersPerHour))
         
def tipCalculator():
  initial = float(input("How much is the Bill?"))
  percentage = float(input("What percentage tip would you like to pay"))
  discount = float(input("How many coupons do you have?"))
  after = initial - discount
  tax = after * 8/100 
  tip = math.ceil(initial * percentage / 100)
  totalCost = "${:.2f}".format(after + tax + tip)
  return totalCost
    
def falafel(falafelBalls, hummus, pitaBread):
  n = int(min(falafelBalls/6, hummus/2, pitaBread))
  s2 = "With {} falafel balls, {} pitas and {} hummus, you can make a maximum of {} falafels."
  print(s2.format(falafelBalls, pitaBread, hummus, n))
  