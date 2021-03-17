from client2server import client2serve

#####import time

def arduino_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def arduino_constrain(x,min_x,max_x):
    if x>=max_x:
        return max_x
    if x<=min_x:
        return min_x
    return round(x)
  


class tracker:
 def run(tracklog):
  c2s=client2server()  
  c2s.moveLeft(3)   
  tracklog.write("Received dx = {},  speed ={}  \n".format(1,1).encode())
      
  i=0


  max_speed=55
  K_p=10
  K_d=0
  K_i=0
  I=0
  last_dx=0
  delta_t=0.1
  f=1

  tracklog.write("Received dx = {},  speed ={}  \n".format(0,1).encode())

    
  speed=0
  while i==0:
   
   
    status=c2s.getStatus()
    dx=int(status)&0x0fff
    
    #tracklog.write("Received dx = {},  speed ={}  \n".format(dx,speed).encode())

    if(dx>2048):
        dx=dx-4096


    sec=1#####time.time()
    if f==1:
        f=0
    else:
    	delta_t=sec-last_sec
    last_sec=sec

#------------------------------------
    P=dx
    D=(dx-last_dx)/delta_t
    I=I+dx*delta_t
    last_dx=dx

    speed=K_p*P+K_d*D+K_i*I
    speed=arduino_constrain(speed,-max_speed,max_speed)
    #tracklog.write("Received dx = {},  speed = {} \n".format(dx,speed).encode())#tracklog.write('dx - {')#("Received %d %d %d %d %d\n" % (dx,state,position,ticks,speed))
    if True:#(abs(int(dx))<500):
        if 0:#(abs(speed)<2):
             c2s.moveStop()
        else:
             if(speed>0):
                  c2s.moveLeft(speed)  # -----------------возможно поменять местами -------------
             else:
                  c2s.moveRight(abs(speed))
#               return
  
#c2s.__finit__
