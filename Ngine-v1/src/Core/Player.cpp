#include "NPhysicsComponent.h"
#include "Player.h"

NPlayer::NPlayer()
{
	using namespace std::placeholders;
	NPhysicsComponent* physicsComponent = new NPhysicsComponent();
	physicsComponent->registerCollisionEvent(std::bind(&NPlayer::onCollision, this, _1));
	this->addComponent(physicsComponent);
}

void NPlayer::Update(GameStateData& gameData)
{
	float speed = 10.0f * gameData.timeData->getDeltaTimeInSeconds();

	position.setZ(position.z() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_W)));
	position.setZ(position.z() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_S)));

	position.setX(position.x() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_D)));
	position.setX(position.x() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_A)));

	NGameObject::Update(gameData);
}

void NPlayer::Render(NRenderer * renderer)
{
	NGameObject::Render(renderer);
}

void NPlayer::onCollision(NPhysicsComponent* component)
{
	OutputDebugString("A collision was detected. \n");
}
