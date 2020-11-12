import numpy as np
total_length = 13
m = 2
pos = [0,1,2.6,4,4.2,4.4,5,6,7,8.1,9.2,9.5,10,11,12]
pos.append(total_length)

water_per_mile = 2/2

hydrate = []
remain = 2

for i,position in enumerate(pos[0:-1]):
    if (pos[i+1]-pos[i])*water_per_mile > remain:
        hydrate.append(position)
        remain = 2-(pos[i+1]-pos[i])*water_per_mile
    else:
        remain -= (pos[i+1]-pos[i])*water_per_mile

hydrate.append(total_length)
print("\nfewest hydration time is {}, hydrating position sequence is :{}".format(len(hydrate),hydrate))