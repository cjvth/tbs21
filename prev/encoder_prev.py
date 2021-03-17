from io import BytesIO


def hamming_encode(data: list):
    data = data.copy()
    x = 1
    while x <= len(data):
        data.insert(x - 1, 0)
        x *= 2
    x = 1
    while x <= len(data):
        s = 0
        for i in range(x - 1, len(data), x * 2):
            for j in range(i, i + x):
                if j < len(data):
                    s += data[j]
        data[x - 1] = s % 2
        x *= 2
    return data


def encoder(filein: BytesIO, fileout: BytesIO):
    a = filein.read(1)
    while a:
        a = [int(i) for i in bin(int.from_bytes(a, 'big'))[2:].rjust(8, '0')]
        b = [hamming_encode(a[:4]) + [0], hamming_encode(a[4:]) + [0]]
        b = [int(''.join(map(str, i)), 2) for i in b]
        for i in b:
            fileout.write(i.to_bytes(1, 'big'))
        a = filein.read(1)

if __name__ == '__main__':
    encoder(open('test.txt', 'rb'), open('buf.txt', 'wb'))
