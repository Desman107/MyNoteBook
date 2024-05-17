```python
import torch
import torch.nn as nn
import torch.optim as optim

class TitanicSurvivalNN(nn.Module):
    def __init__(self):
        super(TitanicSurvivalNN, self).__init__()
        self.layer1 = nn.Linear(6, 128)  # First hidden layer
        self.layer2 = nn.Linear(128, 64) # Second hidden layer
        self.output_layer = nn.Linear(64, 1) # Output layer
        
        self.relu = nn.ReLU()  # ReLU activation function
        self.sigmoid = nn.Sigmoid()  # Sigmoid activation function

    def forward(self, x):
        x = self.relu(self.layer1(x))
        x = self.relu(self.layer2(x))
        x = self.sigmoid(self.output_layer(x))
        return x
```