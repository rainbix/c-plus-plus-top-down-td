#pragma once

class IClickAction
{
protected:
	~IClickAction() = default;

public:
	void virtual OnClickAction() = 0;
};
