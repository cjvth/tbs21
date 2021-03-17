from client2server import client2server

class tracker:
 def run(tracklog):
  c2s=client2server()
  i=0
  while i==0:
   status=c2s.getStatus()
   dx=int(status)&0x0fff
   if(dx>2048):
    dx=dx-4096
      
   tracklog.write("Received dx = {},  speed ={}  \n".format(0,1).encode())#tracklog.write("Received %d %d %d %d %d\n" % (dx,state,position,ticks,key0))
   max_speed=55
   K_p=10
   K_d=0
   K_i=0
   I=0
   last_dx=0
   delta_t=0.1
   f=1   











   if(abs(int(dx))<500):
    if(abs(int(dx))<10):
     c2s.moveStop()
    else:
     if(int(dx)>0):
      c2s.moveLeft(5)
     else:
      c2s.moveRight(5)
#            return
  c2s.__finit__
