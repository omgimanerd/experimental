--[[
Materials managing script for OpenComputers
--]]

local component = require('component')
local sides = require('sides')

local rs = component.block_refinedstorage_interface

for i, item in ipairs(rs.getItems()) do
  for j, k in ipairs(item) do
    print(j, k)
  end
end
