#include "Camera.h"
#include "NPhysicsComponent.h"
#include "Player.h"

NPlayer::NPlayer()
{
	using namespace std::placeholders;
	NPhysicsComponent* physicsComponent = new NPhysicsComponent();
	physicsComponent->registerCollisionEvent(std::bind(&NPlayer::onCollision, this, _1));
	physicsComponent->setGameObject(this);
	this->addComponent(physicsComponent);
}

void NPlayer::Update(GameStateData& gameData)
{
	float speed = 1.0f * gameData.timeData->getDeltaTimeInSeconds();

	position.setZ(position.z() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_W)));
	position.setZ(position.z() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_S)));

	position.setX(position.x() + (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_D)));
	position.setX(position.x() - (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_A)));

	rotation = rotation + NMath::Vector3(0.0f, (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_Q)) + (-speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_E)), 0.0f);

	if (playerCamera) 
	{
		updateCameraPosition(speed, gameData.input);
	}

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

void NPlayer::setCamera(NCamera* camera)
{
	playerCamera = camera;
	playerCamera->setCameraLookAt(this);
}

void NPlayer::updateCameraPosition(float speed, NInputHandler* input)
{
	NMath::Vector3  motion;

	motion.setZ((speed * input->getKeyDown(NKeyboardKeys::KEY_W)));
	motion.setZ(motion.z() - (speed * input->getKeyDown(NKeyboardKeys::KEY_S)));

	motion.setX((speed * input->getKeyDown(NKeyboardKeys::KEY_D)));
	motion.setX(motion.x() - (speed * input->getKeyDown(NKeyboardKeys::KEY_A)));

	playerCamera->setPosition(
		playerCamera->getPosition() + motion
	);
}
