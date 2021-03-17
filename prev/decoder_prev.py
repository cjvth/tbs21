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


def converter(filein: BytesIO, fileout: BytesIO, filelog: BytesIO):
    while True:
        a = [filein.read(1) for i in range(3)]
        if not a[0] or not a[1] or not a[2]:
            break
        a = [[int(i) for i in bin(int.from_bytes(i, 'big'))[2:].rjust(8, '0')] for i in a]
        b = [a[0] + a[1][:4], a[1][4:] + a[2]]
        b = [hamming_decode(i) for i in b]
        b = [int(''.join(map(str, i)), 2) for i in b]
        for i in b:
            fileout.write(i.to_bytes(1, 'big'))
