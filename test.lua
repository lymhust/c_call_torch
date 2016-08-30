print("lua script func.lua have been load ")
model = model:cuda()
local input = torch.CudaTensor(1, 3, 480, 640)
local output = model:forward(input)
print(#output)

function showinfo()
    print("welcome to  lua world ")
end
