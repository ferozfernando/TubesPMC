import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("graph.csv")
yLabel = df.columns.values[1]
df.plot(kind = "line", x="T", y = yLabel)
plt.show()
