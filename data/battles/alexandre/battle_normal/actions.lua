local projs = {}

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

function doAttack1(boss)
	local	projectiles = {}

	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(true)
	for i = 1, 20 do
		projectiles[#projectiles + 1] = vedaApi.addProjectile(
			108 + math.cos(math.pi * i / 10) * 50,
			116 + math.sin(math.pi * i / 10) * 50,
			1,
			-1,
			i * 180 / 10 + 180
		)
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
		projectile.rotationSpeed = 2
		projectile.speed = 2
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	vedaApi.yield(120)
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(true)
	for i, projectile in pairs(projectiles) do
		local OB = math.sqrt((boss.x + 8      - projectile.x) ^ 2 + (boss.y + 16 - projectile.y) ^ 2)
		local AB = math.sqrt((boss.x + 8 + OB - projectile.x) ^ 2 + (boss.y + 16 - projectile.y) ^ 2)
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
	vedaApi.yield(100)
	for i, projectile in pairs(projectiles) do
		projectile:setToRemove()
	end
end

function collectGarbage()
	for i, k in pairs(projs) do
		if k.lifeTime > 2 then
			k:setToRemove()
		end
	end
end

function doAttack2()
	local	succ, err
	for i = 1, 30 do
		projs[#projs + 1] = vedaApi.addProjectile(
			108,
			0 + i * 16,
			0,
			-1,
			0
		)
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		collectGarbage()
		vedaApi.yield(3)
		if i == 20 then
			vedaApi.yield(40)
			vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			vedaApi.stopTime(true)
		end
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	vedaApi.yield(120)
	collectGarbage()
	for i = 1, 30 do
		projs[#projs + 1] = vedaApi.addProjectile(
			532,
			480 - i * 16,
			0,
			-1,
			180
		)
		vedaApi.playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		collectGarbage()
		vedaApi.yield(3)
		if i == 20 then
			vedaApi.yield(40)
			vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			vedaApi.stopTime(true)
		end
	end
	vedaApi.playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	vedaApi.stopTime(false)
	vedaApi.yield(120)
	collectGarbage()
end

function bossAI(boss)
	local proj = vedaApi.addProjectile(
		100,
		100,
		1,
		-1,
		0
	)
	vedaApi.playSound(0)
	vedaApi.yield(30)
	proj:setToRemove()
	doAttack1({x = 100, y = 100})
	while true do
		doAttack2()
		--vedaApi.updateBoss(boss)
		vedaApi.yield(30)
		collectGarbage()
	end
end