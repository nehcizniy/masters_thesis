import numpy as np
import pandas as pd
import math

def read_data_from_excel(filename, min_pt=0.5, max_pt=3.0):
    df = pd.read_excel(filename, header=None)
    df.columns = ["pt", "invariant_yield", "stat_error", "sys_error", "dpT"]
    df = df[(df['pt'] > min_pt) & (df['pt'] <= max_pt)]
    pt = df['pt'].to_numpy()
    invariant_yield = df['invariant_yield'].to_numpy()
    stat_error = df['stat_error'].to_numpy()
    sys_error = df['sys_error'].to_numpy()
    dpT = df['dpT'].to_numpy()
    print(df)
    return pt, invariant_yield, stat_error, sys_error, dpT


print('First file:')
file1 = input()
print('Second file:')
file2 = input()
#print('Save file as:')
#wfile = input()

min_pt_value = 0.5
max_pt_value = 2.0

x_file1, y_1, stat_1, sys_1,dx_1 = read_data_from_excel(file1, min_pt=min_pt_value, max_pt=max_pt_value ) #2013-pi+-20-40-AuAu-phenix.xlsx
x_file2, y_2, stat_2, sys_2,dx_2 = read_data_from_excel(file2, min_pt=min_pt_value, max_pt=max_pt_value) #2013-pi--20-40-AuAu-phenix.xlsx

file1 = file1[:-5]
file2 = file2[:-5]
#print(file1)
x_1_bin_low = [x - y for x, y in zip(x_file1,dx_1)]
x_1_bin_high = [x + y for x, y in zip(x_file1,dx_1)]
x_2_bin_low = [x - y for x, y in zip(x_file2,dx_2)]
x_2_bin_high = [x + y for x, y in zip(x_file2,dx_2)]
y_file1 = [2*math.pi*x*y for x, y in zip(x_file1,y_1)]
y_file2 = [2*math.pi*x*y for x, y in zip(x_file2,y_2)]
stat_file1 = [2*math.pi*x*y for x, y in zip(x_file1,stat_1)]
stat_file2 = [2*math.pi*x*y for x, y in zip(x_file2,stat_2)]
sys_file1 = [2*math.pi*x*y for x, y in zip(x_file1,sys_1)]
sys_file2 = [2*math.pi*x*y for x, y in zip(x_file2,sys_2)]
y_file1 = np.array(y_file1)
y_file2 = np.array(y_file2)
stat_file1 = np.array(stat_file1)
stat_file2 = np.array(stat_file2)
sys_file1 = np.array(sys_file1)
sys_file2 = np.array(sys_file2)

sum_data = sum([a * b for a, b in zip(x_file1, y_file1)])+sum([a * b for a, b in zip(x_file2, y_file2)])
sum_weight_data = sum(y_file1) + sum(y_file2)
mean_pt_data = sum_data/sum_weight_data
mean_pt_data_stat_error = np.sqrt(sum([a*a for a in stat_file1])+sum([a*a for a in stat_file2]))/(len(stat_file1)+len(stat_file2))
mean_pt_data_sys_error = 0.5*np.average([a/b for a, b in zip(sys_file1, y_file1)]) + 0.5*np.average([a/b for a, b in zip(sys_file2, y_file2)])
print(mean_pt_data)
print(mean_pt_data_stat_error)