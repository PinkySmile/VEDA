function onProjectileDie(projectile)

end

function onProjectileHit(projectile, target)
	if projectile.owner == target.id then
		return
	end
end

function onBossDie()

end

function onPlayerShoot(player, mousePos)
	addProjectile(player.position.x + 4, player.position.y, 0, player.id)
	addProjectile(player.position.x - 4, player.position.y, 0, player.id)
end

function onPlayerMove(player, direction)
	if direction == 0 and player.position.y > 0 then
		player.position.y = player.position.y - 1
	elseif direction == 1 and player.direction.x < 540 then
		player.position.x = player.position.x + 1
	elseif direction == 2 and player.position.y < 480 then
		player.position.y = player.position.y + 1
	elseif direction == 3 and player.position.x > 0 then
		player.position.x = player.position.x - 1
	end
	vedaApi.updatePlayer(player)
end

function yield(timer)
	vedaApi.yield(timer)
end

function doAttack1()
	local	projectiles = {}
	local	anim = 0

	repeat
		boss.x = boss.x + (boss.x > 316 and -1 or 1)
		vedaApi.yield()
		anim = anim + 1
		boss.animation = (boss.x > 316 and 3 or 1) + (anim % 20 < 10 and 4 or 0)
	until boss.x == 316
	repeat
		boss.y = boss.y + (boss.y > 224 and -1 or 1)
		vedaApi.yield()
		anim = anim + 1
		boss.animation = (boss.y > 224 and 0 or 2) + (anim % 20 < 10 and 4 or 0)
	until boss.y == 224
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(true)
	boss.animation = 8
	for i = 1, 20 do
		projectiles[#projectiles + 1] = vedaApi.addProjectile(
			boss.x + 16 + math.cos(math.pi * i / 10) * 50,
			boss.y + 16 + math.sin(math.pi * i / 10) * 50,
			1,
			-1,
			i * 180 / 10 + 180
		)
		projectiles[#projectiles].speed = 0
		projectiles[#projectiles].acceleration = 0
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		vedaApi.yield(3)
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	vedaApi.yield(120)
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(true)
	vedaApi.yield(30)
	for i, projectile in pairs(projectiles) do
		projectile.rotationSpeed = 2.7
		projectile.speed = 1.5
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	vedaApi.yield(60)
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	boss.animation = 9
	vedaApi.stopTime(true)
	for i, projectile in pairs(projectiles) do
		local OB = math.sqrt((boss.x + 16      - projectile.x) ^ 2 + (boss.y + 16 - projectile.y) ^ 2)
		local AB = math.sqrt((boss.x + 16 + OB - projectile.x) ^ 2 + (boss.y + 16 - projectile.y) ^ 2)
		local AO = OB
		
		projectile.angle = math.acos((AB ^ 2 - AO ^ 2 - OB ^ 2) / (-2 * AO * OB)) * 180 / math.pi
		if projectile.y < boss.y + 16 then
			projectile.angle = -projectile.angle
		end
		projectile.rotationSpeed = 0
		projectile.speed = 10
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		vedaApi.yield(3)
	end
	vedaApi.yield(7)
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	boss.animation = 10
	vedaApi.yield(30)
	boss.animation = 11
	vedaApi.yield(70)
end

function doAttack2()
	local	succ, err
	local	projs = {}

	for i = 1, 30 do
		projs[i] = vedaApi.addProjectile(
			108,
			0 + i * 16,
			0,
			-1,
			0
		)
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		yield(3)
		if i == 20 then
			yield(40)
			vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			vedaApi.stopTime(true)
		end
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	yield(120)
	for i = 1, 30 do
		projs[30 + i] = vedaApi.addProjectile(
			532,
			480 - i * 16,
			0,
			-1,
			180
		)
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		yield(3)
		if i == 20 then
			yield(40)
			vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			vedaApi.stopTime(true)
		end
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	yield(120)
end

function bossAI()
	local proj = vedaApi.addProjectile(
		116,
		116,
		1,
		-1,
		-90
	)

	boss.animation = 11
	proj.rotationSpeed = 0;
	vedaApi.playSound(0)
	vedaApi.yield(30)
	proj = nil
	collectgarbage()
	doAttack1()
	while true do
		doAttack2()
		yield(30)
	end
end