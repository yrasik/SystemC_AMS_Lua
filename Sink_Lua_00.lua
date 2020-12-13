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
local name = "example_00"

function initialize ()
  file = io.open(name..".dat", "w")
  file:write(string.format("#TIME\tsig_from_gain\tsig_filters1_out\n"))
end


function set_attributes ()

end


function processing( time, in_00, in_01 )
    file:write(string.format("%e\t%e\t%e\n",time, in_00, in_01))
end


function destructor( )
  file:close()
  
  file_dem = io.open(name..".dem", "w")
  file_dem:write("plot '"..name..".dat' with lines\n")
  file_dem:write("pause -1 \"Hit return to continue\"\n")
  file_dem:close()
    
  os.execute('gnuplot "'..name..'.dem" ')
end

