--[[
  Lua script for restocking gardening/plant materials [Minecraft OpenComputers]
  Author: omgimanerd (alvin@omgimanerd.tech)
--]]

local component = require('component')
local sides = require('sides')

local rs = component..
local threshold = 2000

local function str_contains(s, substring)
  return string.find(s, substring) ~= nil
end

for n, item in ipairs(rs.getItems()) do
  if str_contains(item.name, 'biomesoplenty') then
    print('Restocking ' .. item.name)
  end
end
