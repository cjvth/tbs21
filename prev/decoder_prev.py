from io import BytesIO


def hamming_decode(message: list):
    count = message.copy()
    x = 1
    while x <= len(count):
        count[x - 1] = 0
        x *= 2
    x = 1
    while x <= len(count):
        s = 0
        for i in range(x - 1, len(count), x * 2):
            for j in range(i, i + x):
                if j < len(count):
                    s += count[j]
        count[x - 1] = s % 2
        x *= 2
    x //= 2
    x0 = x
    wrong = []
    while x >= 1:
        if message[x - 1] != count[x - 1]:
            wrong.append(x)
        x //= 2
    if len(wrong) > 1 and sum(wrong) < len(count):
        count[sum(wrong) - 1] ^= 1
    x = x0
    while x >= 1:
        c = count.pop(x - 1)
        x //= 2

    return count


def decoder(filein: BytesIO, fileout: BytesIO, filelog: BytesIO):
    a = [filein.read(1) for i in range(2)]
    while True:
        if not a[0] or not a[1]:
            break
        a = [[int(i) for i in bin(int.from_bytes(i, 'big'))[2:].rjust(8, '0')] for i in a]
        b = [i[:7] for i in a]
        b = [hamming_decode(i) for i in b]
        b = b[0] + b[1]
        b = int(''.join(map(str, b)), 2)
        fileout.write(b.to_bytes(1, 'big'))
        a = [filein.read(1) for i in range(2)]



if __name__ == '__main__':
    decoder(open('buf.txt', 'rb'), open('out.txt', 'wb'), open('test.txt', 'rb'))