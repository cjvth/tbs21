import random as r


inp = open('buf.txt', 'rb')
out = open('buf2.txt', 'wb')

#print(inp.read(1))
t=0
f=0
for a in inp.read():
    t+=1
    if f==0:
        rand=r.randint(0, 50)
        #print(bin(a))
        #print(rand,a)
        if rand<=7:
            out.write((a ^ (1 << rand)).to_bytes(1, 'big'))
            #print(bin(a ^ (1 << rand)))
        if rand>=8 and rand<=48:##########################
            out.write(a.to_bytes(1, 'big'))
        if rand>48 and t%2==1:
            #print(rand)
            f=r.randrange(2, 7,2)-1
            print(f)
            
    else:
        
        f-=1
    
        
inp.close()   
out.close()

