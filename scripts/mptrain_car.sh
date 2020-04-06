python3 ./tools/train_net.py \
  --cfg ./configs/default/config_car.py \
  --savemodel ./outputs/dsgn_car \
  --start_epoch 1 \
  --lr_scale 50 \
  --epochs 60 \
  -btrain 4 \
  -d 0-3 \
  --multiprocessing-distributed 