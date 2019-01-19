from Myro import *
init()

def onlySixths(lst):
  new_lst = []
  for i in lst:
    if i % 6  == 0:
      new_lst.append(i)
  return new_lst       
    
def union(a,b):
  lst = []
  for i in a:
    lst.append(i)
  for i in b:
    if i not in a:
      lst.append(i)
  lst.sort()
  return lst
    
def multiplyNums(lst):
  p = 1
  for i in lst:
    if type(i) == float or type(i) == int:
      p = p * i
    if type(i) == list:
      p = p * multiplyNums(i)
  return p
    
def abbreviator(s):
  new_s = ""
  for i in s:
    if i.isupper() or i.isdigit():
      new_s = new_s + i
  return new_s
    
def parse(s,d):
  lst = []
  item = ""
  for char in s:
    if char == d:
      lst.append(item)
      item = ""
    else:
      item = item + char
  lst.append(item)
  return lst
    
def lightStats():
  lst = getLight()
  print("Left:", lst[0])
  print("Center:", lst[1])
  print("Right:", lst[2])
  a = (lst[0] + lst[1] + lst[2])/3
  lst.sort()
  b = lst[1]
  c = lst[2] - lst[0]
  new_lst = [a,b,c]
  return new_lst
          