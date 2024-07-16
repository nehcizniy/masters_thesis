import numpy as np
from matplotlib import pyplot as plt

from sklearn.neural_network import MLPRegressor

np.random.seed(0)

# ----------------------------------------------------------------------
#  Charged pion from PPG101

x_ppg101 = np.array([0.35, 0.45, 0.55, 0.65, 0.75, 0.85, 0.95, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.05, 2.15, 2.25, 2.35, 2.45, 2.55, 2.65, 2.75, 2.85, 2.95])

y_piplus_ppg101 = np.array([27.7000, 14.5000, 7.7600, 4.3900, 2.6500, 1.5900, 1.0100, 0.6450, 0.4180, 0.2760, 0.1880, 0.1290, 0.0907, 0.0652, 0.0448, 0.0345, 0.0249, 0.0183, 0.0137, 0.0113, 0.0082, 0.0067, 0.0054, 0.0043, 0.0030, 0.0025, 0.0018])
ey_piplus_ppg101 = np.array([0.3000, 0.1500, 0.0860, 0.0530, 0.0350, 0.0220, 0.0150, 0.0110, 0.0072, 0.0050, 0.0036, 0.0026, 0.0019, 0.0014, 0.0010, 0.0008, 0.0006, 0.0005, 0.0004, 0.0004, 0.0003, 0.0003, 0.0002, 0.0002, 0.0002, 0.0001, 0.0001])
sys_piplus_ppg101 = np.array([1.9000, 1.0000, 0.5400, 0.3100, 0.1900, 0.1100, 0.0710, 0.0450, 0.0290, 0.0190, 0.0130, 0.0090, 0.0064, 0.0046, 0.0031, 0.0024, 0.0017, 0.0013, 0.0010, 0.0008, 0.0006, 0.0005, 0.0004, 0.0003, 0.0002, 0.0002, 0.0001])

y_piminus_ppg101 = np.array([26.3000, 14.0000, 7.9100, 4.4400, 2.6900, 1.6000, 0.9830, 0.6300, 0.4360, 0.2790, 0.1900, 0.1290, 0.0905, 0.0647, 0.0469, 0.0340, 0.0256, 0.0181, 0.0133, 0.0103, 0.0075, 0.0063, 0.0050, 0.0035, 0.0028, 0.0022, 0.0017]) 
ey_piminus_ppg101 = np.array([0.3700, 0.2000, 0.1200, 0.0700, 0.0460, 0.0290, 0.0190, 0.0130, 0.0095, 0.0063, 0.0044, 0.0031, 0.0023, 0.0017, 0.0012, 0.0009, 0.0007, 0.0006, 0.0004, 0.0004, 0.0003, 0.0003, 0.0002, 0.0002, 0.0002, 0.0002, 0.0001]) 
sys_piminus_ppg101 = np.array([1.8000, 0.9800, 0.5500, 0.3100, 0.1900, 0.1100, 0.0690, 0.0440, 0.0310, 0.0200, 0.0130, 0.0090, 0.0063, 0.0045, 0.0033, 0.0024, 0.0018, 0.0013, 0.0009, 0.0007, 0.0005, 0.0004, 0.0004, 0.0002, 0.0002, 0.0002, 0.0001])

# ----------------------------------------------------------------------
#  Neutral pion from PPG202

x_ppg202 = np.array([0.625, 0.875, 1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.25, 7.75, 8.25, 8.75, 9.25, 9.75, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.50])
y_pizero_ppg202 = np.array([5.606e+00, 1.705e+00, 3.481e-01, 5.474e-02, 1.177e-02, 3.026e-03, 9.061e-04, 3.101e-04, 1.151e-04, 4.767e-05, 2.097e-05, 1.010e-05, 5.104e-06, 2.735e-06, 1.541e-06, 9.085e-07, 5.456e-07, 3.384e-07, 2.140e-07, 1.353e-07, 5.328e-08, 1.368e-08, 4.014e-09, 1.297e-09, 4.859e-10, 1.623e-10, 6.688e-11])
ey_pizero_ppg202 = np.array([2.895e-03, 9.304e-04, 1.558e-04, 3.778e-05, 1.359e-05, 5.779e-06, 2.787e-06, 1.471e-06, 5.854e-07, 3.405e-07, 2.081e-07, 7.930e-08, 4.621e-08, 2.762e-08, 8.443e-09, 6.193e-09, 4.556e-09, 3.352e-09, 2.606e-09, 1.992e-09, 6.267e-10, 2.286e-10, 1.109e-10, 5.706e-11, 3.433e-11, 2.319e-11, 1.390e-11])
sys_pizero_ppg202 = np.array([7.078e-01, 1.243e-01, 1.872e-02, 3.245e-03, 7.525e-04, 2.041e-04, 6.406e-05, 2.273e-05, 8.814e-06, 3.715e-06, 1.660e-06, 8.090e-07, 4.141e-07, 2.233e-07, 1.260e-07, 7.470e-08, 4.504e-08, 2.804e-08, 1.786e-08, 1.133e-08, 4.647e-09, 1.282e-09, 4.223e-10, 1.502e-10, 6.334e-11, 2.319e-11, 1.115e-11])

val = []

val_ppg101 = []
val_ppg202 = []

plt.figure()

plt.errorbar(x_ppg101.T, y_piplus_ppg101, ey_piplus_ppg101, fmt="b.", markersize=10, label="piplus PPG101")
plt.errorbar(x_ppg101.T, y_piminus_ppg101, ey_piminus_ppg101, fmt="bs", markersize=5, label="piminus PPG101")
plt.errorbar(x_ppg202.T, y_pizero_ppg202, ey_pizero_ppg202, fmt="gs", markersize=5, label="pizero PPG202")




