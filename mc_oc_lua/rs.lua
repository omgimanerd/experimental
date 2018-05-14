--[[
Materials managing script for OpenComputers
--]]

local component = require('component')
local sides = require('sides')

local rs = component.block_refinedstorage_interface
local threshold = 500

local function isempty(s)
  return s == nil or s == ""
end

for i, item in ipairs(rs.getItems()) do
  if item.size < threshold then
    if !isempty(string.find(item.name, "biomesoplenty")) then
      print("Marked " .. item.label .. " for restocking")
    end
  end
end
