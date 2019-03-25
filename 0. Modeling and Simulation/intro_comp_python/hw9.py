def machToFPS(machList):
  FPSList = map(lambda x: x*1116.4370079, machList)
  for i in range(len(machList)):
    print("{} mach is equivalent to {:.7f} feet per secont".format(machList[i],FPSList[i]))

def sqPyramidVolume(baseHeightList,volumeList):
  resultList = map(lambda x: (x[0]*x[0]*x[1])/3, baseHeightList)
  correctList = filter(lambda x: x in resultList, volumeList)
  return correctList

def makeChange(changeList):
  changeList[0] = 100 * changeList[0]
  changeList[1] = 25 * changeList[1]
  changeList[2] = 10 * changeList[2]
  changeList[3] = 5 * changeList[3]
  totalValue = reduce(lambda x,y: x+y, changeList)
  return totalValue
  