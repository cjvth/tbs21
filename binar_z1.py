import matplotlib.pyplot as plt
import pandas as pd
from hamming_list import hamming_decode, hamming_encode

cycles = {'PD1': (1950, 3150),
          'PD2': (1030, 2010),
          'PD3': (840, 1600)}

DRAW = False

f = open('data/z1.dat', 'r')

df = pd.read_csv('data/z1.dat', sep=' ', index_col='Tick')

for i in cycles:
    ch = []
    print(i)
    data = df[i].loc[cycles[i][0]:cycles[i][1]]
    # tresh = (data.max() + data.min()) // 2
    tresh = 50
    cur = int(data.iloc[0] > tresh)
    prev = data.index[0]
    for j in data.index:
        if cur ^ (data[j] > tresh):
            ch.append([j, j - prev, cur])
            prev = j
            cur = 1 - cur
    ch = ch[1:]
    print(min(filter(lambda x: x[2] == 0, ch), key=lambda x: x[1])[1], min(filter(lambda x: x[2] == 1, ch), key=lambda x: x[1])[1])
    ml = (min(filter(lambda x: x[2] == 0, ch), key=lambda x: x[1])[1] + min(filter(lambda x: x[2] == 1, ch), key=lambda x: x[1])[1]) // 2
    er = []
    li = []
    for j in ch:
        li += [j[2]] * round(j[1] / ml)
        er.append((j[2], j[1] / ml))
    print(li)
    print(er)
    print(hamming_decode(li, True))
    print(hamming_decode(li[::-1], True))
    print()

if DRAW:
    for i in cycles:
        plt.plot(df[i].loc[cycles[i][0]:cycles[i][1]], 'r')
        # plt.plot(df[i][:3000], 'r')
        plt.show()
