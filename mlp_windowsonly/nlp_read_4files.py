Here is the updated script to handle four file inputs with matplotlib transparency. It is also handled different colors for different datasets.

```python
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from sklearn.neural_network import MLPRegressor

np.random.seed(0)

# Define colors and markers for each year
marker_dict = {2004: '.', 2013: 's'}
color_dict = {2004: 'b', 2013: 'r'}

# ----------------------------------------------------------------------
#  Charged pion from PPG101
def read_data_from_excel(filename, max_pt=3.0):
    df = pd.read_excel(filename, header=None)
    df.columns = ["pt", "invariant_yield", "stat_error", "sys_error"]
    df = df[df['pt'] <= max_pt]
    pt = df['pt'].to_numpy()
    invariant_yield = df['invariant_yield'].to_numpy()
    stat_error = df['stat_error'].to_numpy()
    sys_error = df['sys_error'].to_numpy()
    print(df)
    return pt, invariant_yield, stat_error, sys_error


# File prompt for input
print('Enter four files in order (2004 - k+, k-, 2013 - k+, k-):')
filepath_dict = {2004: {}, 2013: {}}

for year in filepath_dict.keys():
    for charge in ['k+', 'k-']:
        filepath_dict[year][charge] = input(f'{year} {charge} data filepath: ')

print('Enter filename for saving output:')
wfile = input()

max_pt_value = 3.0
data_dict = {}

plt.figure()

# Loop through years and charges and perform operations
for year in filepath_dict.keys():
    for charge in ['k+', 'k-']:
        data_dict[year] = {}
        data_dict[year][charge] = {}
        # Extract data
        data_dict[year][charge]['x'], data_dict[year][charge]['y'], data_dict[year][charge]['ey'], data_dict[year][charge]['sys'] = read_data_from_excel(filepath_dict[year][charge], max_pt = max_pt_value)
        # Plot with different colors and markers
        plt.errorbar(data_dict[year][charge]['x'].T, data_dict[year][charge]['y'], data_dict[year][charge]['ey'], fmt = f"{color_dict[year]}{marker_dict[year]}", markersize = 10, alpha = 0.5, label = f'{year} {charge}')

# Continue with the further operations on the data matrix

# .....

# At the end, where you plot, remember to make the background transparent:
plt.savefig("figure.png", transparent=True)
```
The code provided now works with four different file inputs. Please note that to distinguish between years, it plots markers and colors differently. For the year 2004 data, a blue '.' marker is used, and for the year 2013 data, a red 's' shape marker is used. Here the dataframe loading and extraction are generalized to allow four input file paths.

Further, alpha is set inside plt.errorbar() to make the plotted data points semi-transparent. You can adjust the alpha value (between 0 and 1) to control the transparency of your plots.

In plt.savefig(), the transparent argument is set to True. This results in the area around the plot being saved as transparent in supported file formats (e.g., PNG).

You will also need to adjust the continuation part of the code (marked with `# .....`) according to the relations and computations you need to enforce on the data from the new files.

Please make sure to replace `"figure.png"` in `plt.savefig()` with your preferred file name or file directory.