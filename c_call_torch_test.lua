require 'torch'
torch.setdefaulttensortype('torch.FloatTensor')

function hi_tensor(t)
   print('Lua function')
   local img = t:permute(3, 1, 2)
   img[1] = 0
   img[3] = 1 
return img
end
