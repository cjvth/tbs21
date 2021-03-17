from client2server import client2server
import time
def arduino_constrain(x,min_x,max_x):
    if x>=max_x:
        return max_x
    if x<=min_x:
        return min_x
    return round(x)
  
class tracker:
 def run(tracklog):
  c2s=client2server()
  i=0
  max_speed=100
  K_p=0.96
  K_d=-0.055
  K_i=0.069
  I=0
  last_dx=0
  delta_t=0.1
  f=1  
  while i==0:
   status=c2s.getStatus()
   dx=int(status)&0x0fff
   if(dx>2048):
    dx=dx-4096
   if  dx==-1536:
      dx=last_dx
   #tracklog.write("Received %d %d %d %d %d\n" % (dx,state,position,ticks,key0))
   sec=time.time()    
   #sec=time.time()
   if f==1:
        f=0
   else:
    	delta_t=sec-last_sec
   last_sec=sec



   P=dx
   D=(dx-last_dx)/delta_t
   D=arduino_constrain(D,-1700,1700)
   #if abs(D)>1700:
    #  D=0
   I=I+dx*delta_t
   last_dx=dx

   speed=K_p*P+K_d*D+K_i*I
   speed=arduino_constrain(speed,-max_speed,max_speed)
   tracklog.write("Received dx = {},I ={},D ={},  speed ={} , delta_t={}  \n".format(dx,round(I,1),D,speed,delta_t).encode()) 
        
   if True:#(abs(int(dx))<500):
        if 0:#(abs(speed)<2):
             c2s.moveStop()
        else:
             if(speed>0):
                  c2s.moveLeft(speed)  # -----------------возможно поменять местами -------------
             else:
                  c2s.moveRight(abs(speed))








   '''if(abs(int(dx))<500):
    if(abs(int(dx))<10):
     c2s.moveStop()
    else:
     if(int(dx)>0):
      c2s.moveLeft(5)
     else:
      c2s.moveRight(5)'''
#            return
  c2s.__finit__
