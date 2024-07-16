import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from sklearn.neural_network import MLPRegressor

np.random.seed(0)


# ----------------------------------------------------------------------
#  Charged pion from PPG101
def read_data_from_excel(filename):
    df = pd.read_excel(filename, header=None)
    df.columns = ["pt", "invariant_yield", "stat_error", "sys_error"]
    pt = df['pt'].to_numpy()
    invariant_yield = df['invariant_yield'].to_numpy()
    stat_error = df['stat_error'].to_numpy()
    sys_error = df['sys_error'].to_numpy()
    print(df)
    return pt, invariant_yield, stat_error, sys_error


print('First file:')
file1 = input()
print('Second file:')
file2 = input()
print('Third file:')
file3 = input()
print('Save file as:')
wfile = input()

x_ppg101, y_piplus_ppg101, ey_piplus_ppg101, sys_piplus_ppg101 = read_data_from_excel(file1 + str(".xlsx")) #2013-pi+-20-40-AuAu-phenix.xlsx
x_ppg103, y_piminus_ppg101, ey_piminus_ppg101, sys_piminus_ppg101 = read_data_from_excel(file2 + str(".xlsx")) #2013-pi--20-40-AuAu-phenix.xlsx
x_ppg202, y_pizero_ppg202, ey_pizero_ppg202, sys_pizero_ppg202 = read_data_from_excel(file3 + str(".xlsx")) #2008-pi0-20-40-AuAu-phenix.xlsx

sum_data= sum([a * b for a, b in zip(x_ppg101, y_piplus_ppg101)])+sum([a * b for a, b in zip(x_ppg103, y_piminus_ppg101)])#sum([a * b for a, b in zip(x_ppg202, y_pizero_ppg202)])
sum_weight_data = sum(y_piplus_ppg101)+sum(y_piminus_ppg101)#sum(y_pizero_ppg202)
mean_pt_data = sum_data/sum_weight_data
mean_pt_data_stat_error = np.sqrt(sum([a*a for a in ey_piplus_ppg101])+sum([a*a for a in ey_piminus_ppg101]))/(len(ey_piplus_ppg101)+len(ey_piminus_ppg101))
mean_pt_data_sys_error = np.sqrt(sum([a*a for a in sys_piplus_ppg101])+sum([a*a for a in sys_piminus_ppg101]))/(len(ey_piplus_ppg101)+len(ey_piminus_ppg101))
mean_pt_pi0 = sum([a * b for a, b in zip(x_ppg202, y_pizero_ppg202)])/sum(y_pizero_ppg202)
mean_pt_pi0_stat_error = np.sqrt(sum([a*a for a in ey_pizero_ppg202]))/len(ey_pizero_ppg202)
print(mean_pt_data)
print(mean_pt_data_stat_error)
print(mean_pt_data_sys_error)
val = []

val_ppg101 = []
val_ppg202 = []

plt.figure()

plt.errorbar(x_ppg101.T, y_piplus_ppg101, ey_piplus_ppg101, fmt="b.", markersize=10, label=file1)
plt.errorbar(x_ppg103.T, y_piminus_ppg101, ey_piminus_ppg101, fmt="bs", markersize=5, label=file2)
plt.errorbar(x_ppg202.T, y_pizero_ppg202, ey_pizero_ppg202, fmt="gs", markersize=5, label=file3)
flag = False
for i in range(1000):
    flag = False

    #print(i)

    X = []

    Y = []

    dy = []

    scale = 1

    rndm = 0  # np.random.normal(0, 0.001)
    x2a = x_ppg101  # np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.normal(0, 1)  # 1 - np.random.uniform(-1,1)
    if np.random.uniform(0, 1) > 0.5:
        coin = 1
    else:
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_piplus_ppg101)) + np.square(rndm * sys_piplus_ppg101))
    check1 = np.add(y_piplus_ppg101, coin * noise)
    #print(check1)
    for a in check1:
        if a <= 0:
            flag = True
            break
    if flag:
        print(i)
        continue
    y2a = np.log10(np.multiply(np.add(y_piplus_ppg101, coin * noise), scale))

    rndm = 0  # np.random.normal(0, 0.001)
    x2b = x_ppg103  # np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.normal(0, 1)  # 1 - np.random.uniform(-1,1)
    if np.random.uniform(0, 1) > 0.5:
        coin = 1
    else:
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_piminus_ppg101)) + np.square(rndm * sys_piminus_ppg101))
    check2 = np.add(y_piminus_ppg101, coin * noise)
    #print(check2)
    for a in check2:
        if a <= 0:
            flag = True
            break
    if flag:
        print(i)
        continue
    y2b = np.log10(np.multiply(np.add(y_piminus_ppg101, coin * noise), scale))

    scale = 1

    rndm = 0  # np.random.normal(0, 0.001)
    x3a = x_ppg202  # np.log10(np.add(x_ppg202,rndm))

    rndm = np.random.normal(0, 1)  # 1 - np.random.uniform(-1,1)
    if np.random.uniform(0, 1) > 0.5:
        coin = 1
    else:
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_pizero_ppg202)) + np.square(rndm * sys_pizero_ppg202))
    check3 = np.add(y_pizero_ppg202, coin * noise)
    #print(check3)
    for a in check3:
        if a <= 0:
            flag = True
            break
    if flag:
        print(i)
        continue
    y3a = np.log10(np.multiply(np.add(y_pizero_ppg202, coin * noise), scale))

    X = np.append(X, x3a)
    X = np.append(X, x2a)
    X = np.append(X, x2b)

    X = np.atleast_2d(X).T

    Y = np.append(Y, y3a)
    Y = np.append(Y, y2a)
    Y = np.append(Y, y2b)

    # Instantiate an MLP model
    gp = MLPRegressor(max_iter=1000000, solver='lbfgs', activation='relu').fit(X, Y)

    # x = np.atleast_2d(np.linspace(-0.5, 1.5, 5000)).T
    x = np.atleast_2d(np.linspace(0.01, 30.01, 3000)).T
    y_pred = gp.predict(x)
    val.append(y_pred)

    # y_pred = gp.predict(np.log10(np.atleast_2d(x_ppg101)).T)
    y_pred = gp.predict(np.atleast_2d(x_ppg101).T)
    val_ppg101.append(y_pred)

    # y_pred = gp.predict(np.log10(np.atleast_2d(x_ppg202)).T)
    y_pred = gp.predict(np.atleast_2d(x_ppg202).T)
    val_ppg202.append(y_pred)

