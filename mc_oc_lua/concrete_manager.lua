--[[
  Lua script for restocking concrete [Minecraft OpenComputers]
  Author: omgimanerd (alvin@omgimanerd.tech)
--]]

local component = require('component')

local rs = component..
local threshold = 5000

local function str_contains(s, substring)
  return string.find(s, substring) ~= nil
end

for n, pattern in ipairs(rs.getPatterns()) do
  local output = pattern.outputs[1]
  if str_contains(output.name, 'concrete') then
    --[[
      Calculate how much concrete is needed to meet our threshold.
    --]]
    local craft_amount = 0
    local output_stock = rs.getItem(output)
    if output_stock == nil then
      craft_amount = threshold
    elseif output_stock.size < threshold then
      craft_amount = threshold - output_stock.size
    end

    --[[
      Request the crafting job if the number to craft is nonzero.
    --]]
    if craft_amount > 0 then
      rs.scheduleTask(output, craft_amount)
      print(output.label .. ': Crafting ' .. craft_amount)
    else
      print('Supply of ' .. output_stock.size .. ' ' .. output .. ' is nominal')
    end
  end
end
