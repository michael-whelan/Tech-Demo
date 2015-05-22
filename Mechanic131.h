#ifndef MECHANIC131_H
#define MECHANIC131_H
#include <math.h>
class Mechanic131 : public Test
{
public:
	Mechanic131(){

		m_hz = 4.0f;
		m_zeta = 0.7f;
		m_speed = 50.0f;
		CATEGORY_1 = 0x0001;

		cogH = 0.5;
		cogW= 0.2;
		nCogs = 9;
		cogRad = 2.8;
		//wheel
#pragma region //wheel
		{
			b2CircleShape circle;
			circle.m_radius = 5.0f;
			b2FixtureDef fd;

			b2BodyDef bd;
			bd.type = b2_kinematicBody;

			fd.shape = &circle;
			fd.density = 10.0f;
			fd.friction = 0.9f;
			fd.filter.maskBits = 50;

			bd.position.Set(-1.0f, 30.0f);
			bd.gravityScale = 0;
			bd.angularVelocity =0.5f * b2_pi; 
			m_wheel = m_world->CreateBody(&bd);
			
			m_wheel->CreateFixture(&fd);

			circle.m_radius = 0.2f;
			circle.m_p = b2Vec2(0,4);
			fd.shape = &circle;
			fd.density = 10.0f;
			fd.friction = 0.9f;
			fd.filter.maskBits = CATEGORY_1;
			m_wheel->CreateFixture(&fd);

		}
#pragma endregion
#pragma region //Gap Square
		// Define Square with Gap
		{
			b2PolygonShape shape;
			b2FixtureDef fd;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-1.0f, 26.3f);
			bd.gravityScale = 0;
			bd.fixedRotation = false;
			b2Body* body1 = m_world->CreateBody(&bd);
			//top
			shape.SetAsBox(1.0f, 0.2f,b2Vec2(0.5f,8.0f),0.01f);
			fd.shape = &shape;
			fd.density = 2.0f;
			fd.friction = 0.9f;
			fd.filter.categoryBits = CATEGORY_1;
			body1->CreateFixture(&fd);
			//bottom
			shape.SetAsBox(1.0f, 0.2f,b2Vec2(0.5f,-8.0f),0.01f);
			body1->CreateFixture(&fd);
			//left
			shape.SetAsBox(0.2f, 8.0f,b2Vec2(0,0.0f),0.01f);
			//shape.SetAsBox(0.2f, 2.0f);
			body1->CreateFixture(&fd);
			//right
			shape.SetAsBox(0.2f, 8.0f,b2Vec2(1,0.0f),0.01f);
			body1->CreateFixture(&fd);
			
			//spiked bottom
			shape.SetAsBox(0.2f, 0.8f,b2Vec2(-0.5f,-9.0f),-0.5f);
			body1->CreateFixture(&fd);
			//left
			shape.SetAsBox(0.2f, 0.8f,b2Vec2(0.5f,-9.0f),0.0f);
			body1->CreateFixture(&fd);
			//right
			shape.SetAsBox(0.2f, 0.8f,b2Vec2(1.5f,-9.0f),0.5f);
			body1->CreateFixture(&fd);

			bd.position.Set(0.5f,-9.0f); 
			//b2S polygonShape = b2PolygonShape();
			for (int i=0; i<nCogs; ++i) {
				float angle = -1*(b2_pi/nCogs*i);
				shape.SetAsBox((float)cogH/2,(float)cogW/2, b2Vec2(cogRad*cos(angle)+0.3,cogRad*sin(angle)-8),angle);
				//fd.shape=polygonShape;
				body1->CreateFixture(&fd);
			}
		}
#pragma endregion

#pragma region //pivot joint
		// Pivot
		{
			b2CircleShape circle;
			circle.m_radius = 0.3f;
			b2FixtureDef fd;

			b2BodyDef bd;
			bd.type = b2_staticBody;

			fd.shape = &circle;
			fd.density = 10.0f;
			fd.friction = 0.9f;
			fd.filter.maskBits = CATEGORY_1;

			bd.position.Set(0.0f, 19.0f);
			bd.gravityScale = 0;
			m_wheel = m_world->CreateBody(&bd);
			
			m_wheel->CreateFixture(&fd);

		}
#pragma endregion


		
#pragma region //Horizontal bar
		// horizontal
		{
			b2PolygonShape shape;
			b2FixtureDef fd;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(0.5f,14.8f);
			bd.gravityScale = 1;
			bd.fixedRotation = false;
			b2Body* body1 = m_world->CreateBody(&bd);
			//top
			shape.SetAsBox(8.0f, 1.0f,b2Vec2(0.5f,0),0.0f);
			fd.shape = &shape;
			fd.density = 2.0f;
			fd.friction = 0.9f;
			fd.filter.categoryBits = CATEGORY_1;
			body1->CreateFixture(&fd);
			nCogs =10;
			for (int i=0; i<nCogs; ++i) {
				//float angle = 1*(b2_pi/nCogs*i);
				shape.SetAsBox((float)cogW/2,(float)cogH/2, b2Vec2((i*0.7)-3,1.2),0.0f);
				body1->CreateFixture(&fd);
			}
		}
#pragma endregion

		#pragma region //Horizontal blockers
		{
			b2PolygonShape shape;
			b2FixtureDef fd;
			b2BodyDef bd;
			bd.type = b2_kinematicBody;
			bd.position.Set(0.5f,11.8f);
			bd.gravityScale = 0;
			bd.fixedRotation = false;
			b2Body* body1 = m_world->CreateBody(&bd);
			//topL
			shape.SetAsBox(0.5f, 0.5f,b2Vec2(-6,4.05),0.0f);
			fd.shape = &shape;
			fd.density = 2.0f;
			fd.friction = 0.9f;
			fd.filter.categoryBits = CATEGORY_1;
			body1->CreateFixture(&fd);

			shape.SetAsBox(0.5f, 0.5f,b2Vec2(-6,1),0.0f);
			body1->CreateFixture(&fd);
			
			shape.SetAsBox(0.5f, 0.5f,b2Vec2(5,4.05),0.0f);
			body1->CreateFixture(&fd);

			shape.SetAsBox(0.5f, 0.5f,b2Vec2(5,1),0.0f);
			body1->CreateFixture(&fd);
		}
#pragma endregion
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'a':
			m_spring1->SetMotorSpeed(m_speed);
			break;

		case 's':
			m_spring1->SetMotorSpeed(0.0f);
			break;

		case 'd':
			m_spring1->SetMotorSpeed(-m_speed);
			break;

		case 'q':
			m_hz = b2Max(0.0f, m_hz - 1.0f);
			m_spring1->SetSpringFrequencyHz(m_hz);
			break;

		case 'e':
			m_hz += 1.0f;
			m_spring1->SetSpringFrequencyHz(m_hz);
			break;
		}
	}

	static Test* Create()
	{
		return new Mechanic131;
	}

	b2Body* m_wheel;
	b2WheelJoint* m_spring1;
	b2RevoluteJoint* m_joint1;
	float cogH,cogW,nCogs,cogRad;

	short CATEGORY_1;  // 0000000000000001 in binary
	float32 m_hz;
	float32 m_zeta;
	float32 m_speed;
};



#endif