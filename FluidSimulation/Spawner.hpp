#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "Simulation.hpp"
#include "Conf.hpp"
#include "Util.hpp"

class Spawner
{
public:
	Simulation& sim;

	Spawner(Simulation& sim_) : sim(sim_) {}

	void spawnParticle(Particle p)
	{
		sim.addParticle(p);
	}

	void spawnLine(Particle p, float spaceBetween)
	{
		spawnParticle(p);
		sf::Vector2f v = p.v, norm_v(v.y, -v.x);
		norm_v /= getLen(norm_v);

		if (std::isnan(norm_v.x) || std::isinf(norm_v.x))
		{
			float angle = randFloat(0.0, 360.0) * conf::PI / 180;
			norm_v = sf::Vector2f(cos(angle), sin(angle));
		}

		for (int i = 1; i <= (conf::particle_amount - 1) / 2; i++)
		{
			Particle left(p.pos + spaceBetween * norm_v * float(i));
			left.v = p.v;
			spawnParticle(left);
		}

		for (int i = 1; i <= (conf::particle_amount - 1) / 2; i++)
		{
			Particle right(p.pos - spaceBetween * norm_v * float(i));
			right.v = p.v;
			spawnParticle(right);
		}

		if ((conf::particle_amount - 1) % 2 == 1)
		{
			Particle left(p.pos + spaceBetween * norm_v * float((conf::particle_amount - 1) / 2 + 1));
			left.v = p.v;
			spawnParticle(left);
		}
	}
};