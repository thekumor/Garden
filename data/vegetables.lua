-- ================================================
-- 
--	Project: Garden
-- 
--	File: data/vegetables.lua
--	Desc: Defines vegetable properties
-- 
--	Modified: 2026/02/24 12:48 PM
--	Created: 2026/01/08 8:25 PM
--	Authors: The Kumor
-- 
-- ================================================

rect_size = { 260, 260 }

-- PL: Marchewka
veg_carrot = {
	lang_pl = "Marchewka",
	lang_en = "Carrot",
	img = "img/vegetables/carrot.png",
	likes = { "onion", "leek", "peas", "lettuce", "radish" },
	hates = { "celery", "dill" },
	pos = { 0, 0 }
}

-- PL: Bób
veg_broad_bean = {
	lang_pl = "Bob",
	lang_en = "Broad Bean",
	img = "img/vegetables/broad_bean.png",
	likes = { "lettuce", "corn" },
	hates = { "onion", "garlic" },
	pos = { 1, 0 }
}

-- PL: Ziemniak
veg_potato = {
	lang_pl = "Ziemniak",
	lang_en = "Potato",
	img = "img/vegetables/potato.png",
	likes = { "bean", "corn", "cabbage", "horseradish" },
	hates = { "tomato", "cucumber", "pumpkin" },
	pos = { 2, 0 }
}

-- PL: Seler
veg_celery = {
	lang_pl = "Seler",
	lang_en = "Celery",
	img = "img/vegetables/celery.png",
	likes = { "cabbage", "leek", "onion" },
	hates = { "carrot", "parsley" },
	pos = { 3, 0 }
}

-- PL: Rzodkiewka
veg_radish = {
	lang_pl = "Rzodkiewka",
	lang_en = "Radish",
	img = "img/vegetables/radish.png",
	likes = { "carrot", "lettuce", "peas", "cucumber" },
	hates = { "hyssop" },
	pos = { 4, 0 }
}

-- PL: Fasola
veg_bean = {
	lang_pl = "Fasola",
	lang_en = "Bean",
	img = "img/vegetables/bean.png",
	likes = { "corn", "potato", "cabbage", "cucumber" },
	hates = { "onion", "garlic", "leek" },
	pos = { 0, 1 }
}

-- PL: Por
veg_leek = {
	lang_pl = "Por",
	lang_en = "Leek",
	img = "img/vegetables/leek.png",
	likes = { "carrot", "celery", "onion" },
	hates = { "bean", "peas" },
	pos = { 1, 1 }
}

-- PL: Burak
veg_beetroot = {
	lang_pl = "Burak",
	lang_en = "Beetroot",
	img = "img/vegetables/beetroot.png",
	likes = { "onion", "lettuce", "cabbage" },
	hates = { "peas" },
	pos = { 2, 1 }
}

-- PL: Sałata
veg_lettuce = {
	lang_pl = "Salata",
	lang_en = "Lettuce",
	img = "img/vegetables/lettuce.png",
	likes = { "carrot", "beetroot", "radish", "cucumber" },
	hates = {},
	pos = { 3, 1 }
}

-- PL: Czosnek
veg_garlic = {
	lang_pl = "Czosnek",
	lang_en = "Garlic",
	img = "img/vegetables/garlic.png",
	likes = { "carrot", "beetroot", "lettuce", "cabbage" },
	hates = { "bean", "peas" },
	pos = { 4, 1 }
}

-- PL: Cebula
veg_onion = {
	lang_pl = "Cebula",
	lang_en = "Onion",
	img = "img/vegetables/onion.png",
	likes = { "carrot", "beetroot", "lettuce" },
	hates = { "bean", "peas" },
	pos = { 0, 2 }
}

-- PL: Ogórek
veg_cucumber = {
	lang_pl = "Ogorek",
	lang_en = "Cucumber",
	img = "img/vegetables/cucumber.png",
	likes = { "bean", "peas", "lettuce", "radish", "dill" },
	hates = { "potato" },
	pos = { 1, 2 }
}

