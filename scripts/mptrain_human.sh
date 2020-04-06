python3 ./tools/train_net.py \
  --cfg ./configs/default/config_human.py \
  --savemodel ./outputs/dsgn_human \
  --loadmodel ./outputs/dsgn_disp/finetune_59.tar \
  --start_epoch 1 \
  --lr_scale 25 \
  --epochs 29 \
  -btrain 4 \
  -d 0-3 \
  --multiprocessing-distributed 
