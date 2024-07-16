import os
import pandas as pd

# Get all files in current directory
files = os.listdir('.')

# Filter out those files which are not xlsx
xlsx_files = [f for f in files if f[-4:] == 'xlsx']

# Loop over all xlsx files and convert them to txt
for file in xlsx_files:
    # Read xlsx file using pandas
    df = pd.read_excel(file, engine='openpyxl')

    # Convert to txt file with tab delimiters
    df.to_csv(file[:-4] + 'txt', sep='\t', index=False)