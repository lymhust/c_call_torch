require 'torch'
torch.setdefaulttensortype('torch.FloatTensor')

function hi_tensor(t)
   print('Hi from lua')
   
   t[{ {1,50},{1,50},1 }] = 0
   t[{ {1,50},{1,50},3 }] = 0

   print(#t)
return t
end
