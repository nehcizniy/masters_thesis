import numpy as np
import pandas as pd
import math
from matplotlib import pyplot as plt

from sklearn.neural_network import MLPRegressor

np.random.seed(0)


# ----------------------------------------------------------------------
#  Charged pion from PPG101
def read_data_from_excel(filename, max_pt=3.0):
    df = pd.read_excel(filename, header=None)
    df.columns = ["pt", "invariant_yield", "stat_error", "sys_error", "dpT"]
    df = df[df['pt'] <= max_pt]
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

max_pt_value = 2.0

x_file1, y_1, stat_1, sys_1,dx_1 = read_data_from_excel(file1,max_pt=max_pt_value ) #2013-pi+-20-40-AuAu-phenix.xlsx
x_file2, y_2, stat_2, sys_2,dx_2 = read_data_from_excel(file2,max_pt=max_pt_value) #2013-pi--20-40-AuAu-phenix.xlsx

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
#print(mean_pt_data)
#print(mean_pt_data_stat_error)

val = []

val_ppg101 = []


plt.figure()

plt.errorbar(x_file1.T, y_1, stat_1, fmt="b.", markersize=10, label=file1)
plt.errorbar(x_file2.T, y_2, stat_2, fmt="bs", markersize=5, label=file2)

flag = False
for i in range(1000):
    flag = False

    #print(i)

    X = []

    Y = []

    dx = []

    dy = []

    scale = 1

    rndm = 0  # np.random.normal(0, 0.001)
    x2a = x_file1  # np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.normal(0, 1)  # 1 - np.random.uniform(-1,1)
    if np.random.uniform(0, 1) > 0.5:
        coin = 1
    else:
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, stat_1)) + np.square(rndm * y_1))
    check1 = np.add(y_1, coin * noise)
    #print(check1)
    for a in check1:
        if a <= 0:
            flag = True
            break
    if flag:
        print(i)
        continue
    y2a = np.log10(np.multiply(np.add(y_1, coin * noise), scale))

    rndm = 0  # np.random.normal(0, 0.001)
    x2b = x_file2  # np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.normal(0, 1)  # 1 - np.random.uniform(-1,1)
    if np.random.uniform(0, 1) > 0.5:
        coin = 1
    else:
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, stat_2)) + np.square(rndm * sys_2))
    check2 = np.add(y_2, coin * noise)
    #print(check2)
    for a in check2:
        if a <= 0:
            flag = True
            break
    if flag:
        print(i)
        continue
    y2b = np.log10(np.multiply(np.add(y_2, coin * noise), scale))

    X = np.append(X, x2a)
    X = np.append(X, x2b)

    X = np.atleast_2d(X).T

    Y = np.append(Y, y2a)
    Y = np.append(Y, y2b)

    # Instantiate an MLP model
    gp = MLPRegressor(max_iter=1000000, solver='lbfgs', activation='relu').fit(X, Y)

    # x = np.atleast_2d(np.linspace(-0.5, 1.5, 5000)).T
    x = np.atleast_2d(np.linspace(0.5, 2., 3000)).T
    y_pred = gp.predict(x)
    val.append(y_pred)

    # y_pred = gp.predict(np.log10(np.atleast_2d(x_ppg101)).T)
    y_pred = gp.predict(np.atleast_2d(x_file1).T)
    val_ppg101.append(y_pred)

average = np.average(val, axis=0)
sig = np.std(val, axis=0)

avg_ppg101 = np.average(val_ppg101, axis=0)

sig_ppg101 = np.average(val_ppg101, axis=0)

rat_piplus_ppg101 = np.divide(y_1, 10 ** avg_ppg101)
rat_piminus_ppg101 = np.divide(y_2, 10 ** avg_ppg101)


erat_piplus_ppg101 = np.divide(stat_1, 10 ** avg_ppg101)
erat_piminus_ppg101 = np.divide(stat_2, 10 ** avg_ppg101)


x_coor = x
y_coor = np.atleast_2d(10 ** average).T
e_coor = np.atleast_2d(np.multiply(10 ** average, sig)).T

#end of MLP

with open(file1 + '.txt', 'w') as f:
    lis = [list(map(float, x_coor.flatten())), list(map(float, y_coor.flatten())), list(map(float, e_coor.flatten()))]
    for entry in zip(*lis):
        f.write("{0}\t{1}\t{2}\n".format(*entry))

y_coor = [2*math.pi*x*y for x, y in zip(x_coor,y_coor)]
e_coor = [2*math.pi*x*y for x, y in zip(x_coor,e_coor)]
y_coor = np.array(y_coor)
e_coor = np.array(e_coor)



sum_x_full_range_of_fit = sum([a * b for a, b in zip(x_coor, y_coor)])
sum_weight_full_range_of_fit = sum(y_coor)
mean_pt_full_range_of_fit = sum_x_full_range_of_fit/sum_weight_full_range_of_fit
mean_pt_error_full_range_of_fit = np.sqrt(sum([a*a for a in e_coor]))/(len(e_coor))
print(mean_pt_full_range_of_fit)
print(mean_pt_error_full_range_of_fit)

sum_x_data_range_of_fit=0
sum_weight_data_range_of_fit=0
for i in range(len(x_coor)):
    if x_coor[i] >= x_file1[0] or x_coor[i] >= x_file2[0]:
        if x_coor[i] <= x_file1[-1] or x_coor[i] <= x_file2[-1]:
            sum_x_data_range_of_fit += x_coor[i] * y_coor[i]
            sum_weight_data_range_of_fit += y_coor[i]
mean_pt_data_range_of_fit = sum_x_data_range_of_fit/sum_weight_data_range_of_fit
#print(mean_pt_data_range_of_fit)
ratio = mean_pt_full_range_of_fit/mean_pt_data_range_of_fit
#print(ratio)

true_mean_pt = mean_pt_data*ratio
true_mean_pt_stat = mean_pt_data_stat_error*ratio
true_mean_pt_sys = true_mean_pt * mean_pt_data_sys_error
#print(true_mean_pt)
#print(true_mean_pt_stat)
#print(true_mean_pt_sys)


#with open(wfile + '.txt', 'w') as f:
#    lis = [x_coor, y_coor, e_coor]
#    for entry in zip(*lis):
#        f.write("{0}\t{1}\t{2}\n".format(*entry))



plt.plot(x, 10 ** average)
plt.fill(
    np.concatenate([x_coor, x_coor[::-1]]),
    np.concatenate([y_coor - 1.00 * e_coor, (y_coor + 1.00 * e_coor)[::-1]]),
    alpha=0.,
    fc="r",
    ec="None",
    label="1 sigma",
)

plt.xlabel("$p_{T}$ [GeV]")
plt.xlim(0.0,3.0)
plt.ylabel("Invariant yield")
plt.yscale('log')
plt.ylim(1e-8, 1000.0)
plt.legend(loc="upper right")
plt.savefig(file1 + '.png')

plt.figure()

plt.errorbar(x_file1.T, rat_piplus_ppg101, erat_piplus_ppg101, fmt="b.", markersize=10, label=file1)
plt.errorbar(x_file2.T, rat_piminus_ppg101, erat_piminus_ppg101, fmt="bs", markersize=5, label=file2)

plt.xlabel("$p_{T}$ [GeV]")
plt.ylabel("$ratio$")
plt.ylim(0.5, 1.5)
# plt.legend(loc="upper right")

plt.show()