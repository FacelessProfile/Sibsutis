import pandas as pd
import gnuplotlib as gp
import numpy as np
import shutil  # for terminal size

# Read the CSV file
df = pd.read_csv("results.csv")

# Create a pivot table: rows = matrix size, columns = threads, values = time
pivot = df.pivot_table(
    index="matrix_size",
    columns="threads",
    values="time_ms",
    aggfunc="mean"
).reset_index()

# Detect terminal size (columns x rows)
columns, rows = shutil.get_terminal_size(fallback=(100, 30))

# Prepare plots: one curve per thread count
plots = []
for thread_count in pivot.columns.drop("matrix_size"):
    x = pivot["matrix_size"].to_numpy()
    y = pivot[thread_count].to_numpy()
    plots.append((x, y, {
        'with': 'linespoints',
        'legend': f"{thread_count} thread(s)"
    }))

# Plot using ASCII terminal with axis labels and grid
gp.plot(
    *plots,
    terminal="pngcairo size 800,600",
    output="graph.png",
    title="Matrix Multiplication Time",
    xlabel="Matrix Size (N)",
    ylabel="Time (ms)",
    _set="grid"
)

