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
	elseif direction == 2 and player.position.y < 640 then
		player.position.y = player.position.y + 1
	elseif direction == 3 and player.position.x > 0 then
		player.position.x = player.position.x - 1
	end
	updatePlayer(player)
end

function bossAI(boss)
	while true do
		updateBoss(boss)
		yield()
	end
end