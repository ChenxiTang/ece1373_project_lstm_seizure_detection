import numpy as np

# transform npy file to txt file for cpp code

"""
#file_name = "x_test_se"
#x = np.load(file_name + ".npy")
#print(x.shape)
#file = open(file_name + ".txt", "w")
#n,d = x.shape
#for i in range(n):
#    for j in range(d):
#        file.write('%f\n' % x[i,j])
#file.close()
"""
file_end = ".npy"
file_end2 = ".txt"
"""
file_name = "bc"
bc = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    file.write('%f\n' % bc[i])
file.close()
print(bc.shape)

file_name = "bf"
bf = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    file.write('%f\n' % bf[i])
file.close()
print(bf.shape)

file_name = "bi"
bi = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    file.write('%f\n' % bi[i])
file.close()
print(bi.shape)

file_name = "bo"
bo = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    file.write('%f\n' % bo[i])
file.close()
print(bo.shape)

file_name = "by"
by = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(1):
    file.write('%f\n' % by[i])
file.close()
print(by.shape)

file_name = "Whc"
Whc = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(64):
        file.write('%f\n' % Whc[j,i])
file.close()
print(Whc.shape)

file_name = "Whf"
Whf = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(64):
        file.write('%f\n' % Whf[j,i])
file.close()
print(Whf.shape)

file_name = "Whi"
Whi = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(64):
        file.write('%f\n' % Whi[j,i])
file.close()
print(Whi.shape)

file_name = "Who"
Who = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(64):
        file.write('%f\n' % Who[j,i])
file.close()
print(Who.shape)

file_name = "Wxc"
Wxc = np.load(file_name + file_end)
print(Wxc.shape)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(110):
        file.write('%f\n' % Wxc[j,i])
file.close()


file_name = "Wxf"
Wxf = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(110):
        file.write('%f\n' % Wxf[j,i])
file.close()
print(Wxf.shape)

file_name = "Wxi"
Wxi = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(110):
        file.write('%f\n' % Wxi[j,i])
file.close()
print(Wxi.shape)

file_name = "Wxo"
Wxo = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    for j in range(110):
        file.write('%f\n' % Wxo[j,i])
file.close()
print(Wxo.shape)

file_name = "Wy"
Wy = np.load(file_name + file_end)
file = open(file_name + file_end2, "w")
for i in range(64):
    file.write('%f\n' % Wy[i])
file.close()
print(Wy.shape)
"""

file_name = "logits_series"
logits_series = np.load(file_name + file_end)
print(logits_series.shape)
logits_series = np.transpose(logits_series,(1,0,2))
print(logits_series.shape)
logits_series = np.reshape(logits_series, (61440, 1))
file = open(file_name + file_end2, "w")
for i in range(61440):
    file.write('%f\n' % logits_series[i])
file.close()
print(logits_series.shape)

file_name = "predictions_series"
predictions_series = np.load(file_name + file_end)
predictions_series = np.transpose(predictions_series,(1,0,2))
print(predictions_series.shape)
predictions_series = np.reshape(predictions_series, (61440, 1))
file = open(file_name + file_end2, "w")
for i in range(61440):
    file.write('%f\n' % predictions_series[i])
file.close()
print(predictions_series.shape)

file_name = "states_series"
states_series = np.load(file_name + file_end)
states_series = np.transpose(states_series,(1,0,2))
print(states_series.shape)
states_series = np.reshape(states_series, (61440, 64))
file = open(file_name + file_end2, "w")
for i in range(61440):
    for j in range(64):
        file.write('%f\n' % states_series[i,j])
file.close()
print(states_series.shape)
