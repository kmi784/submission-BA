
import numpy as np

dir = "../data/data_kalz/"

T = np.loadtxt(dir + "L80g3.txt", usecols=0, delimiter=",")
C = np.loadtxt(dir + "L80g3.txt", usecols=1, delimiter=",")

np.savetxt(dir + "kalz_L80g3.txt", np.transpose([T,C]), fmt="%.8f")

