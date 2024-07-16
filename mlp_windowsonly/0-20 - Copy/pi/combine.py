import pandas as pd
import glob

# Find all the Excel files in the current directory
excel_files = glob.glob('*.xlsx')

data_frames = []

# Iterate through each Excel file
for file in excel_files:
    # Read each Excel file into a data frame
    df = pd.read_excel(file, header=None)

    # Append the data frame to the list
    data_frames.append(df)

# Concatenate all data frames in the list
combined_df = pd.concat(data_frames, ignore_index=True)

# Write the combined data frame to a new Excel file
combined_df.to_excel('combined.xlsx', index=False, header=False)