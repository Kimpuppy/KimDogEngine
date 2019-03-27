#pragma once

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	std::list<Component *> components;

public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

public:
	template<typename ComponentType>
	inline void AddComponent()
	{
		ComponentType * component = new ComponentType(this);
		components.push_back(component);
	}

	template<typename ComponentType>
	inline ComponentType * GetComponent()
	{
		for (auto component : components) {
			if (dynamic_cast<ComponentType *>(component))
			{
				if (IsSameType<ComponentType *>(dynamic_cast<ComponentType *>(component)))
					return dynamic_cast<ComponentType *>(component);
			}
		}
		return nullptr;
	}

	template<typename ComponentType>
	inline bool HasComponent()
	{
		for (auto component : components) {
			if (dynamic_cast<ComponentType *>(component))
			{
				if (IsSameType<ComponentType *>(dynamic_cast<ComponentType *>(component)))
					return true;
			}
		}
		return false;
	}
};
