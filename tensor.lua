require 'torch'
torch.setdefaulttensortype('torch.FloatTensor')

function hi_tensor(t)
   print('Hi from lua')
   local img = t:permute(3, 1, 2)
   img[3],img[1] = img[1],img[3]
   print(#img)
return img
end
