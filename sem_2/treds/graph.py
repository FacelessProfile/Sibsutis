import pandas as pd
import termplotlib as tpl

# Загружаем CSV
df = pd.read_csv('results.csv')

# Создаём сводную таблицу
pivot = df.pivot_table(
    index='matrix_size',
    columns='threads',
    values='time_ms',
    aggfunc='mean'
).reset_index()

# Создаём график по каждой колонке (threads)
fig = tpl.figure()
for thr in pivot.columns.drop('matrix_size'):
    x = pivot['matrix_size'].to_numpy()
    y = pivot[thr].to_numpy()
    fig.plot(
        x,
        y,
        label=f"{thr} threads",
        width=60,
        height=20
    )

fig.show()

