--[==[
/*
 * This file is part of the XXX distribution (https://github.com/yrasik/SystemC_AMS_Lua).
 * Copyright (c) 2020 Yuri Stepanenko.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
]==]

local file
local self_name = 'Source_Lua_00.lua'
local name = "example_00_"

function initialize ()
  file = io.open(name..".dat", "r")
  if( file == nil ) then
    print('ERROR: '..self_name..': initialize:  file == nil')
    return
  end

end


function set_attributes ()

end


function processing()
  local line = file:read( "*line" )
  if( line == nil ) then
    print("WARNING: End of file.")
    return 0, 0
  end
  local t, val_00, val_01 = line:match("^%s*([%d%.%+%-e]+)%s+([%d%.%+%-e]+)%s+([%d%.%+%-e]+)")
  val_00 = tonumber(val_00)
  val_01 = tonumber(val_01)
  return val_00, val_01
end


function destructor()
  file:close()
end
