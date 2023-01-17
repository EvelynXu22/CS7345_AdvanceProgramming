import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import seaborn as sns

def probablityDensity(mean, std):
    x = np.arange(-5, 5, 0.001)
    y = stats.norm.pdf(x, loc=mean, scale=std)
    plt.plot(x, y)
    plt.show()


def getConfidenceInterval(array):
    dt = np.dtype(np.float64)
    array = np.array(array, dtype=dt)

    # get mean, std and confidence interval
    mean, std = array.mean(), array.std(ddof = 1)
    conf_intveral = stats.norm.interval(0.95, loc=mean, scale=std)

    # Under the assumption that the data distribution is normal, obtaining the p-value
    d, p = stats.kstest(array, 'norm', (mean, std))
    print('P value:', p)


    print(f'Mean:{mean} Standard:{std}')
    print("Confidence Interval:", conf_intveral)
    sns.distplot(array)
    plt.show()


browserTime, cppTime = [], []
browserO2Time = []

# read file
path = "Data/browser_time.txt"
with open(path,'r') as f:
    browserTime = f.read().splitlines()

path = "Data/cpp_time.txt"
with open(path,'r') as f:
    cppTime = f.read().splitlines()

path = "Data/browser_O2_time.txt"
with open(path,'r') as f:
    browserO2Time = f.read().splitlines()

getConfidenceInterval(cppTime)
getConfidenceInterval(browserTime)
getConfidenceInterval(browserO2Time)