average = np.average(val, axis=0)
sig = np.std(val, axis=0)

avg_ppg101 = np.average(val_ppg101, axis=0)
avg_ppg202 = np.average(val_ppg202, axis=0)

sig_ppg101 = np.average(val_ppg101, axis=0)
sig_ppg202 = np.average(val_ppg202, axis=0)

rat_piplus_ppg101 = np.divide(y_piplus_ppg101, 10 ** avg_ppg101)
rat_piminus_ppg101 = np.divide(y_piminus_ppg101, 10 ** avg_ppg101)

rat_pizero_ppg202 = np.divide(y_pizero_ppg202, 10 ** avg_ppg202)

erat_piplus_ppg101 = np.divide(ey_piplus_ppg101, 10 ** avg_ppg101)
erat_piminus_ppg101 = np.divide(ey_piminus_ppg101, 10 ** avg_ppg101)

erat_pizero_ppg202 = np.divide(ey_pizero_ppg202, 10 ** avg_ppg202)

x_coor = x
y_coor = np.atleast_2d(10 ** average).T
e_coor = np.atleast_2d(np.multiply(10 ** average, sig)).T

sum_x_full_range_of_fit = sum([a * b for a, b in zip(x_coor, y_coor)])
sum_weight_full_range_of_fit = sum(y_coor)
mean_pt_full_range_of_fit = sum_x_full_range_of_fit/sum_weight_full_range_of_fit
print(mean_pt_full_range_of_fit)

sum_x_data_range_of_fit=0
sum_weight_data_range_of_fit=0
for i in range(len(x_coor)):
    if x_coor[i] >= x_ppg101[0] or x_coor[i] >= x_ppg103[0] or x_coor[i] >= x_ppg202[0]:
        if x_coor[i] <= x_ppg101[-1] or x_coor[i] <= x_ppg103[-1] or x_coor[i] <= x_ppg202[-1]:
            sum_x_data_range_of_fit += x_coor[i] * y_coor[i]
            sum_weight_data_range_of_fit += y_coor[i]
mean_pt_data_range_of_fit = sum_x_data_range_of_fit/sum_weight_data_range_of_fit
print(mean_pt_data_range_of_fit)
ratio = mean_pt_full_range_of_fit/mean_pt_data_range_of_fit
print(ratio)
true_mean_pt = mean_pt_data*ratio
true_mean_pt_stat = mean_pt_data_stat_error*ratio
true_mean_pt_sys = mean_pt_data_sys_error*ratio
print(true_mean_pt)
print(true_mean_pt_stat)
print(true_mean_pt_sys)

with open(wfile + '.txt', 'w') as f:
    lis = [x_coor, y_coor, e_coor]
    for entry in zip(*lis):
        f.write("{0}\t{1}\t{2}\n".format(*entry))

plt.plot(x, 10 ** average)
plt.fill(
    np.concatenate([x_coor, x_coor[::-1]]),
    np.concatenate([y_coor - 1.00 * e_coor, (y_coor + 1.00 * e_coor)[::-1]]),
    alpha=0.5,
    fc="r",
    ec="None",
    label="1 sigma",
)

plt.xlabel("$p_{T}$ [GeV]")
plt.ylabel("Invariant yield")
plt.yscale('log')
plt.ylim(1e-12, 100.0)
plt.legend(loc="upper right")

plt.figure()

plt.errorbar(x_ppg101.T, rat_piplus_ppg101, erat_piplus_ppg101, fmt="b.", markersize=10, label=file1)
plt.errorbar(x_ppg103.T, rat_piminus_ppg101, erat_piminus_ppg101, fmt="bs", markersize=5, label=file2)
plt.errorbar(x_ppg202.T, rat_pizero_ppg202, erat_pizero_ppg202, fmt="gs", markersize=5, label=file3)

plt.xlabel("$p_{T}$ [GeV]")
plt.ylabel("$ratio$")
plt.ylim(0.5, 1.5)
# plt.legend(loc="upper right")

plt.show()
