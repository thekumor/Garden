-- ================================================
-- 
--	Project: Garden
-- 
--	File: data/vegetables.lua
--	Desc: Defines vegetable properties
-- 
--	Modified: 2025/01/08 8:30 PM
--	Created: 2025/01/08 8:25 PM
--	Authors: The Kumor
-- 
-- ================================================

local veg = {}

veg.carrot = {
	likes = {"water", "sunlight"},
	dislikes = {"shade", "frost"}
}

-- Assign to the global variable used from C++ side.
vegetables = veg