-- PL: Papryka
veg_pepper = {
	lang_pl = "Papryka",
	lang_en = "Pepper",
	img = "img/vegetables/pepper.png",
	likes = { "onion", "lettuce", "carrot" },
	hates = { "bean" },
	pos = { 2, 2 }
}

-- PL: Kapusta
veg_cabbage = {
	lang_pl = "Kapusta",
	lang_en = "Cabbage",
	img = "img/vegetables/cabbage.png",
	likes = { "celery", "onion", "potato", "bean" },
	hates = { "strawberry" },
	pos = { 3, 2 }
}

-- PL: Groszek
veg_peas = {
	lang_pl = "Groszek",
	lang_en = "Peas",
	img = "img/vegetables/peas.png",
	likes = { "carrot", "radish", "cucumber" },
	hates = { "onion", "garlic", "leek" },
	pos = { 4, 2 }
}

-- PL: Dynia
veg_pumpkin = {
	lang_pl = "Dynia",
	lang_en = "Pumpkin",
	img = "img/vegetables/pumpkin.png",
	likes = { "corn", "bean" },
	hates = { "potato" },
	pos = { 0, 3 }
}

-- PL: Cukinia
veg_zucchini = {
	lang_pl = "Cukinia",
	lang_en = "Zucchini",
	img = "img/vegetables/zucchini.png",
	likes = { "corn", "bean" },
	hates = { "potato" },
	pos = { 1, 3 }
}

-- PL: Bakłażan
veg_eggplant = {
	lang_pl = "Baklazan",
	lang_en = "Eggplant",
	img = "img/vegetables/eggplant.png",
	likes = { "bean", "lettuce" },
	hates = { "potato" },
	pos = { 2, 3 }
}

-- PL: Kalafior
veg_cauliflower = {
	lang_pl = "Kalafior",
	lang_en = "Cauliflower",
	img = "img/vegetables/cauliflower.png",
	likes = { "celery", "onion" },
	hates = {},
	pos = { 3, 3 }
}

-- PL: Brokuł
veg_broccoli = {
	lang_pl = "Brokul",
	lang_en = "Broccoli",
	img = "img/vegetables/broccoli.png",
	likes = { "celery", "onion" },
	hates = {},
	pos = { 4, 3 }
}

-- PL: Pietruszka
veg_parsley = {
	lang_pl = "Pietruszka",
	lang_en = "Parsley",
	img = "img/vegetables/parsley.png",
	likes = { "onion", "carrot" },
	hates = { "celery" },
	pos = { 0, 4 }
}

-- PL: Koper
veg_dill = {
	lang_pl = "Koper",
	lang_en = "Dill",
	img = "img/vegetables/dill.png",
	likes = { "cucumber", "lettuce" },
	hates = { "carrot" },
	pos = { 1, 4 }
}

-- PL: Chrzan
veg_horseradish = {
	lang_pl = "Chrzan",
	lang_en = "Horseradish",
	img = "img/vegetables/horseradish.png",
	likes = { "potato" },
	hates = {},
	pos = { 2, 4 }
}

-- PL: Kukurydza
veg_corn = {
	lang_pl = "Kukurydza",
	lang_en = "Corn",
	img = "img/vegetables/corn.png",
	likes = { "bean", "pumpkin", "zucchini" },
	hates = {},
	pos = { 3, 4 }
}

-- PL: Pomidor
veg_tomato = {
	lang_pl = "Pomidor",
	lang_en = "Tomato",
	img = "img/vegetables/tomato.png",
	--likes = { "kohlrabi" },
	--hates = { "potato" },
	likes = {},
	hates = {},
	pos = { 4, 4 }
}

-- PL: Kalarepa
veg_kohlrabi = {
	lang_pl = "Kalarepa",
	lang_en = "Kohlrabi",
	img = "img/vegetables/kohlrabi.png",
	likes = { "tomato", "bean", "celery", "beetroot", "radish", "leek", "lettuce" },
	hates = {},
	pos = { 0, 5 }
}