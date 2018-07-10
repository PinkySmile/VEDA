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
	updatePlayer(player)
end

function doAttack1()
	local succ, err = playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
	if not succ then
		print(err)
	end
	stopTime(true)
	for i = 1, 20 do
		addProjectile(
			108 + math.cos(math.pi * i / 10) * 50,
			116 + math.sin(math.pi * i / 10) * 50,
			1,
			-1,
			90
		)
		succ, err = playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		if not succ then
			print(err)
		end
		yield(3)
	end
	stopTime(false)
end

function doAttack2()
	local succ, err
	for i = 1, 30 do
		addProjectile(
			108,
			0 + i * 16,
			0,
			-1,
			0
		)
		succ, err = playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		if not succ then
			print(err)
		end
		yield(3)
		if i == 20 then
			yield(40)
			succ, err = playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			if not succ then
				print(err)
			end
			stopTime(true)
		end
	end
	stopTime(false)
	yield(120)
	for i = 1, 30 do
		addProjectile(
			532,
			480 - i * 16,
			0,
			-1,
			180
		)
		succ, err = playSound("data/battles/alexandre/battle_normal/bullet_spawn_sound.ogg")
		if not succ then
			print(err)
		end
		yield(3)
		if i == 20 then
			yield(40)
			succ, err = playSound("data/battles/alexandre/battle_normal/stop_time_sound.ogg")
			if not succ then
				print(err)
			end
			stopTime(true)
		end
	end
	stopTime(false)
end

function bossAI(boss)
	playSound(0)
	yield(30)
	doAttack1()
	yield(100)
	while true do
		doAttack2()
		--updateBoss(boss)
		yield(150)
	end
end