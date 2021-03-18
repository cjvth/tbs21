# prefix = '-py'
prefix = '-cpp'

inp = open(f'buf{prefix}.txt', 'rb')
out = open(f'buf2{prefix}.txt', 'wb')
a = inp.read(2)
while a:
    out.write(a)
    for i in range(16):
        out.write((int.from_bytes(a, 'big') ^ (1 << i)).to_bytes(2, 'big'))
    a = inp.read(2)