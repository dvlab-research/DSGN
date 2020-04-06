MODEL="./outputs/MODEL_PATH"

for i in $(seq 5 5 43)
do
    python3 test_net.py --loadmodel $MODEL/finetune_${i}.tar -d 0-3 -btest 8 --debug --debugnum 1000
done
