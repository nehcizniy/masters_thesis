import pandas as pd
import os
import numpy as np
import glob

dndeta = [5.1,4.0,4.0,3.0]
# Get list of all excel files
file_list = glob.glob('./*.xlsx')
files = sorted(file_list)

# Create a list to hold all data
all_data = []

for file, d in zip(files, dndeta):
    # Read each excel file and assign column names
    df = pd.read_excel(file, header=None, names=['a', 'b', 'c', 'd', 'e'])

    # Split the filename into parts
    parts = file.split('-')

    # Get f or k (2nd part) and g or i (4th part) from file name
    type1 = float(parts[1])
    type2 = float(parts[2])

    # Apply the transformation to the data
    df['pt'] = df['a']
    df['ptlow'] = df['a'] - df['e']
    df['pthigh'] = df['a'] + df['e']
    df['inv.yield'] = df['b']
    df['stat +'] = df['c']
    df['stat -'] =  - df['c']
    df['sys +'] = df['d']
    df['sys -'] =  - df['d']

    # Select only the 8 columns
    df = df[['pt', 'ptlow', 'pthigh', 'inv.yield', 'stat +', 'stat -', 'sys +', 'sys -']]

    # Add first row
    df.loc[-1] = ['pt', 'ptlow', 'pthigh', 'inv.yield', 'stat +', 'stat -', 'sys +', 'sys -']
    df.index = df.index + 1
    df = df.sort_index()


    # Add second row
    df.loc[-1] = ['centrality', type1, type2, d, 0, '', '', '']
    df.index = df.index + 1
    df = df.sort_index()


    # Append the data to the list
    all_data.append(df)

    # Add an empty row
    empty_row = pd.DataFrame([[np.nan] * 8], columns=df.columns)
    all_data.append(empty_row)

# Concatenate all data into one DataFrame
all_data_df = pd.concat(all_data, ignore_index=True)

# Save the new excel file
all_data_df.to_excel('phenix-pion-pAl-200.xlsx', header=None, index=False)