import numpy as np
from datetime import datetime

a = np.random.normal(size=100000).tolist()

begin_1 = datetime.now()
b = [num+1 for num in a]
print(f"List comprehension: {(datetime.now()-begin_1).microseconds/1000}")

c = np.array(a)

begin_2 = datetime.now()
d = c + 1
print(f"Numpy: {(datetime.now()-begin_2).microseconds/1000}")

