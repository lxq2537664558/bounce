/*
* Copyright (c) 2016-2016 Irlan Robson http://www.irlan.net
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BOX_STACK_H
#define BOX_STACK_H

class BoxStack : public Test
{
public:
	enum
	{
		e_rowCount = 1,
		e_columnCount = 5,
		e_depthCount = 1
	};

	BoxStack()
	{
		{
			b3BodyDef bdef;
			bdef.type = b3BodyType::e_staticBody;

			b3Body* body = m_world.CreateBody(bdef);

			b3HullShape hs;
			hs.m_hull = &m_groundHull;

			b3ShapeDef sdef;
			sdef.shape = &hs;
			sdef.friction = 1.0f;

			body->CreateShape(sdef);
		}

		b3Vec3 boxScale(1.0f, 1.0f, 1.0f);

		b3Vec3 stackOrigin(0.0f, 4.05f, 0.0f);

		for (u32 i = 0; i < e_rowCount; ++i)
		{
			for (u32 j = 0; j < e_columnCount; ++j)
			{
				for (u32 k = 0; k < e_depthCount; ++k)
				{
					b3BodyDef bdef;
					bdef.type = b3BodyType::e_dynamicBody;
					bdef.orientation.Set(b3Vec3(0.0f, 1.0f, 0.0f), 0.5f * B3_PI);

					bdef.position.x = float32(i) * boxScale.x;
					bdef.position.y = 2.5f * float32(j) * boxScale.y;
					bdef.position.z = float32(k) * boxScale.z;

					bdef.position += stackOrigin;

					b3Body* body = m_world.CreateBody(bdef);

					b3HullShape hs;
					hs.m_hull = &b3BoxHull_identity;

					b3ShapeDef sdef;
					sdef.density = 0.1f;
					sdef.friction = 0.3f;
					sdef.shape = &hs;

					body->CreateShape(sdef);
				}
			}
		}
	}

	static Test* Create()
	{
		return new BoxStack();
	}
};

#endif