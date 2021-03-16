import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('data/z2_result6.dat', sep=' ', index_col='Tick')

for i, col in enumerate(df.columns):
    plt.plot(df[col], ['r', 'g', 'b'][i % 3])
    plt.show()
