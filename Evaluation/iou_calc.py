# Usage example: python iou_eval.py test-0.txt ground-truth-0.txt
import sys
import numpy as np

# two assisting functions
def area(width, height):
	return width*height

# (xa1, ya1) is top left corner of box a
# (xa2, ya2) is bottom right corner of box a
# same for box b
def intersection_area(xa1, ya1, xa2, ya2, xb1, yb1, xb2, yb2):
	dx = min(xa2, xb2) - max(xa1, xb1)
	dy = min(ya2, yb2) - max(ya1, yb1)
	if (dx>=0) and (dy>=0):
		return dx*dy
	else:
		return 0

IOU_list = []
for i in range(170):
  gt_file = "ground_truth/test-"+"%03d" % (i,)+"=.txt"
  pred_file = "results/test-"+str(i)+".txt"
  # read input files and preallocate arrays
  prediction = np.loadtxt(pred_file,dtype=int,ndmin=2)
  #prediction = np.reshape(prediction[0], (len(prediction[0])/2,2))
  npr = prediction.shape[0] # nof rows
  groundtruth = np.loadtxt(gt_file,dtype=int,ndmin=2)
  groundtruth = np.reshape(groundtruth[0], (len(groundtruth[0])/2,2))
  ngt = groundtruth.shape[0]
  union_area = np.zeros((ngt, npr))
  intersect_area = np.zeros((ngt, npr))
  for g in range(0, ngt):
    xa1 = groundtruth[g][0]
    ya1 = groundtruth[g][1]
    xa2 = xa1 + 100
    ya2 = ya1 + 40
    gt_area = area(40,100)
    for p in range(0, npr):
      xb1 = prediction[p][0]
      yb1 = prediction[p][1]
      xb2 = prediction[p][2]
      yb2 = prediction[p][3]
      pred_area = area(xb2-xb1,yb2-yb1)
      intersect_area[g,p] = intersection_area(xa1, ya1, xa2, ya2, xb1, yb1, xb2, yb2)
      union_area[g,p] = gt_area + pred_area - intersect_area[g,p]
  IOU = np.amax(intersect_area / union_area)
  IOU_list.append(IOU)
  print IOU
  
IOU_array = np.array(IOU_list)
print("mean: ", np.mean(IOU_array))
print("std dev: ", np.std(IOU_array))
  





