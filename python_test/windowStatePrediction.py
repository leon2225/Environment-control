from __future__ import with_statement
import json
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

def moving_average(x, alpha):
    ret = np.array(x)
    for i, value in enumerate(x[1:]):
        ret[i] = ret[i-1] * alpha + value * (1-alpha)
    return ret

file = open("python_test/envlog.json")
envValues = json.load(file)
humidity = np.array([tempDict['value'] for tempDict in envValues["humidity"]["Arbeitszimmer"]])
times = np.array([datetime.fromtimestamp(tempDict['time']/1000) for tempDict in envValues["humidity"]["Arbeitszimmer"]])
xpoints = times
ypoints = humidity

avg = moving_average(ypoints, 0.97)

windowState = (humidity - avg) < -3

fig,ax = plt.subplots()

ax.plot(xpoints, ypoints)
ax.plot(xpoints, avg)

ax2 = ax.twinx()
ax2.plot(xpoints, windowState)
fig.show()
print("End")

