python3 ./tools/train_net.py \
  --cfg ./configs/default/config_disp.py \
  --savemodel ./outputs/dsgn_disp_trainval \
  --split_file ./data/kitti/trainval.txt \
  --start_epoch 1 \
  --lr_scale 35 \
  --epochs 45 \
  -btrain 4 \
  -d 0-3 \
  --multiprocessing-distributed 
