#include <server/GameEngine.h>
#include <common/SharedMemory.h>
#include <common/Player.h>
#include <common/dimmensions.h>
#include <common/Ball.h>
#include <iostream>
#include <cstddef>
#include <Box2D/Box2D.h>
#include <unistd.h>

using namespace server;
using namespace common;

GameEngine::GameEngine(SharedMemory& sharedMemory)
	: sharedMemory(sharedMemory)
{
}

void* GameEngine::start_routine()
{
	std::cout << "game engine thread" << std::endl;

	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	const float scaleFactor = 100.0f;

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 0.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef ceilingBodyDef;
	ceilingBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, windowHeightf/scaleFactor);
	b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
	b2PolygonShape ceilingBox;
	ceilingBox.SetAsBox(0.5f*windowWidthf/scaleFactor, borderSizef/scaleFactor);
	ceilingBody->CreateFixture(&ceilingBox, 0.0f);

	b2BodyDef leftBodyDef;
	leftBodyDef.position.Set(0.0f, 0.5f*windowHeightf/scaleFactor);
	b2Body* leftBody = world.CreateBody(&leftBodyDef);
	b2PolygonShape leftSideBox;
	leftSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeight/scaleFactor);
	leftBody->CreateFixture(&leftSideBox, 0.0f);

	b2BodyDef rightBodyDef;
	rightBodyDef.position.Set(windowWidthf/scaleFactor, 0.5f*windowHeightf/scaleFactor);
	b2Body* rightBody = world.CreateBody(&rightBodyDef);
	b2PolygonShape rightSideBox;
	rightSideBox.SetAsBox(borderSizef/scaleFactor, 0.5f*windowHeightf/scaleFactor);
	rightBody->CreateFixture(&rightSideBox, 0.0f);

	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(0.5f*(windowWidthf-circleRadiusf)/scaleFactor, 0.5f*(windowHeightf-circleRadiusf)/scaleFactor);
	ballBodyDef.gravityScale = 0.0f;
	b2Body* ballBody = world.CreateBody(&ballBodyDef);
	b2CircleShape ballCircle;
	ballCircle.m_radius = circleRadiusf/scaleFactor;
	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &ballCircle;
	ballFixtureDef.density = 1.0f;
	ballFixtureDef.friction = 0.3f;
	ballFixtureDef.restitution = 1.0f;
	ballBody->CreateFixture(&ballFixtureDef);
	b2Vec2 vvv(-2.8f, 3.5f);
	ballBody->SetLinearVelocity(vvv);

	b2BodyDef bottomPlayerBodyDef;
	bottomPlayerBodyDef.type = b2_kinematicBody;
	bottomPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, windowHeightf/scaleFactor - 0.9f);
	b2Body* bottomPlayerBody = world.CreateBody(&bottomPlayerBodyDef);
	b2PolygonShape bottomPlayerPolygon;
	bottomPlayerPolygon.SetAsBox(0.5f*platformWidthf/scaleFactor, 0.5f*platformHeightf/scaleFactor);
	b2FixtureDef bottomPlayerFixtureDef;
	bottomPlayerFixtureDef.shape = &bottomPlayerPolygon;
	bottomPlayerFixtureDef.density = 1.0f;
	bottomPlayerFixtureDef.friction = 0.2f;
	bottomPlayerBody->CreateFixture(&bottomPlayerFixtureDef);

	b2BodyDef topPlayerBodyDef;
	topPlayerBodyDef.type = b2_kinematicBody;
	topPlayerBodyDef.position.Set(0.5f*windowWidthf/scaleFactor, 0.9f);
	b2Body* topPlayerBody = world.CreateBody(&topPlayerBodyDef);
	b2PolygonShape topPlayerPolygon;
	topPlayerPolygon.SetAsBox(0.5*platformWidthf/scaleFactor, 0.5f*platformHeight/scaleFactor);
	b2FixtureDef topPlayerFixtureDef;
	topPlayerFixtureDef.shape = &topPlayerPolygon;
	topPlayerFixtureDef.density = 1.0f;
	topPlayerFixtureDef.friction = 0.2f;
	topPlayerBody->CreateFixture(&topPlayerFixtureDef);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// TODO
	bool quit = false;

	Ball ball;
	Player player[2];
	CursorPosition cursorPosition[2];

	while (!quit)
	{
		// set velocity
		b2Vec2 bottomPlayerPosition = bottomPlayerBody->GetPosition();
		sharedMemory.getPlayerCursorPosition(cursorPosition[0], 0);
		b2Vec2 bottomPlayerLinearVelocity(30.0f*(cursorPosition[0].x / scaleFactor - bottomPlayerPosition.x), 0.0f);
		bottomPlayerBody->SetLinearVelocity(bottomPlayerLinearVelocity);

		b2Vec2 topPlayerPosition = topPlayerBody->GetPosition();
		sharedMemory.getPlayerCursorPosition(cursorPosition[1], 1);
		b2Vec2 topPlayerLinearVelocity(30.0f*(cursorPosition[1].x / scaleFactor - topPlayerPosition.x), 0.0f);
		topPlayerBody->SetLinearVelocity(topPlayerLinearVelocity);

		// update world
		bool alreadyStarted;
		sharedMemory.getStarted(alreadyStarted);
		if (alreadyStarted)
		{
			world.Step(timeStep, velocityIterations, positionIterations);
		}

		// change world rules
		b2Vec2 vcx = ballBody->GetLinearVelocity();
		//printf("%4.2f %4.2f\n", vcx.x, vcx.y);
		const float minThrV = 4.0f;
		if (vcx.y < minThrV && vcx.y > -minThrV)
		{
			if (vcx.y >= 0.0f)
				vcx.y = minThrV;
			else
				vcx.y = -minThrV;
			ballBody->SetLinearVelocity(vcx);
		}
		const float maxThrV = 10.0f;
		if (vcx.x > maxThrV || vcx.x < -maxThrV)
		{
			if (vcx.x >= 0.0f)
				vcx.x = maxThrV;
			else
				vcx.x = -maxThrV;
			ballBody->SetLinearVelocity(vcx);
		}

		if (vcx.y > maxThrV || vcx.y < -maxThrV)
		{
			if (vcx.y >= 0.0f)
				vcx.y = maxThrV;
			else
				vcx.y = -maxThrV;
			ballBody->SetLinearVelocity(vcx);
		}

		// set structures in shared memory
		bottomPlayerPosition = bottomPlayerBody->GetPosition();
		player[0].setPosition(bottomPlayerPosition.x * scaleFactor, bottomPlayerPosition.y * scaleFactor);

		topPlayerPosition = topPlayerBody->GetPosition();
		player[1].setPosition(topPlayerPosition.x * scaleFactor, topPlayerPosition.y * scaleFactor);

		b2Vec2 ballPosition = ballBody->GetPosition();
		ball.setPosition(ballPosition.x * scaleFactor, ballPosition.y * scaleFactor);

		//std::cout << ballPosition.x << " " << ballPosition.y << std::endl;

		sharedMemory.setCurrentState(ball, player[0], player[1]);

		usleep(static_cast<int>(1000000.0/60.0));

		sharedMemory.getEnded(quit);
	}


	return NULL;
}
