import torch
import torch.nn as nn
import torch.onnx


# Simple linear classifier
class SimpleModel(nn.Module):
    def __init__(self, input_size=128, output_size=10):
        super().__init__()
        self.fc = nn.Linear(input_size, output_size)
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        x = self.fc(x)
        x = self.softmax(x)
        return x


# Model parameters
input_size = 128  # match your C++ input vector
output_size = 10  # arbitrary number of classes for testing

# Create model
model = SimpleModel(input_size, output_size)
model.eval()

# Dummy input to trace the model
dummy_input = torch.randn(1, input_size)

# Export to ONNX
onnx_path = "model.onnx"
torch.onnx.export(
    model,
    dummy_input,
    onnx_path,
    input_names=["input"],
    output_names=["prob"],
    dynamic_axes={
        "input": {0: "batch_size"},
        "prob": {0: "batch_size"},
    },
    opset_version=17,
)

print(f"Model exported to {onnx_path}")
