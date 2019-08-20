from ampgen import FixedLib
model = FixedLib('./MyFile.so')
#print(model.matrix_elements[0]) # Print first matrix element

import pandas as pd
data = pd.read_csv('events.csv', nrows=100000)
fcn1 = model.FCN_all(data)

# or, a bit slower, but just to show flexibility:
fcn2 = data.apply(model.FCN, axis=1)
