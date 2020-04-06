import os
import numpy as np
from yacs.config import CfgNode as CN

cfg = CN()

cfg.cnt = 0

cfg.btrain = 8

cfg.hg_cv = True

cfg.align_corners = True

cfg.valid_classes = [1,2,3]
#cfg.valid_classes = [2]

cfg.GN = True

cfg.num_classes = 3

cfg.input_size = [384, 1248]
cfg.output_size = [96, 312]

#------------- disparity ---------------#
cfg.maxdisp = 192
cfg.downsample_disp = 4

#------------- depth ---------------#
cfg.eval_depth = True # test
cfg.depth_interval = 0.2 # (meters)
cfg.depth_min_intervals = 10

cfg.max_depth = (cfg.maxdisp + cfg.depth_min_intervals) * cfg.depth_interval
cfg.min_depth = cfg.depth_min_intervals * cfg.depth_interval

cfg.loss_disp = True
cfg.flip = True
#------------- detection ---------------#
cfg.RPN_CONVDIM = 32
cfg.RPN_ONEMORE_CONV = True
cfg.RPN3D_ENABLE = False
cfg.RPN3D = CN()
cfg.RPN3D.ANCHORS_Y = [0.74, 0.825, 0.74]
cfg.RPN3D.ANCHORS_HEIGHT = [1.73, 1.56, 1.73]
cfg.RPN3D.ANCHORS_WIDTH = [0.6, 1.6, 0.6]
cfg.RPN3D.ANCHORS_LENGTH = [0.8, 3.9, 1.76]

cfg.RPN3D.PRIOR_PROB = 0.01 # RetinaNet
cfg.RPN3D.FOCAL_GAMMA = 2.0
cfg.RPN3D.FOCAL_ALPHA = 0.25
cfg.RPN3D.PRE_NMS_THRESH = 0.05
cfg.RPN3D.PRE_NMS_TOP_N = 300
cfg.RPN3D.NMS_THRESH = 0.6 # [0.6, 0.6, 0.45]
cfg.RPN3D.POST_NMS_TOP_N = 30
cfg.RPN3D.NUM_CONVS = 4

#-------------- debug ----------------#
cfg.debug = False

#-------------- Parameters -----------#
cfg.Z_MIN = 40.4
cfg.Z_MAX = 2.
cfg.VOXEL_Z_SIZE = -0.2
cfg.X_MIN = -30.
cfg.X_MAX = 30.
cfg.VOXEL_X_SIZE = 0.2
cfg.Y_MIN = 3.
cfg.Y_MAX = -1.
cfg.VOXEL_Y_SIZE = -0.2
cfg.INPUT_WIDTH = int((cfg.X_MAX - cfg.X_MIN + np.sign(cfg.VOXEL_X_SIZE) * 1e-10) / cfg.VOXEL_X_SIZE)
cfg.INPUT_HEIGHT = int((cfg.Y_MAX - cfg.Y_MIN + np.sign(cfg.VOXEL_Y_SIZE) * 1e-10) / cfg.VOXEL_Y_SIZE)
cfg.INPUT_DEPTH = int((cfg.Z_MAX - cfg.Z_MIN + np.sign(cfg.VOXEL_Z_SIZE) * 1e-10) / cfg.VOXEL_Z_SIZE)
cfg.VOXEL_SIZE = [cfg.VOXEL_Z_SIZE, cfg.VOXEL_Y_SIZE, cfg.VOXEL_X_SIZE]
cfg.GRID_SIZE = [cfg.INPUT_DEPTH, cfg.INPUT_HEIGHT, cfg.INPUT_WIDTH]

cfg.CV_Z_MIN = 40.4
cfg.CV_Z_MAX = 2.0
cfg.CV_VOXEL_Z_SIZE = -0.2

cfg.CV_X_MIN = 0.
cfg.CV_X_MAX = cfg.input_size[1] - 1
cfg.CV_VOXEL_X_SIZE = 1.
cfg.CV_Y_MIN = 0
cfg.CV_Y_MAX = cfg.input_size[0] - 1
cfg.CV_VOXEL_Y_SIZE = 1.
cfg.CV_INPUT_WIDTH = int((cfg.CV_X_MAX - cfg.CV_X_MIN + np.sign(cfg.CV_VOXEL_X_SIZE) * (1. + 1e-10)) / cfg.CV_VOXEL_X_SIZE)
cfg.CV_INPUT_HEIGHT = int((cfg.CV_Y_MAX - cfg.CV_Y_MIN + np.sign(cfg.CV_VOXEL_Y_SIZE) * (1. + 1e-10)) / cfg.CV_VOXEL_Y_SIZE)
cfg.CV_INPUT_DEPTH = int((cfg.CV_Z_MAX - cfg.CV_Z_MIN + np.sign(cfg.CV_VOXEL_Z_SIZE) * 1e-10) / cfg.CV_VOXEL_Z_SIZE)
cfg.CV_VOXEL_SIZE = [cfg.CV_VOXEL_Z_SIZE, cfg.CV_VOXEL_Y_SIZE, cfg.CV_VOXEL_X_SIZE]
cfg.CV_GRID_SIZE = [cfg.CV_INPUT_DEPTH, cfg.CV_INPUT_HEIGHT, cfg.CV_INPUT_WIDTH]

print('depth: {} -> {}'.format(cfg.min_depth, cfg.max_depth))
print('z range: {} -> {}'.format(cfg.CV_Z_MIN, cfg.CV_Z_MAX))
print('GRID SIZE', cfg.GRID_SIZE)
print('CV GRID SIZE', cfg.CV_GRID_SIZE)

cfg.ANCHOR_ANGLES = [0., np.pi / 2., np.pi, np.pi / 2. * 3.]
cfg.num_angles = len(cfg.ANCHOR_ANGLES)
# cat disparity
cfg.cat_disp = False

# cat img feature
cfg.cat_img_feature = True
cfg.cat_right_img_feature = False

# attention
cfg.img_feature_attentionbydisp = True
cfg.voxel_attentionbydisp = False

cfg.learn_viewpoint = False
cfg.class4angles = True
cfg.centerness4class = False

#----------------- centerness --------------#
cfg.norm_expdist = True
cfg.norm_factor = 1.
cfg.norm_max = False

cfg.box_pixel_multiple = 3

cfg.box_corner_parameters = False
#----------------------------------------------------#

cfg.less_car_pos = True
cfg.less_human_pos = False

cfg.hg_rpn_conv = True

# network
cfg.backbone = 'reslike-det-small'

