--[==[
/*
 * This file is part of the "SystemC AMS Lua" distribution (https://github.com/yrasik/SystemC_AMS_Lua).
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

function initialize ()

end


function set_attributes ()

end


function processing(in_00, in_01)
  out_00 = in_00
  if( out_00 > 1 ) then
    out_00 = 1;
  end

  out_01 = in_01
  if( out_01 < -1 ) then
    out_01 = -1;
  end
  return out_00, out_01
end


function destructor()

end


