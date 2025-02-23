#pragma once
#include "merlin/core/core.h"

#include "camera.h"
#include "merlin/core/timestep.h"

#include "merlin/events/applicationevent.h"
#include "merlin/events/mouseevent.h"

namespace Merlin {

	class CameraController {
	public:

		CameraController(shared<Camera> cam) : _Camera(cam) {}
		virtual void onUpdate(Timestep ts) = 0;
		virtual void onEvent(Event& e) = 0;

		Camera& getCamera() const { return *_Camera; }
		shared<Camera> shareCamera() const { return _Camera; }
		float getCameraSpeed() const { return _CameraSpeed; }
		void setCameraSpeed(float speed) { _CameraSpeed = speed; }
		void setZoomLevel(float zl);


	protected:
		shared<Camera> _Camera;
		float _CameraSpeed = 1.0f;
		float _ZoomLevel = 1.0f;
	};

	class CameraController3D : public CameraController {
	public:
		CameraController3D(shared<Camera> cam);
		virtual void onUpdate(Timestep ts) override;
		virtual void onEvent(Event& e) override;

	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);

		glm::vec2 _lastMousePos = { 0.0f, 0.0f};
		glm::vec2 _deltaMousePos = { 0.0f, 0.0f };

		glm::vec3 _dU = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _dR = { 0.0f, 0.0f, 0.0f }; //In degrees, in the anti-clockwise direction, yaw, pitch, roll
	};


	class CameraController2D : public CameraController {
	public:
		CameraController2D(shared<Camera> Camera);
		void onUpdate(Timestep ts) override;
		void onEvent(Event& e) override;
		
	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		glm::vec2 _dU = { 0.0f, 0.0f };
		glm::vec2 _lastMousePos = { 0.0f, 0.0f };
		glm::vec2 _deltaMousePos = { 0.0f, 0.0f };
	};

	typedef shared<CameraController> CameraController_Ptr;
}