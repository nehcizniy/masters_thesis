import numpy as np
from matplotlib import pyplot as plt

from sklearn.neural_network import MLPRegressor

np.random.seed(0)

# ===== define data sets with their errors ======

npt = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24])

x = np.array([0.85, 1.25, 1.75, 2.25, 2.75, 3.25, 3.75, 4.25, 4.75, 5.25, 5.75, 6.25, 6.75, 7.25, 7.75, 8.25, 8.75, 9.25, 9.75, 10.95, 12.95, 14.95, 16.95, 18.95, 20.95])

ratio = np.array([0.995615, 1.00864, 0.999353, 0.988733, 0.998756, 0.999006, 1.02627, 0.99224, 0.9899, 0.997687, 0.99548, 1.00383, 1.00052, 1.00737, 0.993666, 0.999766, 0.998177, 0.991247, 1.0193, 1.01813, 0.963662, 0.980865, 1.0421, 0.999599, 0.355798])
err_ratio = np.array([0.00433193, 0.00217494, 0.00220205, 0.00296521, 0.00442811, 0.00683782, 0.0103068, 0.00164679, 0.00210266, 0.00273192, 0.0036039, 0.00467823, 0.00604587, 0.00760938, 0.00954986, 0.0116903, 0.0143002, 0.0172963, 0.0204992, 0.0151715, 0.0306412, 0.0586835, 0.111092, 0.247135, 1.41421])


plt.figure()
plt.errorbar(x.T, ratio, yerr=err_ratio, fmt="r.", markersize=10, label="raw/out")
plt.legend(loc="upper right")
plt.xlabel("$p_{T}$ [GeV]")

val = []

for i in range(100):

    print(i)

    X = []
    Y = []

    y1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    for b in npt:
        while y1[b] <= 0:
            y1[b] = np.random.normal(ratio[b], err_ratio[b])
            
    
    X = np.append(X, x)
    X = np.atleast_2d(X).T

    Y = np.append(Y, y1)

    regr = MLPRegressor(max_iter=10000, solver='lbfgs', activation='tanh').fit(X, Y) #'relu' logistic softmax
    
    xpred = np.atleast_2d(np.linspace(0.3, 35.0, 3470)).T

    ypred = regr.predict(xpred)
    
    val.append(ypred)
    


average = np.average(val, axis=0)
sig = np.std(val, axis=0)

x_coor = xpred
y_coor = np.atleast_2d(average).T
e_coor = np.atleast_2d(sig).T

with open('pion_iteration2.txt','w') as f:
    lis=[x_coor, y_coor, e_coor]
    for entry in zip(*lis):
        f.write("{0}\t{1}\t{2}\n".format(*entry))

plt.plot(xpred, average)

plt.fill(
    np.concatenate([x_coor, x_coor[::-1]]),
    np.concatenate([y_coor - 1.00 * e_coor, (y_coor + 1.00 * e_coor)[::-1]]),
    alpha=0.5,
    fc="r",
    ec="None",
    label="1 sigma",
)

plt.show()
