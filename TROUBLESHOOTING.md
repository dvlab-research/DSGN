## Troubleshooting

#### Why the released models get a worse performance with PyTorch 1.4.0?

Prior to release the code, I spent plenty of time in making the pre-trained model compatible with the results. At last I found that I am using the newest PyTorch 1.4.0 + Torchvision 0.5.0, while the pre-trained models are trained in the environment of PyTorch 1.1.0 and Torchvision 0.2.0. This difference causes the minor difference of results, which gets much worse results during evaluation on KITTI. Currently I do not have machine to train the original model. You are welcome to contribute it in the model zoo. 
