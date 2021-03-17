import matplotlib.pyplot as plt
import pandas as pd

DRAW = True

df = pd.DataFrame({'PD1': pd.read_csv('data/z3_pik1.dat', sep=' ', index_col='Tick')['PD3'],
                   'PD2': pd.read_csv('data/z3_pik2.dat', sep=' ', index_col='Tick')['PD3'],
                   'PD3': pd.read_csv('data/z3_pik3.dat', sep=' ', index_col='Tick')['PD3']})

ch = []
data = df['PD2']

tresh = {'PD1': 55, 'PD2': 50, 'PD3': 55}
piks = {'PD1bd': 25, 'PD2bd': 25, 'PD3bd': 25}

for i in tresh:
    df[i+'b'] = (df[i] > tresh[i]).astype('int')
    df[i+'bd'] = df[i+'b'].diff().abs()

print('способ 1')
for i in piks:
    l1 = df.loc[:1000][df[i].loc[:1000] == 1].index[-1]
    r1 = df.loc[1000:8000][df[i].loc[1000:8000] == 1].index[0]
    l2 = df.loc[:8000][df[i].loc[:8000] == 1].index[-1]
    r2 = df.loc[8000:15000][df[i].loc[8000:15000] == 1].index[0]
    l3 = df.loc[8000:15000][df[i].loc[8000:15000] == 1].index[-1]
    r3 = df.loc[15000:][df[i].loc[15000:] == 1].index[0]
    s1 = df[i].loc[1000:8000].sum() + (r1 - 1000) / (r1 - l1) + (8000 - l2) / (r2 - l1)
    s2 = df[i].loc[8000:15000].sum() + (r2 - 8000) / (r2 - l2) + (15000 - l3) / (r3 - l3)
    s1 *= 360 / 2 / piks[i]
    s2 *= 360 / 2 / piks[i]
    print(i, (s2 - s1) / 14 ** 2)


print('способ 2')
for i in piks:
    changes = df[df[i] == 1].index[12:-12]
    s = len(changes) // 2
    t1 = (changes[s-1] - changes[0]) * 2 / 1000
    t2 = (changes[s*2-1] - changes[s]) * 2 / 1000
    s *= 360 / 50
    k = (2 * t1 * t2 + t2 ** 2 - t1 ** 2) / (2 * t1 - 2 * t2)  # v0 = a * k
    a = 2 * s / (2 * k * t1 + t1 ** 2)
    print(i, a)


if DRAW:
    for i, col in enumerate(df.columns):
        fig, ax = plt.subplots()
        ax.plot(df[col].dropna(), 'rgbcmyk'[i % 7])
        ax.set_title(col)
        plt.show()
