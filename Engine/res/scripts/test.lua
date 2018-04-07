player = {
	name = "rocketman",

	model = "pig.obj",
	
	position = {
		x = 5.5,
		y = 9.0,
		z = 0.0,
	},

	collidable = {
		type = "aabb",
		position = {
			x = 0.0,
			y = 0.0,
			z = 0.0,
		},
		dimensions = {
			x = 1.0,
			y = 1.0,
			z = 1.0,
		},
	},

	material = "glass",
	
	sound = {
		type = "env",
		file = "sound.sound",
	},
}

function onInit()
	print("Calling in LUA")
	yourName = io.read()
	io.write("Hi ", yourName)
end

function onRepeat()
	print("Calling in LUA")
	yourName = io.read()
	io.write("Hi ", yourName)
end