require 'torch'

function hi_tensor(t)
   print('Hi from lua')
   torch.setdefaulttensortype('torch.FloatTensor')
   t[100] = 0
   print(#t)
return t
end
