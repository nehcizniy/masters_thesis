import os
import pandas as pd

# Get all excel files in current directory
files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('.xlsx')]

# Loop through all files
for file in files:
    # Load spreadsheet ('None' to specify there is no header)
    xl = pd.read_excel(file, header=None)

    # Find row in first column where value is 0.95
    scaling_row = xl.loc[xl[xl.columns[0]] == 0.95]

    if scaling_row.empty:
        print(f"No value 0.95 in first column of file {file}")
        continue

    # Take value of second column in this row
    scaling_value = scaling_row[scaling_row.columns[1]].values[0]

    # Scale down 2nd, 3rd, 4th column
    xl.iloc[:, 1:4] /= scaling_value

    # Save the scaled-down dataframe back into Excel file
    xl.to_excel(file, index=False, header=False)

print("Done processing all Excel files")