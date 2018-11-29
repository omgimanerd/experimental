--[[
  Lua script for restocking dye [Minecraft OpenComputers]
  Author: omgimanerd (alvin@omgimanerd.tech)
--]]

local component = require('component')

local rs = component.proxy(component.get('e4299aeb'))
local threshold = 1000

local function str_contains(s, substring)
  return string.find(s, substring) ~= nil
end

for n, pattern in ipairs(rs.getPatterns()) do
  local output = pattern.outputs[1]
  if str_contains(output.name, 'dye') then
    --[[
      Calculate how much dye is needed to meet our supply threshold.
    --]]
    local craft_amount = 0
    local output_stock = rs.getItem(output)
    if output_stock == nil then
      craft_amount = threshold
    elseif output_stock.size < threshold then
      craft_amount = threshold - output_stock.size
    end

    --[[
      Ensure we have enough of the corresponding plant, if not, craft enough
      to leave one plant remaining for regrowing.
    --]]
    local input = pattern.inputs[1]
    local input_required = (craft_amount / output.size) * input.size
    local input_stock = rs.getItem(input)
    if input_stock == nil then
      craft_amount = 0
      print('ERROR: We ran out of the ' .. input.label)
    elseif input_stock.size == 1 then
      craft_amount = 0
      print('WARNING: We only have 1 of ' .. input.label .. ' and cannot restock ' .. output.label)
    elseif input_required >= input_stock.size then
      craft_amount = ((input_stock.size - 1) / input.size) * output.size
      print('WARNING: We are running out of ' .. input_stock.label)
    end

    --[[
      Request the crafting job if the number to craft is nonzero.
    --]]
    if craft_amount > 0 then
      rs.scheduleTask(output, craft_amount)
      print('INFO: Crafting ' .. craft_amount .. ' of ' .. output.label)
    end
  end
end

print('Done!')
