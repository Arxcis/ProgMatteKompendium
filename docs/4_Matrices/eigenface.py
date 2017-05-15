# -*- coding: utf-8 -*-
"""
A script that computes the eigen faces.

Xingbo Wang <xingbo.wang@ntnu.no>
Apr 9, 2017
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import misc

number_of_faces = 40
m,n = np.shape(misc.imread('./faces/1.bmp'))
faces = -np.ones((m*n,number_of_faces))

for i in range(number_of_faces):
    faces[:,i] = np.squeeze(np.reshape(misc.imread('./faces/%s.bmp' % str(i+1)),(-1,1)))

EX = np.mean(faces, axis=1)
B = faces - np.matmul(np.array([EX]).T, np.ones((1,number_of_faces)))

fast_comp = True
if fast_comp:
    C = np.matmul(B.T, B)/(m*n-1)
    D, Q = np.linalg.eig(C)
    IX = np.argsort(D)[::-1]
    D = D[IX]
    Q = np.matmul(B, Q[:,IX])
    Q = np.divide(Q, np.matmul(np.ones((m*n,1)),np.array([np.linalg.norm(Q,axis=0)])))
else:
    C = np.matmul(B, B.T)/(m*n-1)
    D, Q = np.linalg.eig(C)
    IX = np.argsort(D)[::-1]
    D = D[IX]
    Q = Q[:,IX]

r = 0.9
for L in range(number_of_faces):
     if sum(D[:L+1])/sum(D) >= r:
         break
k = L + 1

P = np.matmul(B.T, Q[:,:k])
faces2 = np.matmul(P, Q[:,:k].T).T + np.matmul(np.array([EX]).T, np.ones((1, number_of_faces)))

plt.figure(1)
plt.imshow(np.reshape(EX,(m,n)),cmap='gray',vmin=0,vmax=255)
plt.axis('off')

plt.figure(2)
for i in range(number_of_faces):
    plt.subplot(5,8,i+1)
    plt.imshow(np.reshape(Q[:,i],(m,n)),cmap='gray',vmin=np.min(Q),vmax=np.max(Q))
    plt.axis('off')

plt.figure(3)
for i in range(number_of_faces):
    plt.subplot(5,8,i+1)
    plt.imshow(np.reshape(faces[:,i],(m,n)),cmap='gray',vmin=0,vmax=255)
    plt.axis('off')

plt.figure(4)
for i in range(number_of_faces):
    plt.subplot(5,8,i+1)
    plt.imshow(np.reshape(faces2[:,i],(m,n)),cmap='gray',vmin=0,vmax=255)
    plt.axis('off')