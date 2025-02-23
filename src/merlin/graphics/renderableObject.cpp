#include "pch.h"
#include "merlin/core/core.h"
#include "merlin/graphics/renderableObject.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Merlin {
	
	int RenderableObject::nextID = 0;

	std::string RenderableObject::typeToString(ObjectType ob) {

		switch (ob){
		case Merlin::ObjectType::SCENE:
			return "Scene";
			break;
		case Merlin::ObjectType::MODEL:
			return "Model";
			break;
		case Merlin::ObjectType::MESH:
			return "Mesh";
			break;
		case Merlin::ObjectType::TRANSFORM:
			return "Transform";
			break;
		case Merlin::ObjectType::PARTICLESYSTEM:
			return "ParticleSystem";
			break;
		default:
			return "GenericObject";
			break;
		}
	}

	RenderableObject::RenderableObject() : m_type(ObjectType::GENERIC), m_parent(nullptr), m_transform(glm::mat4(1)) {
		m_ID = nextID++;
		m_name = typeToString(m_type) + std::to_string(m_ID);
	}

	RenderableObject::RenderableObject(std::string name, ObjectType type) : m_type(type), m_parent(nullptr), m_name(name), m_transform(glm::mat4(1)) {
		m_ID = nextID++;
	}

	shared<RenderableObject> RenderableObject::getChild(std::string name) {
		for (auto child : m_children) {
			if (child->name() == name) return child;
		}
		return nullptr;
	}

	void RenderableObject::enableWireFrameMode(){
		m_wireframe = true;
		for (auto child : m_children) {
			child->enableWireFrameMode();
		}
	}

	void RenderableObject::disableWireFrameMode(){
		m_wireframe = false;
		for (auto child : m_children) {
			child->disableWireFrameMode();
		}
	}

	void RenderableObject::addChild(const shared<RenderableObject>& child) {
		if (child != nullptr) {
			m_children.push_back(child);
			child->setParent(this);
		}
		else Console::warn("SceneNode") << "Empty node child ignored" << Console::endl;
	}
	void RenderableObject::removeChild(shared<RenderableObject> child) {
		m_children.remove(child);
	}

	void RenderableObject::setParent(RenderableObject* parent) {
		m_parent = parent;
	}

	bool RenderableObject::hasParent() const {
		return m_parent != nullptr;
	}

	bool RenderableObject::hasChildren() const {
		return m_children.size();
	}


	std::list<shared<RenderableObject>>& RenderableObject::children() {
		return m_children;
	}

	RenderableObject* RenderableObject::parent() {
		return m_parent;
	}


	void RenderableObject::translate(glm::vec3 v) {
		m_transform = glm::translate(m_transform, v);
	}

	void RenderableObject::scale(glm::vec3 v) {
		m_transform = glm::scale(m_transform, v);
	}

	void RenderableObject::scale(float v) {
		m_transform = glm::scale(m_transform, glm::vec3(v));
	}

	void RenderableObject::setPosition(glm::vec3 v) {
		m_transform = glm::translate(m_transform, v - position());
	}

	void RenderableObject::rotate(glm::vec3 v) {
		m_transform = glm::rotate(m_transform, v.x, glm::vec3(1, 0, 0));
		m_transform = glm::rotate(m_transform, v.y, glm::vec3(0, 1, 0));
		m_transform = glm::rotate(m_transform, v.z, glm::vec3(0, 0, 1));
	}

	void RenderableObject::rotate(float angle, glm::vec3 v) {
		m_transform = glm::rotate(m_transform, angle, v);
	}

	void RenderableObject::setTransform(glm::mat4 t) {
		m_transform = t;
	}

	const glm::vec3& RenderableObject::position() const {
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(m_transform, scale, rotation, translation, skew, perspective);
		return translation;
	}

	const glm::quat& RenderableObject::rotation() const {
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(m_transform, scale, rotation, translation, skew, perspective);
		return rotation;
	}

	const glm::vec3& RenderableObject::scale() const {
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(m_transform, scale, rotation, translation, skew, perspective);
		return scale;
	}

	glm::mat4& RenderableObject::globalTransform() {
		//loop to the scene graph to get global transform
		glm::mat4 globalTransform = glm::mat4(1.0f); // Initialize with identity matrix
		std::vector<glm::mat4> nodeStack;

		RenderableObject* node = this;
		int it = 0;

		while (node && it < 50) {// Push all nodes to the stack
			nodeStack.push_back(node->transform());
			node = node->parent();
		}

		// Multiply matrices in the correct order (from root to leaf)
		for (auto it = nodeStack.rbegin(); it != nodeStack.rend(); ++it) {
			globalTransform = globalTransform * (*it);
		}
		return globalTransform;
	}


}