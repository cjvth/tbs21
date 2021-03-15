from client2server import client2server

def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    


class tracker:
 def run(tracklog):
  c2s=client2server()
  i=0
  while i==0:
   status=c2s.getStatus()
   dx=int(status)&0x0fff
   #speed=int(arduino_map(abs(int(dx)),0,4096,0,100))
   #if(dx>2048):
   #     dx=dx-4096
#            tracklog.write("Received %d %d %d %d %d\n" % (dx,state,position,ticks,key0))
   speed=int(arduino_map(abs(int(dx)),0,4096,0,100)) 
   if(abs(int(dx))<500):
        if(abs(int(dx))<10):
             c2s.moveStop()
        else:
             if(int(dx)>0):
                  c2s.moveLeft(speed)
             else:
                  c2s.moveRight(speed)
#               return
  c2s.__finit__
