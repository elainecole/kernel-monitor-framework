import numpy as np
differences = []
with open('variance.txt') as f:
    c = 0
    prev = 0
    for line in f:
        if c == 0:
            prev = float(line)
            c += 1
            continue
        differences.append(float(line) - prev)
        prev = float(line)

print 'Variance: ', np.var(differences)
        