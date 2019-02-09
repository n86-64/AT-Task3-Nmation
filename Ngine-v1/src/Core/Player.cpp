#include "Camera.h"
#include "NPhysicsComponent.h"
#include "Player.h"

NPlayer::NPlayer()
{
	using namespace std::placeholders;
	//NPhysicsComponent* physicsComponent = new NPhysicsComponent();
	//physicsComponent->registerCollisionEvent(std::bind(&NPlayer::onCollision, this, _1));
	//physicsComponent->setGameObject(this);
	//physicsComponent->isKinematic(false);
	//physicsComponent->setMass(0.1f);
	//this->addComponent(physicsComponent);
}

void NPlayer::Update(GameStateData& gameData)
{
	float speed = 10.0f * gameData.timeData->getDeltaTimeInSeconds();
	NMath::Vector3   motion;

	motion = motion + (realForward * (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_W)));
    motion = motion + (realForward * (-speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_S)));

	//motion = motion + (realRight * (speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_D)));
	//motion = motion + (realRight * (-speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_A)));

//	position = position + motion;
	rotation = rotation + NMath::Vector3((speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_Q)) + (-speed * gameData.input->getKeyDown(NKeyboardKeys::KEY_R)), 0.0f, 0.0f);

	realForward = DirectX::XMVector3Transform(forward.getRawVector(), DirectX::XMMatrixRotationRollPitchYawFromVector(rotation.getRawVector()));
	realRight   = DirectX::XMVector3Transform(right.getRawVector(), DirectX::XMMatrixRotationRollPitchYawFromVector(rotation.getRawVector()));

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
	OutputDebugString("Lol collision.");
}

void NPlayer::setCamera(NCamera* camera)
{
	playerCamera = camera;
	//playerCamera->setCameraLookAt(this);
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

	// playerCamera->setRotation(rotation);
}
