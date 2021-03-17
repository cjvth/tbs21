import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('data/z2_result6.dat', sep=' ', index_col='Tick')
corr = pd.DataFrame()
for i in df.columns:
    a = pd.DataFrame(columns=[i+'c'])
    for j in range(0, 6000):
        a.loc[j] = abs(df[i] - df[i].shift(j)).iloc[6000:].sum()
    corr = corr.append(a)

for i, col in enumerate(corr.columns):
    plt.plot(corr[col], ['r', 'g', 'b'][i % 3])
    plt.show()
