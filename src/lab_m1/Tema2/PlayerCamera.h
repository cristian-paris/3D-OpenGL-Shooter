#pragma once

namespace implemented
{
	class PlayerCamera
	{
	public:
		PlayerCamera()
		{
			position = glm::vec3(0.f);
			forward = glm::vec3(0.f, 0.f, -1.f);
			up = glm::vec3(0.f, 1.f, 0.f);
			right = glm::vec3(1.f, 0.f, 0.f);
			distanceToTarget = 0.f;
		}

		PlayerCamera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up, const glm::mat4& projectMatrix, float distanceToTarget)
		{
			Set(position, center, up, projectMatrix, distanceToTarget);
		}

		~PlayerCamera()
		{ }

		// Update camera
		void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up, const glm::mat4& projectMatrix, float distanceToTarget)
		{
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
			this->projectionMatrix = projectMatrix;
			this->distanceToTarget = distanceToTarget;
		}

		void MoveForward(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0.f, forward.z));
			position += dir * distance;
		}

		void TranslateForward(float distance)
		{
			position += forward * distance;
		}

		void TranslateUpward(float distance)
		{
			position += up * distance;
		}

		void TranslateRight(float distance)
		{
			glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0.f, right.z));
			position += dir * distance;
		}

		void RotateFirstPerson_OX(float angle)
		{
			forward = glm::rotate(glm::mat4(1.f), angle, right) * glm::vec4(glm::vec3(forward), 0.f);
			forward = glm::normalize(forward);

			up = glm::cross(right, forward);
		}

		void RotateFirstPerson_OY(float angle)
		{
			forward = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(glm::vec3(forward), 0.f);
			forward = glm::normalize(forward);
			right = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(glm::vec3(right), 0.f);
			right = glm::normalize(right);
			up = glm::cross(right, forward);
		}

		void RotateFirstPerson_OZ(float angle)
		{
			right = glm::rotate(glm::mat4(1.f), angle, forward) * glm::vec4(glm::vec3(right), 0.f);
			right = glm::normalize(right);

			up = glm::cross(right, forward);
		}

		void RotateThirdPerson_OX(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OX(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OY(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OY(angle);
			TranslateForward(-distanceToTarget);
		}

		void RotateThirdPerson_OZ(float angle)
		{
			TranslateForward(distanceToTarget);
			RotateFirstPerson_OZ(angle);
			TranslateForward(-distanceToTarget);
		}

		glm::mat4 GetViewMatrix()
		{
			// Returns the view matrix
			return glm::lookAt(position, position + forward, up);
		}

		glm::vec3 GetTargetPosition()
		{
			return position + forward * distanceToTarget;
		}

	public:
		// Getters and setters for these
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
		glm::mat4 projectionMatrix = glm::mat4(1);
	};
}
