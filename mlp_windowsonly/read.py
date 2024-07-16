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


x_ppg101, y_piplus_ppg101, ey_piplus_ppg101, sys_piplus_ppg101 = read_data_from_excel("2006-pi+-0-100-pp-phenix.xlsx")
x_ppg103, y_piminus_ppg101, ey_piminus_ppg101, sys_piminus_ppg101 = read_data_from_excel("2006-pi--0-100-pp-phenix.xlsx")
x_ppg202, y_pizero_ppg202, ey_pizero_ppg202, sys_pizero_ppg202 = read_data_from_excel("2007-pi0-0-100-pp-phenix.xlsx")