for i in range(1000):

    print(i)

    X = []

    Y = []

    dy = []

    
    scale = 1 

    rndm = 0 #np.random.normal(0, 0.001)
    x2a = x_ppg101 #np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.uniform(0,1) #1 - np.random.uniform(-1,1)
    if np.random.uniform(0,1) > 0.5 :
        coin = 1
    else :
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_piplus_ppg101)) + np.square(rndm*sys_piplus_ppg101))
    y2a = np.log10(np.multiply(np.add(y_piplus_ppg101,coin*noise), scale))


    rndm = 0 #np.random.normal(0, 0.001)
    x2b = x_ppg101 #np.log10(np.add(x_ppg101,rndm))

    rndm = np.random.uniform(0,1) #1 - np.random.uniform(-1,1)
    if np.random.uniform(0,1) > 0.5 :
        coin = 1
    else :
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_piminus_ppg101)) + np.square(rndm*sys_piminus_ppg101))
    y2b = np.log10(np.multiply(np.add(y_piminus_ppg101,coin*noise), scale))


    scale = 1 

    rndm = 0 #np.random.normal(0, 0.001)
    x3a = x_ppg202 #np.log10(np.add(x_ppg202,rndm))

    rndm = np.random.uniform(0,1) #1 - np.random.uniform(-1,1)
    if np.random.uniform(0,1) > 0.5 :
        coin = 1
    else :
        coin = -1
    noise = np.sqrt(np.square(np.random.normal(0, ey_pizero_ppg202)) + np.square(rndm*sys_pizero_ppg202))
    y3a = np.log10(np.multiply(np.add(y_pizero_ppg202,coin*noise), scale))

    X = np.append(X, x3a)
    X = np.append(X, x2a)
    X = np.append(X, x2b)

    X = np.atleast_2d(X).T

    Y = np.append(Y, y3a)
    Y = np.append(Y, y2a)
    Y = np.append(Y, y2b)


# Instantiate an MLP model
    gp =  MLPRegressor(max_iter=1000000, solver='lbfgs', activation='relu').fit(X, Y)

    #x = np.atleast_2d(np.linspace(-0.5, 1.5, 5000)).T
    x = np.atleast_2d(np.linspace(0.3, 30.3, 3000)).T
    y_pred = gp.predict(x)
    val.append(y_pred)

    #y_pred = gp.predict(np.log10(np.atleast_2d(x_ppg101)).T)
    y_pred = gp.predict(np.atleast_2d(x_ppg101).T)
    val_ppg101.append(y_pred)

    #y_pred = gp.predict(np.log10(np.atleast_2d(x_ppg202)).T)
    y_pred = gp.predict(np.atleast_2d(x_ppg202).T)
    val_ppg202.append(y_pred) 

average = np.average(val, axis=0)
sig = np.std(val, axis=0)

avg_ppg101 = np.average(val_ppg101, axis=0)
avg_ppg202 = np.average(val_ppg202, axis=0)

sig_ppg101 = np.average(val_ppg101, axis=0)
sig_ppg202 = np.average(val_ppg202, axis=0)


rat_piplus_ppg101 = np.divide(y_piplus_ppg101, 10**avg_ppg101)
rat_piminus_ppg101 = np.divide(y_piminus_ppg101, 10**avg_ppg101)

rat_pizero_ppg202 = np.divide(y_pizero_ppg202, 10**avg_ppg202)

erat_piplus_ppg101 = np.divide(ey_piplus_ppg101, 10**avg_ppg101)
erat_piminus_ppg101 = np.divide(ey_piminus_ppg101, 10**avg_ppg101)

erat_pizero_ppg202 = np.divide(ey_pizero_ppg202, 10**avg_ppg202)

x_coor = x
y_coor = np.atleast_2d(10**average).T
e_coor = np.atleast_2d(np.multiply(10**average,sig)).T

with open('mlp_pion_pp200_sys.txt','w') as f:
    lis=[x_coor, y_coor, e_coor]
    for entry in zip(*lis):
        f.write("{0}\t{1}\t{2}\n".format(*entry))

plt.plot(x, 10**average)
plt.fill(
    np.concatenate([x_coor, x_coor[::-1]]),
    np.concatenate([y_coor - 1.00 * e_coor, (y_coor + 1.00 * e_coor)[::-1]]),
    alpha=0.5,
    fc="r",
    ec="None",
    label="1 sigma",
)

plt.xlabel("$p_{T}$ [GeV]")
plt.ylabel("Invariant cross-section")
plt.yscale('log')
plt.ylim(1e-12, 100.0)
plt.legend(loc="upper right")


plt.figure()

plt.errorbar(x_ppg101.T, rat_piplus_ppg101, erat_piplus_ppg101, fmt="b.", markersize=10, label="piplus PPG101")
plt.errorbar(x_ppg101.T, rat_piminus_ppg101,erat_piminus_ppg101, fmt="bs", markersize=5, label="piminus PPG101")
plt.errorbar(x_ppg202.T, rat_pizero_ppg202, erat_pizero_ppg202, fmt="gs", markersize=5, label="pizero PPG202")

plt.xlabel("$p_{T}$ [GeV]")
plt.ylabel("$ratio$")
plt.ylim(0.5, 1.5)
#plt.legend(loc="upper right")

plt.show()
