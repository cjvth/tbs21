from client2server import client2server
#import time
def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    


class tracker:
 def run(tracklog):
  c2s=client2server()
  i=0
  




 # for i in range(0,100):
#   time.sleep(1)


  
  while i==0:
   status=c2s.getStatus()
   
   dx=int(status)&0x0fff
   tracklog.write("dx = {}\n".format(dx).encode()) 
