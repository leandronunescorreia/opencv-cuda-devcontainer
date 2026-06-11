import torch
import torch.nn as nn
import torch.optim as optim

num_samples = 1000
input_dim = 5
output_dim = 1

x_train = torch.randn(num_samples, input_dim)
y_train = torch.randint(0, 2, (num_samples, output_dim), dtype=torch.float32)

class LogisticRegression(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        self.linear = nn.Linear(input_dim, output_dim)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        return self.sigmoid(self.linear(x))

model = LogisticRegression(input_dim, output_dim)

criterion = nn.BCELoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

for epoch in range(1000):
    optimizer.zero_grad()
    outputs = model(x_train)
    loss = criterion(outputs, y_train)
    loss.backward()
    optimizer.step()

    if (epoch + 1) % 100 == 0:
        print(loss.item())

model.eval()

example_input = torch.randn(1, 5)

torch.onnx.export(
    model,
    example_input,
    "logreg.onnx",
    opset_version=17,
    input_names=["input"],
    output_names=["output"],
    dynamic_axes={"input": {0: "batch"}, "output": {0: "batch"}}
)

print("ONNX model exported!")