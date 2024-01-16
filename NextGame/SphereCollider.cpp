#include "stdafx.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

void SphereCollider::Initialize() {
    Collider::Initialize();
}

void SphereCollider::Update() {

}

void SphereCollider::Destroy() {
    collisionHook = nullptr;
}

ColliderType SphereCollider::GetType() {
	return ColliderType::SPHERE;
}

void SphereCollider::Collide(Collider* other) {
    float3 p1 = parentEntity->GetTransform().position;
    float3 p2 = other->parentEntity->GetTransform().position;
    if (other->GetType() == ColliderType::SPHERE) {
        SphereCollider* collider = static_cast<SphereCollider*>(other);
        float distance = p1.Distance(p2);
        if (distance < (radius + collider->radius)) {
            if (collisionHook != nullptr) {
                collisionHook(this, collider);
            }
        }
    }
    else if (other->GetType() == ColliderType::BOX) {
        BoxCollider* collider = static_cast<BoxCollider*>(other);

        float halfBoxX = collider->dimensions.x * 0.5;
        float halfBoxY = collider->dimensions.y * 0.5;
        float halfBoxZ = collider->dimensions.z * 0.5;

        float3 closestPoint;
        closestPoint.x = max(p2.x - halfBoxX, min(p1.x, p2.x + halfBoxX));
        closestPoint.y = max(p2.y - halfBoxY, min(p1.y, p2.y + halfBoxY));
        closestPoint.z = max(p2.z - halfBoxZ, min(p1.z, p2.z + halfBoxZ));

        float distance = p1.Distance(closestPoint);

        if (distance < radius) {
            if (collisionHook != nullptr) {
                collisionHook(this, collider);
            }
        }
    }
}
