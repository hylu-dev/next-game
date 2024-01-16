#include "stdafx.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

void BoxCollider::Initialize() {
    Collider::Initialize();
}

void BoxCollider::Update() {
}

void BoxCollider::Destroy() {
    collisionHook = nullptr;
}

ColliderType BoxCollider::GetType()
{
	return ColliderType::BOX;
}

void BoxCollider::Collide(Collider* other) {
    float3 p1 = parentEntity->GetTransform().position;
    float3 p2 = other->parentEntity->GetTransform().position;

    if (other->GetType() == ColliderType::BOX) {
        BoxCollider* collider = static_cast<BoxCollider*>(other);

        bool isXCollide = std::abs(p1.x - p2.x) < (dimensions.x + collider->dimensions.x) * 0.5;
        bool isYCollide = std::abs(p1.y - p2.y) < (dimensions.y + collider->dimensions.y) * 0.5;
        bool isZCollide = std::abs(p1.z - p2.z) < (dimensions.z + collider->dimensions.z) * 0.5;

        if (isXCollide && isYCollide && isZCollide) {
            if (collisionHook != nullptr) {
                collisionHook(this, collider);
            }
        }

    }
    else if (other->GetType() == ColliderType::SPHERE) {
        SphereCollider* collider = static_cast<SphereCollider*>(other);

        float halfBoxX = dimensions.x * 0.5;
        float halfBoxY = dimensions.y * 0.5;
        float halfBoxZ = dimensions.z * 0.5;

        float3 closestPoint;
        closestPoint.x = max(p1.x - halfBoxX, min(p2.x, p1.x + halfBoxX));
        closestPoint.y = max(p1.y - halfBoxY, min(p2.y, p1.y + halfBoxY));
        closestPoint.z = max(p1.z - halfBoxZ, min(p2.z, p1.z + halfBoxZ));

        float distance = p2.Distance(closestPoint);

        if (distance < collider->radius) {
            if (collisionHook != nullptr) {
                collisionHook(this, collider);
            }
        }
    }
}
